/* 
 * File:   Wall.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 10, 2013, 2:50 AM
 */

#include "Wall.h"

Wall::Wall()
{
    fixed = true;
    solid = true;
    type = EntityWall;
}

Wall::Wall(int _x, int _y) : Object(_x, _y)
{
    fixed = true;
    solid = true;
    type = EntityWall;
}
Wall::Wall(const Wall& wall)
{
    Copy(wall);
}

Wall::~Wall()
{
    Destructor();
}

Wall&
Wall::operator =(const Wall &wall)
{
    if(this != &wall)
    {
        Destructor();
        Copy(wall);
    }
    
    return *this;
}

void
Wall::Copy(const Wall &wall)
{
    fixed = wall.fixed;
    solid = wall.solid;
    type = wall.type;
    x = wall.x;
    y = wall.y;
}

void
Wall::Destructor()
{
    x = y = -1;
    type = EntityNone;
}
