/* 
 * File:   Dot.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 10, 2013, 2:42 AM
 */

#include "Dot.h"

Dot::Dot() : Object()
{
    solid = false;
    fixed = false;
    type = EntityDot;
}

Dot::Dot(int _x, int _y) : Object(_x, _y)
{
    solid = false;
    fixed = false;
    type = EntityDot;
}

Dot::Dot(const Dot& dot)
{
    Copy(dot);
}

Dot::~Dot()
{
    Destructor();
}

Dot&
Dot::operator =(const Dot &dot)
{
    if(this != &dot)
    {
        Destructor();
        Copy(dot);
    }
    
    return *this;
}

void
Dot::Copy(const Dot &dot)
{
    x = dot.x;
    y = dot.y;
    type = dot.type;
    fixed = dot.fixed;
    solid = dot.solid;
}

void
Dot::Destructor()
{
    x = y = -1;
    type = EntityNone;
}
