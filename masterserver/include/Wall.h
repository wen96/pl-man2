/* 
 * File:   Wall.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 10, 2013, 2:50 AM
 */

#ifndef WALL_H
#define	WALL_H

#include "Object.h"
#include "Core.h"

using namespace Entities;

class Wall : public Object {
public:
    Wall();
    Wall(int, int);
    Wall(const Wall& orig);
    virtual ~Wall();
    Wall& operator=(const Wall &);
private:
    //Canonical form Helpers
    void Copy(const Wall &);
    void Destructor();

};

#endif	/* WALL_H */

