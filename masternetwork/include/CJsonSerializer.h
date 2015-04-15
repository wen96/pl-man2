#pragma once

#include "IJsonSerializable.h"
#include <map>
#include <string>

class CJsonSerializer : public IJsonSerializable
{
public:
  /// Map relating names of types with a pointer to an object of that type (casted to IJsonSerializable*)
  typedef std::map< std::string, const CJsonSerializer* > TString2JsonMap;

  explicit CJsonSerializer(std::string typeName);
  virtual ~CJsonSerializer();

  // Inheritable Implementation
  std::string                 json_serialize   () const;
  IJsonSerializable*          json_deserialize (const std::string& json_str) const;
  IJsonSerializable*          createObjectFromJson(const Json::Value& v) const;
  std::string                 typeName         () const { return m_typeName; }

  // Interface inherited
  virtual void                write2json       (Json::Value& v) const;
  virtual void                setFromJson      (const Json::Value& v);
  virtual IJsonSerializable*  createNewInstance() const;
  virtual void                destroy          ();

protected:
  std::string m_typeName;                      //< Name of the type
};

