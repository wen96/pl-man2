/* 
 * File:   FireDoor.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 11, 2013, 7:53 PM
 */

#include "FireDoor.h"
#include "MasterManAPI.h"
#include "Entity.h"
#include "MasterMan.h"
#include <stdlib.h> 
#include <time.h>    
#include <cmath> 

FireDoor::FireDoor() : Object()
{
    solid = false;
    fixed = true;
    type = EntityFireDoor;
}

FireDoor::FireDoor(int _x,int _y, int numbers, int min, int max, DataGen * _gen) : Object(_x, _y)
{
    gen = _gen;
    
    srand(time(NULL));
    int range = max - min;
    //cout << "Puerta: ";
    for(int i = 0; i < numbers; i++)
    {
        
        float number = ((rand()%(range*100))/100.0)+min;
        //cout << number << ", ";
        weights.push_back(number);
    }
    //cout << endl;
    type = EntityFireDoor;
}

FireDoor::FireDoor(const FireDoor& door)
{
    Copy(door);
}

FireDoor::~FireDoor()
{
    Destructor();
}

FireDoor&
FireDoor::operator =(const FireDoor &door)
{
    if(this != &door)
    {
        Destructor();
        Copy(door);
    }
    
    return *this;
}


void
FireDoor::Copy(const FireDoor &door)
{
    x = door.x;
    y = door.y;
    fixed = door.fixed;
    solid = door.solid;
    type = door.type;
    
    gen = door.gen;
    for(unsigned int i = 0; i < door.weights.size(); i++)
    {
        weights.push_back(door.weights[i]);
    }
}

void
FireDoor::Destructor()
{
    x = y = -1;
    type = EntityNone;
    
    gen = NULL;
    weights.clear();
}

bool 
FireDoor::Update()
{
    if(gen == NULL)
    {
        findDataGen();
    }
    
    if(gen != NULL)
    {
        vector<float> data = gen->getData();
    
        float total = 0;
        for(unsigned int i = 0; i < weights.size(); i++)
        {
            total += data[i]*weights[i];
        }
        
        //cout << "Total: " << total << endl;

        bool Upmortal = false;
        if(total > 0)
        {
            Upmortal = true;
        }

        //Compruebo si es diferente a lo anterior
        //para actualizar o no
        if(mortal != Upmortal)
        {
            updated = false;
        }

        mortal = Upmortal;

        if(mortal)
        {
             MasterManAPI *api =  MasterManAPI::getInstance();

             if(api->isPlayer(x,y))
             {
                 api->setFinish(true);
                 api->setWin(false);
                 api->killPlayer();

                 return true;
             }
        }
    }
    
    
    return false;
}

void 
FireDoor::findDataGen()
{
   MasterManAPI *api = MasterManAPI::getInstance();
   
   Entity *entity;
   
   for(int dir = 0; dir < 8 && gen == NULL; dir++)
   {
      entity = api->getDataGen(x,y,(Map::Direction)dir);
       
      if(entity != NULL)
      {
          gen = (DataGen*)entity;
      }
   }
}
