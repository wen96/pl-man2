/* 
 * File:   MasterManAPI.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 9, 2013, 7:22 PM
 */

#include "MasterManAPI.h"
#include "Player.h"
#include "MasterMan.h"
#include "DataGen.h"

MasterManAPI* MasterManAPI::m_pInstance = NULL;

MasterManAPI::MasterManAPI()
{
    win = finish = false;
    lastID = 0;
}

MasterManAPI::MasterManAPI(const MasterManAPI& api)
{
    Copy(api);
}

MasterManAPI::~MasterManAPI()
{
    Destructor();
}

MasterManAPI&
        MasterManAPI::operator =(const MasterManAPI &api)
{
    Copy(api);
    return *this;
}

void
MasterManAPI::Destructor()
{
    //delete m_pInstance;
    m_pInstance = NULL;
    win = finish = false;

    for (unsigned int i = 0; i < entities.size(); i++)
    {
        if (entities[i] != NULL)
        {
            delete entities[i];
            entities[i] = NULL;
        }
    }

    for (unsigned int i = 0; i < world->size(); i++)
    {
        world[i].clear();
    }

    world->clear();
    if (world != NULL)
    {
        delete world;
    }

}

void
MasterManAPI::dispose()
{
    delete m_pInstance;
    m_pInstance = NULL;
}

void
MasterManAPI::Copy(const MasterManAPI &api)
{
    m_pInstance = api.m_pInstance;
    world = api.world;
    finish = api.finish;
    win = api.win;
    lastID = api.lastID;
}

MasterManAPI*
MasterManAPI::getInstance()
{

    if (m_pInstance == NULL)
    {
        m_pInstance = new MasterManAPI();
    }

    return m_pInstance;

}

vector<Entity *>
MasterManAPI::getEntity(int x, int y)
{

    vector<Entity *> entity;

    if (x >= 0 && x < width && y >= 0 && y <= height)
    {

        vector< vector < vector<Entity *> > > & ref = (*world);
        entity = ref[x][y];
    }

    return entity;

}

bool
MasterManAPI::isSolid(int x, int y)
{
    vector<Entity *> entities = getEntity(x, y);
    bool solid = false;

    for (unsigned int i = 0; i < entities.size() && !solid; i++)
    {
        if (entities[i] != NULL && entities[i]->getSolid())
        {
            solid = true;
        }
    }

    return solid;
}

bool
MasterManAPI::isSolid(int x, int y, Direction dir)
{
    return isSolid(getNextX(x, dir), getNextY(y, dir));
}

bool
MasterManAPI::isPlayer(int x, int y)
{
    vector<Entity *> entities = getEntity(x, y);
    bool is_player = false;

    for (unsigned int i = 0; i < entities.size() && !is_player; i++)
    {
        if (entities[i] != NULL && entities[i]->getType() == EntityPlayer)
        {
            is_player = true;
        }
    }

    return is_player;
}

bool
MasterManAPI::isPlayer(int x, int y, Direction dir)
{
    return isPlayer(getNextX(x, dir), getNextY(y, dir));
}

bool 
MasterManAPI::isType(int x, int y, EntityType type)
{
    vector<Entity *> entities = getEntity(x, y);
    bool is_type = false;

    for (unsigned int i = 0; i < entities.size() && !is_type; i++)
    {
        if (entities[i] != NULL && entities[i]->getType() == type)
        {
            is_type = true;
        }
    }

    return is_type;
}

bool 
MasterManAPI::isType(int x, int y, Direction direction, EntityType type)
{
    return isType(getNextX(x,direction), getNextY(y, direction), type);
}

void
MasterManAPI::killPlayer()
{
    player->setAlive(false);
    player->setUpdated(false);
}

void
MasterManAPI::setEntity(int x, int y, Entity *entity)
{

    if (x >= 0 && x < width && y >= 0 && y <= height)
    {
        vector< vector < vector<Entity *> > >& ref = (*world);
        if (entity != NULL)
        {
        	bool find = false;
            vector<Entity*>::iterator it;
            for (it = ref[entity->getX()][entity->getY()].begin(); it != ref[entity->getX()][entity->getY()].end(); ++it )
            {
                if((*it) == entity)
                {
                	find = true;
                	break;
                }

            }

            if(find)
            {
            	ref[entity->getX()][entity->getY()].erase(it);
            }
            else
            {
            	 entities.push_back(entity);
            }

            if(ref[x][y].size() == 1 && ref[x][y][0] == NULL)
            {
            	ref[x][y].pop_back();
            }
            ref[x][y].push_back(entity);
            entity->setX(x);
			entity->setY(y);
			entity->setAlive(true);
			entity->setUpdated(false);
        }
    }
}

vector<Entity *>
MasterManAPI::getEntity(int x, int y, Direction direction)
{
    return getEntity(getNextX(x, direction), getNextY(y, direction));
}

void
MasterManAPI::setEntity(int x, int y, Direction direction, Entity *entity)
{
    setEntity(getNextX(x, direction), getNextY(y, direction), entity);
}

int
MasterManAPI::getNextX(int x, Direction direction)
{
    int newX = x;
    switch (direction)
    {
        case Map::Left:
            newX = x - 1;
            break;
        case Map::Right:
            newX = x + 1;
            break;

        case Map::UpRight:
            newX = x + 1;
            break;

        case Map::UpLeft:
            newX = x - 1;
            break;

        case Map::DownRight:
            newX = x + 1;
            break;

        case Map::DownLeft:
            newX = x - 1;
            break;
        default:
            break;
    }

    return newX;
}

int
MasterManAPI::getNextY(int y, Direction direction)
{
    int newY = y;
    switch (direction)
    {
        case Map::Up:
            newY = y - 1;
            break;
        case Map::Down:
            newY = y + 1;
            break;

        case Map::UpRight:
            newY = y - 1;
            break;

        case Map::UpLeft:
            newY = y - 1;
            break;

        case Map::DownRight:
            newY = y + 1;
            break;

        case Map::DownLeft:
            newY = y + 1;
            break;
        default:
            break;
    }

    return newY;
}

int
MasterManAPI::getScore()
{
    int score = 0;
    if (player != NULL)
    {
        score = player->getPoints();
    }

    return score;
};

Entity *
MasterManAPI::getDataGen(int x, int y, Direction direction)
{
    vector<Entity *> entities = getEntity(getNextX(x, direction), getNextY(y, direction));

    Entity *gen = NULL;

    for (unsigned int i = 0; i < entities.size() && gen == NULL; i++)
    {
        if (entities[i] != NULL && entities[i]->getType() == EntityDataGen)
        {
            gen = entities[i];
        }
    }

    return gen;


}

void
MasterManAPI::deleteEntity(int x,int y, Direction dir, EntityType entity)
{
    deleteEntity(getNextX(x,dir), getNextY(y,dir), entity);
}

/*Entity *
MasterManAPI::getDataGen(int x, int y, Direction direction)
{
    vector<Entity *> entities = getEntity(getNextX(x, direction), getNextY(y, direction));

    Entity *gen = NULL;

    for (unsigned int i = 0; i < entities.size() && gen == NULL; i++)
    {
        if (entities[i] != NULL && entities[i]->getType() == EntityDataGen)
        {
            gen = entities[i];
        }
    }

    return gen;


}*/

Entity *
MasterManAPI::getEntityByPriority(int x, int y, Direction direction)
{
    vector<Entity *> entities = getEntity(x,y, direction);

    Entity *entity = NULL;
    if(entities.size() > 0)
    {
    	entity = entities[0];
    }
    for (unsigned int i = 0; i < entities.size(); i++)
    {
        if (entities[i] != NULL && entities[i]->getType() == EntityEnemy)
        {
        	entity = entities[i];
        	break;
        }
        else if (entities[i] != NULL && entities[i]->getType() == EntityDot)
        {
        	entity = entities[i];
        }
    }

    return entity;


}

void
MasterManAPI::deleteEntity(int x,int y, EntityType entity)
{
	vector< vector < vector<Entity *> > >& ref = (*world);
    std::vector<Entity*>::iterator it;
    
    for (it = ref[x][y].begin() ; it != ref[x][y].end(); ++it)
    {
            if((*it)->getType() == entity)
            {
                (*it)->setAlive(false);
                (*it)->setUpdated(false);
              break;
            }
    }

    ref[x][y].erase(it);
    //entities->erase(it);
}

void
MasterManAPI::removeEntity(Entity* entity)
{

    std::vector<Entity*>::iterator it;

    for (it = entities.begin() ; it != entities.end(); ++it)
    {
            if((*it)== entity)
            {
              break;
            }
    }

    entities.erase(it);
}

Entity*
MasterManAPI::getEntityByType(int x, int y, Direction direction, EntityType type)
{
	vector<Entity *> entities = getEntity(x,y, direction);

	    Entity *entity = NULL;

	    for (unsigned int i = 0; i < entities.size(); i++)
	    {
	        if (entities[i] != NULL && entities[i]->getType() == type)
	        {
	        	entity = entities[i];
	        	break;
	        }
	    }

	    return entity;
}
