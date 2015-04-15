/* 
 * File:   Bot.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 7, 2013, 10:32 PM
 */

#ifndef BOT_H
#define	BOT_H

#include "Character.h"

class Bot : public Character {
public:
    //Canonical form
    Bot();
    Bot(int,int);
    Bot(const Bot&);
    virtual ~Bot();
    Bot & operator =(const Bot &);
    virtual bool Update() { return false; };
private:
    
    //Canonical form Helpers
    void Copy(const Bot &);
    void Destructor();

};

#endif	/* BOT_H */

