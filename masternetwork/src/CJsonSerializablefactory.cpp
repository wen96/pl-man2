#include "CJsonSerializableFactory.h"
#include "CJsonCommand.h"
#include "CJsonCustomData.h"
#include <boost/bind.hpp>



///////////////////////////////////////////////////////////////////////////////
/// \brief Constructor of CJsonSerializableFactory
///////////////////////////////////////////////////////////////////////////////
CJsonSerializableFactory::CJsonSerializableFactory() {
  m_methodTable["command"] = boost::bind(&CJsonSerializableFactory::createCJsonCommand, *this);
  //No si si esto es para conseguir un puntero al tipo de entidad que es u otra cosa. Si es otra cosa
  //aqui bajo lo unico que estoy haciendo es liarla
  m_methodTable["visual_number"] = boost::bind(&CJsonSerializableFactory::createCJsonVisualEntity, *this);
  m_methodTable["visual_numbers"] = boost::bind(&CJsonSerializableFactory::createCJsonVisualEntity, *this);
  m_methodTable["visual_boolean"] = boost::bind(&CJsonSerializableFactory::createCJsonVisualEntity, *this);
  m_methodTable["visual_entity"] = boost::bind(&CJsonSerializableFactory::createCJsonVisualEntity, *this);
  m_methodTable["visual_map"] = boost::bind(&CJsonSerializableFactory::createCJsonVisualMap, *this);
  m_methodTable["custom_data"] = boost::bind(&CJsonSerializableFactory::createCJsonCustomData, *this);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Returns a reference to the singleton object CJsonSerializable
///////////////////////////////////////////////////////////////////////////////
CJsonSerializableFactory&
CJsonSerializableFactory::get() {
  static CJsonSerializableFactory j;
  return j;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Creates a IJsonSerializable object from a concrete class
///
/// \param type Type of the object to be created
/// \returns Pointer to a new CCommand
///////////////////////////////////////////////////////////////////////////////
IJsonSerializable*
CJsonSerializableFactory::create(std::string type) {
  // Check if the type is registered in the method table
  if (m_methodTable.count(type) == 0)
    throw "Exception: trying to create an object of a non registered class";

  // Call the appropriate production method
  return m_methodTable[type]();
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Creates a new CJsonCommand and returns the pointer
///
/// \returns Pointer to a new CCommand
///////////////////////////////////////////////////////////////////////////////
IJsonSerializable*
CJsonSerializableFactory::createCJsonCommand() {
  return new CJsonCommand();
}

//---------------- No estoy nada seguro de que esto deba existir
IJsonSerializable*
CJsonSerializableFactory::createCJsonVisualEntity() {
  return new VisualEntity();
}

IJsonSerializable*
CJsonSerializableFactory::createCJsonVisualMap() {
  return new VisualMap();
}
IJsonSerializable*
CJsonSerializableFactory::createCJsonCustomData() {
	return new cJsonCustomData();
}
//-------------------------------------------------------
