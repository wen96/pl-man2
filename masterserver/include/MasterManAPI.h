/* 
 * File:   MasterManAPI.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 9, 2013, 7:22 PM
 */

#ifndef MASTERMANAPI_H
#define	MASTERMANAPI_H

#include <vector>
using namespace std;

#include "Entity.h"
#include "Core.h"

using namespace Map;
using namespace Entities;

class Player;

class MasterManAPI {
public:
    //Singlenton class
    static MasterManAPI *getInstance();
    
    //Getters and Setters
    void setWorld(vector< vector < vector<Entity *> > > *_world) {
        world = _world;
        vector< vector< vector<Entity *> > > & vecRef = *world;
        entities.clear();
        
        for(unsigned int i = 0; i < vecRef.size(); i++)
        {
            for(unsigned int j = 0; j < vecRef[i].size(); j++)
            {
                for(unsigned int z = 0; z < vecRef[i][j].size(); z++)
                {
                    entities.push_back(vecRef[i][j][z]);
                }
            }
        }
    };
    void setEntity(int,int, Entity*);
    void setEntity(int, int, Direction, Entity*);
    void setFinish(bool _finish) { finish = _finish; };
    void setWin(bool _win) { win = _win; };
    void setPlayer(Player* _player) { player = _player; };
    vector<Entity *> getEntity(int,int);
    vector<Entity *> getEntity(int, int, Direction);
    Entity* getEntityByPriority(int x, int y, Direction direction);
    Entity* getEntityByType(int x, int y, Direction direction, EntityType);
    bool getFinish() { return finish ; };
    vector< vector < vector<Entity *> > > * getWorld() { return world ; };
    bool getWin() { return win ; };
    Player* getPlayer() { return player ; };
    int getNextX(int, Direction);
    int getNextY(int, Direction);
    int getNextID() { return lastID++;};
    int getScore();
    
    vector<Entity *>& getEntities()
    {
        return entities;
    }
    int getWidth() const {return width;} 
    int getHeight() const {return height;} 
    void setWidth(int w)  {width = w;} 
    void setHeight(int h)  {height = h;} 
    void dispose();
    
    bool isSolid(int, int);
    bool isSolid(int, int, Direction);
    bool isPlayer(int, int);
    bool isPlayer(int, int, Direction);
    bool isType(int, int, EntityType);
    bool isType(int, int, Direction, EntityType);
    void killPlayer();
    Entity* getDataGen(int,int,Direction); 
    void deleteEntity(int,int,Direction, EntityType);
    void deleteEntity(int,int, EntityType);
    void removeEntity(Entity*);
private:
    //Canonical form
    MasterManAPI();
    MasterManAPI(const MasterManAPI& orig);
    virtual ~MasterManAPI();
    MasterManAPI& operator=(const MasterManAPI &);
    
    //Canonical form Helpers
    void Copy(const MasterManAPI &);
    void Destructor();
          
    
    //World of game
    vector< vector< vector<Entity *> > > *world;
    vector<Entity *> entities;
    
    //Static pointer
    static MasterManAPI* m_pInstance;
    
    //The game is finish
     bool finish;
     
    //The winner is the player
    bool win;
    
    //Id to Entities
    int lastID;
    
    Player *player;
    
    int width;
    int height;
};

#endif	/* MASTERMANAPI_H */

