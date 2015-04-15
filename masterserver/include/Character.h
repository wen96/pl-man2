/* 
 * File:   Character.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 7, 2013, 10:29 PM
 */

#ifndef CHARACTER_H
#define	CHARACTER_H

#include <vector>

#include "Core.h"
#include "Entity.h"

class Entity;
class MasterManAPI;
using namespace std;
using namespace Map;

class Character : public Entity {
public:
    //Canonical form
    Character();
    Character(int,int,EntityType);
    Character(const Character& orig);
    virtual ~Character();
    Character & operator =(const Character &);
    virtual bool Update() { return false; };
    //Move character one step in direction
    virtual void move(Direction);
private:
    
    //Canonical form Helpers
    void Copy(const Character &);
    void Destructor();
protected:
};

#endif	/* CHARACTER_H */

