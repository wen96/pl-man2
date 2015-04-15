/* 
 * File:   Character.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 7, 2013, 10:29 PM
 */

#include <unistd.h>

#include "Character.h"
#include "MasterManAPI.h"
Character::Character() : Entity()
{
    solid = true;
    fixed = false;
}

Character::Character(int _x, int _y, EntityType _type) : Entity(_x, _y, _type)
{
    solid = true;
    fixed = false;
}

Character::Character(const Character& character)
{
    Copy(character);
}

Character::~Character()
{
    Destructor();
}

void
Character::Copy(const Character &character)
{
    x = character.x;
    y = character.y;
    type = character.type;
    solid = character.solid;
    fixed = character.fixed;

}

void
Character::Destructor()
{
    x = y = -1;
    type = EntityNone;
}

Character&
Character::operator =(const Character &character)
{
    if (this != &character)
    {
        Destructor();
        Copy(character);
    }

    return *this;
}

void
Character::move(Direction direction)
{
    
    
    MasterManAPI *api = MasterManAPI::getInstance();

    vector<Entity *> next = api->getEntity(x, y, direction);
    if (!api->isSolid(x,y,direction))
    {
        api->setEntity(x, y, direction, this);
    }
    else if(api->isPlayer(x,y,direction))
    {
        api->setEntity(x, y, direction, this);
        api->setFinish(true);
        api->setWin(false);
        api->killPlayer();
    }
}
