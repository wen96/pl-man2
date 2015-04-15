/* 
 * File:   Dot.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 10, 2013, 2:42 AM
 */

#ifndef DOT_H
#define	DOT_H

#include "Object.h"
#include "Core.h"

using namespace Entities;

class Dot : public Object {
public:
    //Canonical form
    Dot();
    Dot(int,int);
    Dot(const Dot&);
    virtual ~Dot();
    Dot & operator =(const Dot &);
    virtual bool Update() {if(!alive) {updated = false;}else{updated = true;} return false;};
private:
    //Canonical form Helpers
    void Copy(const Dot &);
    void Destructor();

};

#endif	/* DOT_H */

