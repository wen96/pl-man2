/* 
 * File:   Barredor.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 9, 2013, 1:25 PM
 */

#include "Barredor.h"

Barredor::Barredor()
{
}

Barredor::Barredor(int _x, int _y, Direction _direction)
: Bot(_x, _y)
{
    type = EntityEnemy;
    direction = _direction;
}

Barredor::Barredor(const Barredor& barredor)
{
    Copy(barredor);
}

Barredor::~Barredor()
{
    Destructor();
}

void
Barredor::Copy(const Barredor &barredor)
{
    x = barredor.x;
    y = barredor.y;
    type = barredor.type;
    direction = barredor.direction;
}

void
Barredor::Destructor()
{
    x = y = -1;
    type = EntityNone;
    direction = Up;
}

bool
Barredor::Update()
{
    updated = false;
    if (alive)
    {
        MasterManAPI *api = MasterManAPI::getInstance();

        if (!api->isSolid(x,y,direction))
        {
            move(direction);
        } 
        else if (api->isPlayer(x,y,direction))
        {
            api->setFinish(true);
            api->setWin(false);
            api->killPlayer();
            move(direction);
            
            return true;
        } 
        else
        {
            switch (direction)
            {
                case Up:
                    direction = Down;
                    break;
                case Down:
                    direction = Up;
                    break;
                case Left:
                    direction = Right;
                    break;
                case Right:
                    direction = Left;
                    break;
                default:
                    break;
            }

            move(direction);

        }
    }


    return false;
}

