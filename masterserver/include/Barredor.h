/* 
 * File:   Barredor.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 9, 2013, 1:25 PM
 */

#ifndef BARREDOR_H
#define	BARREDOR_H

#include <iostream>
using namespace std;

#include "Core.h"
#include "Bot.h"
#include "MasterManAPI.h"

using namespace Entities;
using namespace Map;

class Barredor : public Bot {
private:
    /*Dirección hacia la que se mueve el Barredor. 
     * Cuando llega a un obstaculo cambia a la dirección inversa.
     */
    Direction direction;
    
    
    void Copy(const Barredor &);
    void Destructor();
public:
    Barredor();
    Barredor(int,int, Direction);
    Barredor(const Barredor&);
    virtual ~Barredor();
    Barredor& operator=(const Barredor &);
    
    virtual bool Update();
    
private:

};

#endif	/* BARREDOR_H */

