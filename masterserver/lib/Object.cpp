/* 
 * File:   Object.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 7, 2013, 10:26 PM
 */

#include "Object.h"

Object::Object()
{
}

Object::Object(int _x, int _y) : Entity(_x, _y)
{
}

Object::Object(const Object& object)
{
    Copiar(object);
}

Object::~Object()
{
    Destructor();
}

void
Object::Copiar(const Object &object)
{
    x = object.x;
    y = object.y;
    type = object.type;
    solid = object.solid;
    fixed = object.fixed;
}

void 
Object::Destructor()
{
    
}
void
Object::Use(Direction direction)
{
    
}

