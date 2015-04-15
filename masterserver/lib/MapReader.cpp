/* 
 * File:   MapReader.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on December 26, 2013, 6:34 PM
 */

#include "MapReader.h"
#include "Entity.h"
#include "Wall.h"
#include "Player.h"
#include "Barredor.h"
#include "FireDoor.h"
#include "ExitDoor.h"
#include "Dot.h"
#include "Gun.h"
#include "MasterManAPI.h"
#include <jsoncpp/json/json.h>
#include <fstream>
#include <vector>

MapReader::MapReader()
{
}

MapReader::MapReader(const MapReader& orig)
{
}

MapReader::~MapReader()
{
}

void
MapReader::ReadMap(string filename)
{

    
    ifstream file;
    string str;
    string json_str;

    file.open(filename.c_str(), ios::in);
    while (std::getline(file, str))
    {
        json_str += str;
        json_str.push_back('\n');
    }

    Json::Value jv;
    Json::Reader reader;

    // Parse Json String
    if (!reader.parse(json_str, jv))
        throw "Parse Exception: An error ocurred while parsing a json string.";

    int w = jv.get("width", "").asInt();
    int h = jv.get("height", "").asInt();


    //cout << "H: " << h << endl;
    //cout << "W: " << w << endl;

    vector<vector<vector<Entity*> > >*world = new vector<vector<vector<Entity*> > >();

    for (int x = 0; x < w; x++)
    {
        vector<vector<Entity *> > row;

        for (int y = 0; y < h; y++)
        {
            vector<Entity *> column;
            row.push_back(column);
        }

        world->push_back(row);
    }

    MasterManAPI *api = MasterManAPI::getInstance();

    Json::Value layers = jv.get("layers", "");
    Json::Value entities = layers[0].get("data","");
    
    
    for (unsigned i = 0; i < entities.size(); i++)
    {
        //world.push_back(createObjectFromJson(entities[i]) );
        int y = (i / w);
        int x = (i % w);

        Entity *entity;
        switch (entities[i].asInt()-1)
        {
            case EntityNone:
                entity = NULL;
                break;
            case EntityWall:
                entity = new Wall(x, y);
                break;
            case EntityPlayer:
                //cout << "Set Player" << endl;
                entity = new Player(x, y);
                api->setPlayer((Player*) entity);
                break;
            case EntityEnemy:
                entity = new Barredor(x, y, Left);
                break;
            case EntityFireDoor:
                entity = new FireDoor(x, y, 5, -3, 3, NULL);
                break;
            case EntityExitDoor:
                entity = new ExitDoor(x, y);
                break;
            case EntityDataGen:
                entity = new DataGen(x, y, 5, -3, 3);
                break;
            case EntityDot:
                entity = new Dot(x, y);
                break;
            case EntityGun:
                entity = new Gun(x, y);
                break;
            default:
                entity = NULL;
                break;
        }
        (*world)[x][y].push_back(entity);

    }


    /*for (int x = 0; x < h; x++)
    {

        for (int y = 0; y < w; y++)
        {
            if (world[x][y] != NULL)
            {
                switch (world[x][y]->getType())
                {
                    case EntityNone:
                        cout << " ";
                        break;
                    case EntityWall:
                        cout << "#";
                        break;
                    case EntityPlayer:
                        cout << "@";
                        break;
                    case EntityEnemy:
                        cout << "E";
                        break;
                    case EntityFireDoor:
                        cout << "F";
                        break;
                    case EntityExitDoor:
                        cout << "!";
                        break;
                    case EntityDataGen:
                        cout << "?";
                        break;
                    case EntityDot:
                        cout << ".";
                        break;
                    case EntityGun:
                        cout << "l";
                        break;
                    default:
                        cout << "-";
                        break;
                }
            }
            else
            {
                cout << " ";
            }
        }

        cout << endl;
    }*/
    
    api->setWidth(w);
    api->setHeight(h);
    api->setWorld(world);
}


