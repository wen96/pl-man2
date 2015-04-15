/* 
 * File:   Player.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 7, 2013, 10:30 PM
 */

#include "Player.h"
#include "Object.h"
#include "MasterManAPI.h"
#include "FireDoor.h"

Player::Player() : Character()
{
    points = 0;
    type = EntityPlayer;
    object = NULL;
}

Player::Player(int _x, int _y) : Character(_x, _y, EntityPlayer)
{
    points = 0;
    object = NULL;
}

Player::Player(const Player& player)
{
    Copy(player);
}

Player::~Player()
{
    Destructor();
}

void
Player::Copy(const Player& player)
{
    x = player.x;
    y = player.y;
    type = player.type;
    points = player.points;
    if(player.object != NULL)
    {
        object = new Object(*object);
    }
    else
    {
        object = NULL;
    }

}

void
Player::Destructor()
{
    x = y = -1;
    points = -1;
    
    if(object != NULL)
    {
        delete object;
        object = NULL;
    }
}

Player&
Player::operator=(const Player &player)
{
    if (this != &player)
    {
        Destructor();
        Copy(player);
    }

    return *this;
}

void
Player::move(Direction direction)
{
    updated = false;
    MasterManAPI *api = MasterManAPI::getInstance();
    
    if (!api->isSolid(x,y,direction))
    {
        if (api->isType(x,y,direction, EntityDot))
        {
            api->deleteEntity(x,y,direction, EntityDot);
            api->setEntity(x, y, direction, this);
            ((Player*)this)->addPoint();
            
        }
        else if (api->isType(x,y,direction, EntityFireDoor))
		{
        	Entity *door = api->getEntityByType(x,y,direction,EntityFireDoor);

        	if(door != NULL)
        	{
        		api->setEntity(x, y, direction, this);

        		if(((FireDoor*)door)->getMortal())
        		{
					api->setFinish(true);
					api->setWin(false);
        		}

        	}

		}
        else if (api->isType(x,y,direction, EntityExitDoor))
        {
            api->setEntity(x, y, direction, this);
            api->setFinish(true);
            api->setWin(true);
        }
        else
        {
            api->setEntity(x, y, direction, this);
        }
                

    }
}
