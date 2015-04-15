#pragma once

#include <vector>
#include "CJsonSerializer.h"

using namespace std;

class VisualEntity : public CJsonSerializer  {
public:
    VisualEntity();
    VisualEntity(int, int, int, int, bool);
    VisualEntity(const VisualEntity& orig);
    virtual ~VisualEntity();
    
    virtual void                write2json       (Json::Value& v) const;
    virtual void                setFromJson      (const Json::Value& v);
    virtual IJsonSerializable*  createNewInstance() const;
    virtual void                destroy          ();
    int getType() {return entity;};
    int getX() {return x;};
    int getY() {return y;};
    int getID() {return id;};
    vector< IJsonSerializable* > getAttributes() {return m_attibutes;};
    bool getAlive() {return alive;};
    void addAttribute(std::string, std::string);
    std::string getValue(std::string key);
    void addAttribute(IJsonSerializable* p)
    {
        m_attibutes.push_back(p);
    }
    
private:
    int entity;
    int x;
    int y;
    int id;
    bool alive;
    vector< IJsonSerializable* >   m_attibutes;     //< List of parameters for this command

};

