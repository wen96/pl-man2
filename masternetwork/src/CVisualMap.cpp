/* 
 * File:   VisualMap.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 9, 2013, 9:45 PM
 */

#include "CVisualMap.h"

#include "CJsonSerializer.h"
#include "CJsonCommand.h"
#include <jsoncpp/json/json.h>

VisualMap::VisualMap() : CJsonSerializer("visual_map")
{
	width = 0;
	height = 0;
        score = 0;
	finish = win = false;
	m_typeName = "visual_map";
}

VisualMap::VisualMap(int _width, int _height, vector<vector<int> > _world) : CJsonSerializer("visual_map")
{
	width = _width;
	height = _height;
        score = 0;
	finish = win = false;
        

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			world.push_back(new VisualEntity(_world[x][y],-1,-1,-1, true));
		}
	}
}

VisualMap::VisualMap(int _width, int _height) : CJsonSerializer("visual_map")
{
	width = _width;
	height = _height;
        score = 0;
	finish = win = false;
}

VisualMap::VisualMap(int _width, int _height, bool _finish, bool _win,  int _score) : CJsonSerializer("visual_map")
{
	width = _width;
	height = _height;
	finish = _finish;
	win = _win;
        score = _score;
}


VisualMap::VisualMap(const VisualMap &map) : CJsonSerializer("visual_map")
{
	Copy(map);
}

VisualMap::~VisualMap()
{
	Destructor();
}

IJsonSerializable*
VisualMap::createNewInstance() const
{
	return new VisualMap();
}

void
VisualMap::write2json(Json::Value& v) const
{
	Json::Value dataVector(Json::arrayValue);
	v["type"] = "visual_map";
	v["width"] = width;
	v["height"] = height;

	v["finish"] = finish;
	v["win"] = win;
        v["score"] = score;

	for(unsigned i=0; i < world.size(); i++) {
		Json::Value pv;
		world[i]->write2json(pv);
		dataVector.append( pv );
	}

	v["data"] = dataVector;



}

void
VisualMap::setFromJson(const Json::Value& json)
{

	this->width  = json.get("width", "").asInt();
	this->height  = json.get("height", "").asInt();
        this->score  = json.get("score", "").asInt();
        
	this->finish  = json.get("finish", "").asBool();
	this->win  = json.get("win", "").asBool();

	Json::Value entities = json["data"];
	for (unsigned i=0; i < entities.size(); i++) {
		world.push_back(createObjectFromJson(entities[i]) );
	}
}

void
VisualMap::destroy()
{
	Destructor();
}

void 
VisualMap::Copy(const VisualMap &map)
{
	m_typeName = "visual_map";
	height = map.height;
	width = map.width;
        score = map.score;

	world.clear();
	for(unsigned i=0; i < map.world.size(); i++) {
		world.push_back(map.world[i]);
	}
}

void
VisualMap::Destructor()
{
	height = -1;
	width = -1;
        score = -1;
	for(unsigned i=0; i < world.size(); i++) {
		delete world[i];
		world[i] = NULL;
	}
	world.clear();
}

VisualMap& 
VisualMap::operator =(const VisualMap &map)
{
	if(this != &map)
	{
		Destructor();
		Copy(map);
	}

	return *this;
}
