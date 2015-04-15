#include "CJsonSerializer.h"
#include "CJsonSerializableFactory.h"
#include <jsoncpp/json/json.h>

///////////////////////////////////////////////////////////////////////////////
/// \brief Autoregisters CJsonSerializer into CJsonSerializer
/// It uses typeName() method to get the name of the type it wants to register.
/// BEWARE! Types must have different names for this to work propperly
///////////////////////////////////////////////////////////////////////////////
CJsonSerializer::CJsonSerializer(std::string typeName) {
  m_typeName = typeName;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Destructs the IJsonSerializable part of the object
///////////////////////////////////////////////////////////////////////////////
CJsonSerializer::~CJsonSerializer() {
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Standard implementation of serialize method (uses write2json)
///
/// \returns String with the command serialized
///////////////////////////////////////////////////////////////////////////////
std::string
CJsonSerializer::json_serialize() const {
  Json::Value       root;
  Json::FastWriter  writer;

  write2json(root);

  return writer.write(root);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Deserialize a Json Value into an object and return IJSonSerializable*
///
/// \param jv Json Value of the object to be deserialized
/// \returns IJSonSerializable* casted object newly created
///////////////////////////////////////////////////////////////////////////////
IJsonSerializable*
CJsonSerializer::json_deserialize(const std::string& json_str) const {
  Json::Value  jv;
  Json::Reader reader;

  // Parse Json String
  if ( !reader.parse (json_str, jv) )
    throw "Parse Exception: An error ocurred while parsing a json string.";
  
  return createObjectFromJson(jv);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Creates a new object from its Json representation
///
/// \param json Json Value of the object to be reconstructed
/// \returns IJSonSerializable* casted object newly created
///////////////////////////////////////////////////////////////////////////////
IJsonSerializable*
CJsonSerializer::createObjectFromJson(const Json::Value& json) const {
  // Getting the type of the object to deserialize
  std::string type = json.get("type", "").asString();
  if (type.compare("") == 0)
    throw "Exception: type not found in json string during deserialization of json.";
  //std::cout << "VIENE A SERIALIZAR" << type << std::endl;
  // Create new instance of the type of object reconstruct it from json
  IJsonSerializable *new_instance = CJSFACT.create(type);
  //std::cout << "VIENE A SERIALIZAR" << type << std::endl;
  new_instance->setFromJson(json);

  return new_instance;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Creates a new CJsonSerializer object
///
/// \returns IJSonSerializable* casted object newly created
///////////////////////////////////////////////////////////////////////////////
IJsonSerializable*
CJsonSerializer::createNewInstance() const {
  return new CJsonSerializer(m_typeName);
}

void
CJsonSerializer::write2json (Json::Value& v) const{
  // TODO
}

void
CJsonSerializer::setFromJson (const Json::Value& v) {
  // TODO
}
void
CJsonSerializer::destroy          (){

}
