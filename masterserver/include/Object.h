/* 
 * File:   Object.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 7, 2013, 10:26 PM
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include <vector>

#include "Entity.h"
#include "Core.h"

using namespace std;
using namespace Entities;
using namespace Map;

class Object : public Entity {
public:
    //Canonical form
    Object();
    Object(int, int);
    Object(const Object&);
    virtual ~Object();
    Object & operator =(const Object &);
    
    //Use action object
    virtual void Use(Direction);
    virtual bool Update() { updated = false; return false; };
private:
    //Canonical form Helpers
    void Copiar(const Object &);
    void Destructor();

};

#endif	/* OBJECT_H */

