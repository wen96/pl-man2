/* 
 * File:   ExitDoor.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 10, 2013, 3:40 AM
 */

#include "ExitDoor.h"

ExitDoor::ExitDoor() : Object()
{
    solid = false;
    fixed = true;
    type = EntityExitDoor;
}

ExitDoor::ExitDoor(int _x, int _y) : Object(_x, _y)
{
    solid = false;
    fixed = true;
    type = EntityExitDoor;
}

ExitDoor::ExitDoor(const ExitDoor &door)
{
    Copy(door);
}

ExitDoor::~ExitDoor()
{
    Destructor();
}

ExitDoor&
ExitDoor::operator =(const ExitDoor &door)
{
    if(this != &door)
    {
        Destructor();
        Copy(door);
    }
    
    return *this;
}

void
ExitDoor::Copy(const ExitDoor &door)
{
    x = door.x;
    y = door.y;
    type = door.type;
    solid = door.solid;
    fixed = door.fixed;
}

void
ExitDoor::Destructor()
{
    x = y = -1;
    type = EntityNone;
}