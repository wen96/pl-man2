/* 
 * File:   Entity.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 7, 2013, 10:24 PM
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include <iostream>
using namespace std;

#include <ostream>
#include "Core.h"
using namespace std;
using namespace Entities;

class Entity {
    
protected:
    //Entity position
    int x;
    int y;
    
    //Entity type
    EntityType type;
    
    //Canonical form Helpers
    void Copy(const Entity&);
    void Destructor();
    
    //Indica si es solido o no
    bool solid;
    //Indica si es fijo o no
    bool fixed;
    
    //ID de la entidad
    int id;
    
    //Nos dice si la entidad esta actualizada o no
    //true: actualizada
    //false: necesita actualizacion
    bool updated;
    
    //Nos dice si la entidad esta viva o no
    bool alive;
    
public:
    //Canonical form
    Entity();
    Entity(int,int);
    Entity(int,int,EntityType);
    Entity(const Entity&);
    virtual ~Entity();
    Entity& operator=(const Entity &);
    
    //Setters and Getters
    void setX(int newX){ x = newX; };
    void setY(int newY){ y = newY; };
    void setID(int newID){ id = newID; };
    void setType(EntityType _type) { type = _type; };
    void setSolid(bool _solid) { solid = _solid; };
    void setFixed(bool _fixed) { fixed = _fixed; };
    void setUpdated(bool _updated) { updated = _updated; };
    void setAlive(bool _alive) { alive = _alive; };
    int getX() const { return x; };
    int getY() const { return y; };
    int getID() const { return id; };
    EntityType getType() const { return type; };
    bool getSolid() const { return solid; };
    bool getFixed() const { return fixed; };
    bool getUpdated() const { return updated; };
    bool getAlive() const { return alive; };
    //Virtual Method update entity.
    //Devuelve true si se finaliza el juego
    virtual bool Update() { updated = true; return false;};
    
    
    
    //Overloading operator <<
    friend ostream& operator<< (ostream&, const Entity&);
private:

};

#endif	/* ENTITY_H */

