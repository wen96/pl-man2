/* 
 * File:   ExitDoor.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 10, 2013, 3:40 AM
 */

#ifndef EXITDOOR_H
#define	EXITDOOR_H

#include "Object.h"
#include "Core.h"

using namespace Entities;

class ExitDoor : public Object {
public:
    ExitDoor();
    ExitDoor(int,int);
    ExitDoor(const ExitDoor&);
    virtual ~ExitDoor();
    ExitDoor& operator=(const ExitDoor &);
    
private:
    void Copy(const ExitDoor &);
    void Destructor();

};

#endif	/* EXITDOOR_H */

