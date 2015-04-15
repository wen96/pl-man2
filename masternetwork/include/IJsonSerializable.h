#pragma once

// Forward declarations
namespace Json {
  class Value;
}

class IJsonSerializable
{
public:
  // Interface inheritance
  virtual void                write2json       (Json::Value& v) const = 0;
  virtual void                setFromJson      (const Json::Value& v) = 0;
  virtual IJsonSerializable*  createNewInstance() const = 0;
  virtual void                destroy          () = 0;
  virtual ~IJsonSerializable(){};
  // TODO: dispose method
};

