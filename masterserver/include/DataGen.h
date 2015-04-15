/* 
 * File:   DataGen.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 11, 2013, 7:56 PM
 */

#ifndef DATAGEN_H
#define	DATAGEN_H


#include <vector>
using namespace std;

#include "Object.h"
#include "Core.h"
using namespace Entities;

class DataGen : public Object {
public:
    DataGen();
    DataGen(int,int, int, int, int);
    DataGen(const DataGen&);
    virtual ~DataGen();
    DataGen& operator=(const DataGen&);
    vector<float> getData(){return data;};
    virtual bool Update();
private:
    int min;
    int max;
    void Copy(const DataGen &);
    void Destructor();
    vector<float> data;
};

#endif	/* DATAGEN_H */

