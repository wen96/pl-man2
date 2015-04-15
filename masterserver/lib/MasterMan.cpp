/*
 * MasterMan.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 */

#include "MasterMan.h"
#include "Dot.h"
#include "Barredor.h"
#include "Wall.h"
#include "ExitDoor.h"
#include "Gun.h"
#include "FireDoor.h"
#include "DataGen.h"
#include "MapReader.h"
#include <sstream>

MasterMan::MasterMan(string _map) {

	map = _map;
	MapReader reader;
	reader.ReadMap(map);

	api = MasterManAPI::getInstance();
	player = api->getPlayer();

}

MasterMan::~MasterMan() {

	Destructor();
}

MasterMan::MasterMan(const MasterMan &masterMan)
{
	Copy(masterMan);
}

MasterMan&
MasterMan::operator =(const MasterMan &masterMan)
{
	if(this != &masterMan)
	{
		Destructor();
		Copy(masterMan);
	}

	return *this;
}

void
MasterMan::Copy(const MasterMan &masterMan)
{
	player = new Player(*(masterMan.player));
	api = masterMan.api;
}

string 
MasterMan::init()
{
	api->dispose();

	MapReader reader;
	reader.ReadMap(map);

	api = MasterManAPI::getInstance();
	player = api->getPlayer();

	return getWorld();
}

void
MasterMan::Destructor()
{
	api->dispose();
}

string
MasterMan::drawWorld() {
	string map = "";
	/*string map = "";

    for (int y = 0; y < WorldSizeY; y++) {
        for (int x = 0; x < WorldSizeX; x++) {
            if (world[x][y] == NULL) {
                map += " ";
            } else if (world[x][y]->getType() == EntityWall) {
                map += "#";
            } else if (world[x][y]->getType() == EntityPlayer) {
                map += "@";
            }
            else if (world[x][y]->getType() == EntityEnemy) {
                map += "E";
            }
            else if (world[x][y]->getType() == EntityDot) {
                map += ".";
            }
            else if (world[x][y]->getType() == EntityExitDoor) {
                map += "=";
            }
            else if (world[x][y]->getType() == EntityFireDoor) {

                if(((FireDoor*)world[x][y])->getMortal())
                {
                        map += "*";
                }
                else
                {
                    map += "O";
                }
            }
            else if (world[x][y]->getType() == EntityDataGen) {
                map += "?";
            }
            else if (world[x][y]->getType() == EntityExitDoor) {
                map += "=";
            }

        }

        map += "\n";
    }

	 */

	return map;
}

void
MasterMan::UpdateWorld() {


	for(unsigned int i = 0; i < api->getEntities().size(); i++)
	{
		if(api->getEntities()[i] != NULL)
		{
			if(api->getEntities()[i]->Update())
			{
				return;
			}
		}
	}
}

string
MasterMan::move(Direction direction) {

	if(!api->getFinish())
	{
		if(direction != None)
		{
			player->move(direction);
		}
		UpdateWorld();
	}


	return getWorld();
}

string
MasterMan::see(Direction direction) {

	if(!api->getFinish())
	{
		//vector<Entity*> entities = api->getEntity(player->getX(), player->getY(), direction);
		Entity* entity = api->getEntityByPriority(player->getX(), player->getY(), direction);
		VisualEntity *vEntity;
		if (entity != NULL){
			vEntity = new VisualEntity(entity->getType(), entity->getX(), entity->getY(), entity->getID(), entity->getAlive());
			if(entity->getType() == EntityFireDoor)
			{
				bool active = ((FireDoor*)entity)->getMortal();

				if(active)
				{
					vEntity->addAttribute("mortal","true");
				}
				else
				{
					vEntity->addAttribute("mortal","false");
				}

			}
			else if(entity->getType() == EntityDataGen)
			{
				stringstream str;
				str.clear();
				vector<float> numbers = ((DataGen*)entity)->getData();

				for(unsigned int j = 0; j < numbers.size(); j++)
				{
					str << numbers[j];

					if(j < numbers.size() - 1)
					{
						str << ";";
					}
				}
				vEntity->addAttribute("numbers", str.str());
			}
		}
		else
		{
			vEntity = new VisualEntity(EntityNone, api->getNextX(player->getX(), direction), api->getNextY(player->getY(), direction), -1, false);
		}
		return vEntity->json_serialize();
	}
	else
	{
		return getWorld();
	}
}



string
MasterMan::interact(Direction direction)
{
	if(!api->getFinish())
	{
		/*Entity *entity = api->getEntity(player->getX(), player->getY(), direction);

	if(entity != NULL)
	{
		Object* object =  dynamic_cast<Object*> (entity);

		if(object != NULL)
		{
			object->Use(direction);
		}
	}

	UpdateWorld();*/
		return getWorld();
	}
	else
	{
		return getWorld();
	}
}

string
MasterMan::use(Direction direction)
{
	if(!api->getFinish())
	{
		Object* object =  player->getObject();

		if(object != NULL)
		{
			object->Use(direction);
		}

		UpdateWorld();
	}
	return getWorld();
}

string
MasterMan::take(Direction direction)
{
	//cout << "TAKE: " << direction << endl;
	if(!api->getFinish())
	{
		std::vector<Entity *> entity = api->getEntity(player->getX(), player->getY(),direction);


		for(unsigned int i = 0; i < entity.size(); i++)
		{
			Object* object =  dynamic_cast<Object*> (entity[i]);

			if(object != NULL)
			{

				player->setObject(object);
				api->deleteEntity(player->getX(), player->getY(),direction, object->getType());

				break;
			}
		}
		player->setUpdated(false);
		UpdateWorld();
	}
	return getWorld();
}

string
MasterMan::put(Direction direction)
{
	if(!api->getFinish())
	{
		Object* object =  player->getObject();

		if(object != NULL)
		{
			//cout << "Objeto a dejar: " << endl;
			if(!api->isSolid(player->getX(), player->getY(), direction))
			{
				//cout << "No es solido a dejar: " << endl;
				api->setEntity(player->getX(), player->getY(), direction, object);
				player->setObject(NULL);
			}

		}

		UpdateWorld();
	}
	return getWorld();
}


string 
MasterMan::getWorld()
{
	MasterManAPI *api = MasterManAPI::getInstance();

	VisualMap *map = new VisualMap(api->getWidth(), api->getHeight(), api->getFinish(), api->getWin(), api->getScore());
	vector<Entity*> deads;

	vector<Entity*> entities = api->getEntities();

	for(unsigned int i = 0; i < entities.size(); i++)
	{
		if(entities[i] != NULL)
		{
			if(!entities[i]->getUpdated())
			{
				VisualEntity *vEntity = new VisualEntity(entities[i]->getType(), entities[i]->getX(),
						entities[i]->getY(), entities[i]->getID(),
						entities[i]->getAlive());

				if(entities[i]->getType() == EntityFireDoor)
				{
					bool active = ((FireDoor*)entities[i])->getMortal();

					if(active)
					{
						vEntity->addAttribute("mortal","true");
					}
					else
					{
						vEntity->addAttribute("mortal","false");
					}

				}
				else if(entities[i]->getType() == EntityDataGen)
				{
					stringstream str;
					str.clear();
					vector<float> numbers = ((DataGen*)entities[i])->getData();

					for(unsigned int j = 0; j < numbers.size(); j++)
					{
						str << numbers[j];

						if(j < numbers.size() - 1)
						{
							str << ";";
						}
					}
					vEntity->addAttribute("numbers", str.str());
				}

				//cout << "E: " << entities[i]->getType() << " A: " <<entities[i]->getAlive() << " X: " << entities[i]->getX() << " Y: " << entities[i]->getY() << " ID: " << entities[i]->getID() << endl;
 				map->addEntity(vEntity);

				if(!entities[i]->getAlive())
				{
					deads.push_back(entities[i]);
				}
			}
		}
		else
		{
		}
	}
	//Para no eliminar el objeto del player
	Entity* playerObject = player->getObject();
	for(unsigned int i = 0; i < deads.size(); i++)
	{
		if(deads[i] != NULL && playerObject != deads[i])
		{
			api->removeEntity(deads[i]);
			delete deads[i];
			deads[i] = NULL;
		}
	}


	string serielize = map->json_serialize();

	if(map != NULL)
	{
		delete map;
		map = NULL;
	}

	deads.clear();

	return serielize;
}
