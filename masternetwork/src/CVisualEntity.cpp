/* 
 * File:   VisualEntity.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 10, 2013, 7:51 PM
 */

#include "CVisualEntity.h"

#include "CJsonSerializer.h"
#include "CJsonCommand.h"
#include "CJsonCustomData.h"
#include <jsoncpp/json/json.h>

VisualEntity::VisualEntity() : CJsonSerializer("visual_entity") {
	m_typeName = "visual_entity";
	entity = x = y = id = -1;
	alive = false;

}

VisualEntity::VisualEntity(int _entity, int _x, int _y, int _id, bool _alive) : CJsonSerializer("visual_entity") {
	m_typeName = "visual_entity";
	entity = _entity;
	x = _x;
	y = _y;
	id = _id;
	alive = _alive;
}


VisualEntity::~VisualEntity()
{
	entity = x = y = id = -1;
	for (unsigned i=0; i < m_attibutes.size(); i++){
		delete m_attibutes[i];
	}
}

IJsonSerializable*
VisualEntity::createNewInstance() const {
	return new VisualEntity();
}

void
VisualEntity::write2json (Json::Value& v) const{

	Json::Value dataVector(Json::arrayValue);
	v["type"]    = "visual_entity";

	v["typeEntity"]    = entity;
	v["x"]    = x;
	v["y"]    = y;
	v["id"]    = id;
	v["alive"]    = alive;


	// JSON Parameters value
	if (m_attibutes.size() > 0 ) {
		for(unsigned i=0; i < m_attibutes.size(); i++) {
			Json::Value pv;
			m_attibutes[i]->write2json(pv);
			dataVector.append( pv );
		}

		v["attributes"] = dataVector;
	}

	//cout << "JSON VALUE: " << v.toStyledString() << endl;

}

void
VisualEntity::setFromJson (const Json::Value& json) {

	entity = json.get("typeEntity", "").asInt();
	x = json.get("x", "").asInt();
	y = json.get("y", "").asInt();
	id = json.get("id", "").asInt();
	alive = json.get("alive", "").asBool();

	Json::Value paramArray = json["attributes"];
	for (unsigned i=0; i < paramArray.size(); i++) {
		cJsonCustomData *data = (cJsonCustomData*)createObjectFromJson(paramArray[i]);
		addAttribute( data->getKey(), data->getValue() );
		//cout << " Añado: " << data->getKey() << data->getValue() << endl;
		if (data) delete data;
	}
}
void
VisualEntity::destroy          (){

	entity = x = y = id = -1;

}

void
VisualEntity::addAttribute(string key, string value)
{
	m_attibutes.push_back(new cJsonCustomData(key, value));
}

string
VisualEntity::getValue(string key)
{
	string value = "";
	for(unsigned i=0; i < m_attibutes.size(); i++) {
		if(((cJsonCustomData*)m_attibutes[i])->getKey() == key)
		{
			value = ((cJsonCustomData*)m_attibutes[i])->getValue();
			break;
		}
	}

	return value;
}
