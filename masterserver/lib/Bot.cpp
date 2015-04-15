/* 
 * File:   Bot.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 7, 2013, 10:32 PM
 */

#include "Bot.h"

Bot::Bot() : Character()
{
}

Bot::Bot(int _x, int _y) : Character(_x, _y, EntityEnemy)
{
}

Bot::Bot(const Bot& bot)
{
    Copy(bot);
}

Bot::~Bot()
{
    Destructor();
}

Bot&
Bot::operator =(const Bot &bot)
{
    if(this != &bot)
    {
        Destructor();
        Copy(bot);
    }
    
    return *this;
}

void
Bot::Copy(const Bot &bot)
{
    x = bot.x;
    y = bot.y;
    type = bot.type;
}

void
Bot::Destructor()
{
    x = y = -1;
    type = EntityNone;
}



