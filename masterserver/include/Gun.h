/* 
 * File:   Gun.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 10, 2013, 5:54 PM
 */

#ifndef GUN_H
#define	GUN_H

#include "Object.h"
#include "Core.h"
using namespace Entities;

class Gun : public Object {
public:
    //Canonical form
    Gun();
    Gun(int,int);
    Gun(const Gun&);
    virtual ~Gun();
    Gun& operator=(const Gun &);
    virtual void Use(Direction);
    
private:
    //Canonical form Helpers
    void Copy(const Gun &);
    void Destructor();

};

#endif	/* GUN_H */

