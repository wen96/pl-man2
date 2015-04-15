#pragma once

#include "CJsonSerializer.h"
#include "CVisualEntity.h"
#include <vector>
using namespace std;

class VisualMap : public CJsonSerializer {
public:
    VisualMap();
    VisualMap(int,int);
    VisualMap(int,int, bool, bool, int);
    VisualMap(int,int,vector<vector<int> >);
    VisualMap(const VisualMap& orig);
    virtual ~VisualMap();
    VisualMap& operator=(const VisualMap &);
    
    virtual void                write2json       (Json::Value& v) const;
    virtual void                setFromJson      (const Json::Value& v);
    virtual IJsonSerializable*  createNewInstance() const;
    virtual void                destroy          ();
    
    int getWidth() const {return width;};
    int getHeight() const {return height;};
    bool getFinish() const {return finish;};
    bool getWin() const {return win;};
    vector<IJsonSerializable*>  getWorld() const {return world;};
    void addEntity(IJsonSerializable *entity) {world.push_back(entity);};
private:
    int width;
    int height;
    bool finish;
    bool win;
    int score;
    vector<IJsonSerializable*> world;
    void Copy(const VisualMap &);
    void Destructor();

};


