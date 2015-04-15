/* 
 * File:   Gun.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 10, 2013, 5:54 PM
 */

#include "Gun.h"
#include "MasterManAPI.h"
#include "Player.h"
#include "Character.h"
#include "Barredor.h"

Gun::Gun() : Object()
{
    type = EntityGun;
}

Gun::Gun(int _x, int _y) : Object(_x, _y)
{
    type = EntityGun;
}

Gun::Gun(const Gun &gun) : Object(gun)
{
    Copy(gun);
}

Gun::~Gun()
{
    Destructor();
}

Gun&
Gun::operator =(const Gun &gun)
{
    if(this != &gun)
    {
        Destructor();
        Copy(gun);
    }
    
    return *this;
}

void 
Gun::Copy(const Gun &gun)
{
    x = gun.x;
    y = gun.y;
    solid = gun.solid;
    fixed = gun.fixed;
    type = gun.type;
}

void
Gun::Destructor()
{
    x = y = -1;
    type = EntityNone;
    solid = fixed = false;
}

void 
Gun::Use(Direction direction)
{
    MasterManAPI *api = MasterManAPI::getInstance();
    
    int traX, traY;
    traX = api->getPlayer()->getX();
    traY = api->getPlayer()->getY();
    
    bool collision = false; 
    do
    {
        if(api->isSolid(traX,traY,direction))
        {
            if(api->isType(traX,traY,direction,EntityEnemy))
            {
                api->deleteEntity(traX,traY,direction,EntityEnemy);
            }
            
            collision = true;
        }
        else
        {
           traX = api->getNextX(traX, direction);
           traY = api->getNextY(traY, direction);
        }
        
        
    }while(!collision);
    
    
}
