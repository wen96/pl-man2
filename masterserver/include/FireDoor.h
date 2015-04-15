/* 
 * File:   FireDoor.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 11, 2013, 7:53 PM
 */

#ifndef FIREDOOR_H
#define	FIREDOOR_H

#include <vector>
using namespace std;

#include "Object.h"
#include "DataGen.h"


class FireDoor : public Object {
public:
    FireDoor();
    FireDoor(int,int, int, int, int, DataGen *);
    FireDoor(const FireDoor&);
    virtual ~FireDoor();
    FireDoor& operator=(const FireDoor &);
    bool getMortal() {return mortal;};
    virtual bool Update();
private:
    //Si no está asociado a un DataGen busca uno
    //a su alrededor
    void findDataGen();
    bool mortal;
    vector<int> weights;
    DataGen *gen;
    void Copy(const FireDoor&);
    void Destructor();

};

#endif	/* FIREDOOR_H */

