/* 
 * File:   Player.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 7, 2013, 10:30 PM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include <iostream>
using namespace std;

#include "Core.h"
#include "Character.h"

class Object;
using namespace Entities;
using namespace Map;

class Player : public Character {
public:
    //Canonical form
    Player();
    Player(int,int);
    Player(const Player& orig);
    virtual ~Player();
    Player& operator=(const Player &);
    
    //Setters and Getters
    Object *getObject() const { return object;};
    void setObject(Object * _object) {object = _object; };
    int getPoints() {return points;};
    void setPoints(int _points) { points = _points; };
    void addPoints(int _points) { points += _points; };
    void addPoint() { points += 1; };
    
    virtual void move(Direction);
    virtual bool Update() { return false; };
private:
    //Canonical Helpers
    void Copy(const Player&);
    void Destructor();
    
    //Object of player
    Object *object;
    
    //Point of the player 
    int points;

};

#endif	/* PLAYER_H */

