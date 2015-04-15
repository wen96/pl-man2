
#include "CJsonCustomData.h"
#include <jsoncpp/json/json.h>

cJsonCustomData::cJsonCustomData()
: CJsonSerializer("custom_data"){
	m_key = "key";
	m_value = "value";
}
cJsonCustomData::cJsonCustomData(std::string _key, std::string _value)
: CJsonSerializer("custom_data"){
	m_key = _key;
	m_value = _value;
}

cJsonCustomData::~cJsonCustomData() {
	m_key = "";
	m_value = "";
}

void cJsonCustomData::write2json(Json::Value& v) const {
	// JSON Command value
	v["type"]    = "custom_data";
	v["key"] = m_key;
	v["value"] = m_value;

}

void cJsonCustomData::setFromJson(const Json::Value& json) {
	// Check that we actually receive a command
	if(json.get("type", "").asString().compare("custom_data") != 0)
		throw "Exception: Trying to deserialize a non-custom_data as a custom_data";
	m_key = json.get("key", "").asString();
	m_value = json.get("value", "").asString();
}

IJsonSerializable* cJsonCustomData::createNewInstance() const {
	return new cJsonCustomData();
}

void cJsonCustomData::destroy() {
	m_key = "";
	m_value = "";
	delete this;
}

const std::string& cJsonCustomData::getKey() const {
	return m_key;
}

void cJsonCustomData::setKey(const std::string& key) {
	m_key = key;
}

const std::string& cJsonCustomData::getValue() const {
	return m_value;
}



void cJsonCustomData::setValue(const std::string& value) {
	m_value = value;
}
