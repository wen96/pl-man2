/* 
 * File:   Entity.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 7, 2013, 10:24 PM
 */

#include "Entity.h"
#include "MasterManAPI.h"

Entity::Entity() {
    x = y = 0;
    type = EntityNone;
    id = MasterManAPI::getInstance()->getNextID();
    updated = false;
    alive = true;
}

Entity::Entity(int _x, int _y) {

    x = _x;
    y = _y;
    id = MasterManAPI::getInstance()->getNextID();
    updated = false;
    alive = true;
}

Entity::Entity(int _x, int _y, EntityType _type) {

    x = _x;
    y = _y;
    type = _type;
    id = MasterManAPI::getInstance()->getNextID();
    updated = false;
    alive = true;
}

Entity::Entity(const Entity& entity) {
    Copy(entity);
}

Entity::~Entity() {
    Destructor();
}

Entity&
Entity::operator =(const Entity &entity)
{
    if(this != &entity)
    {
        Destructor();
        Copy(entity);
    }
    
    return *this;
}

void
Entity::Destructor()
{
    x = y = id = -1;
    type = EntityNone;
    alive = false;
}

void
Entity::Copy(const Entity &entity)
{
    x = entity.x;
    y = entity.y;
    type = entity.type;
    fixed = entity.fixed;
    solid = entity.solid;
    id = entity.id;
    updated = entity.updated;
    alive = entity.alive;
}

ostream&
operator<<(ostream& os, const Entity& entity) {
    switch (entity.getType()) {
        case EntityWall:
            os << "Wall";
            break;
        case EntityPlayer:
            os << "Player";
            break;
        case EntityEnemy:
            os << "Enemy";
            break;
        default:
            break;
    }

    return os;
}

