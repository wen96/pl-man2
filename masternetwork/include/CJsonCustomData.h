#pragma once

#include "CJsonSerializer.h"
#include <string>

/**
 * Clase para crear mensajes con el servidor del tipo clave valor que deseemos
 */
class cJsonCustomData: public CJsonSerializer {
public:
	cJsonCustomData();
	cJsonCustomData(std::string _key, std::string _value);

	// Virtual Methods ----------------------------------------------
	virtual ~cJsonCustomData();
	virtual void                write2json       (Json::Value& json) const;
	virtual void                setFromJson      (const Json::Value& v);
	virtual IJsonSerializable*  createNewInstance() const;
	virtual void                destroy          ();

	// getters and setters
	const std::string& getKey() const;
	void setKey(const std::string& key);
	const std::string& getValue() const;
	void setValue(const std::string& value);

private:
	std::string m_key;
	std::string m_value;
};

