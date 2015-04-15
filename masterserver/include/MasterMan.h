/*
 * MasterMan.h
 *
 *  Created on: Nov 6, 2013
 *      Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 */

#ifndef MASTERMAN_H_
#define MASTERMAN_H_

#include <iostream>
#include <vector>
using namespace std;


#include "Player.h"
#include "Object.h"
#include "MasterManAPI.h"
//#include "MasterNetworksds.h"
#include "CVisualMap.h"

class Entity;

//Game class. This class contains the game logic.
class MasterMan {
private:
    //Player entity
    Player *player;
    
    //Update all world
    void UpdateWorld();
    
    //Canonical form helpers
    void Copy(const MasterMan &);
    void Destructor();
    
    //Instance of MasterManAPI
    MasterManAPI * api;
    
    string map;
    
public:
    //Canonical form
    MasterMan(string);
    virtual ~MasterMan();
    MasterMan(const MasterMan &);
    MasterMan & operator=(const MasterMan &);
    
    //Draw world in text format
    string drawWorld();
    
    //Move the player in direction
    string move(Direction);
    
    //Get entity in player seen direction
    string see(Direction);
    
    //Use the player object in direction
    string use(Direction);
    
    //Intertact with the object in direction
    string interact(Direction);
    
    //Put object in direction
    string put(Direction);
    
    //Take object in direction
    string take(Direction);
    
    string init();
    
    //Get the player points
    int getPoints() const { return player->getPoints();};
    string getWorld();
};

#endif /* MASTERMAN_H_ */
