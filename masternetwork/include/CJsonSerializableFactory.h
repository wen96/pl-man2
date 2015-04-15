#pragma once

#include <boost/function.hpp>
#include <string>
#include <map>
#include "CVisualEntity.h"
#include "CVisualMap.h"

class IJsonSerializable;

class CJsonSerializableFactory
{
public:
  // Method types
  typedef boost::function< IJsonSerializable*() > TMethod;
  typedef std::map< std::string, TMethod > TMethodTable;

  static CJsonSerializableFactory& get();

  // Factory Methods
  IJsonSerializable* create(std::string type);
  IJsonSerializable* createCJsonCommand();
  IJsonSerializable* createCJsonCustomData();
  IJsonSerializable* createCJsonVisualEntity();
  IJsonSerializable* createCJsonVisualMap();
private:
  CJsonSerializableFactory();

  TMethodTable m_methodTable;  //! Actual method table to call methods for each command
};

// Macro for easy access to the Singleton
#define CJSFACT CJsonSerializableFactory::get()

