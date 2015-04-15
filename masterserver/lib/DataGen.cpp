/* 
 * File:   DataGen.cpp
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 * 
 * Created on November 11, 2013, 7:56 PM
 */

#include "DataGen.h"
#include "Object.h"

#include <stdlib.h>    
#include <time.h>    
#include <cmath> 

DataGen::DataGen() : Object()
{
    type = EntityDataGen;
    solid = true;
    fixed = true;
}

DataGen::DataGen(int _x, int _y, int numbers, int _min, int _max) : Object(_x,_y)
{
    type = EntityDataGen;
    min = _min;
    max = _max;
    solid = true;
    fixed = true;
    srand(time(NULL));
    int range = max - min;
    //cout << "Puerta: ";
    for(int i = 0; i < numbers; i++)
    {
        float number = ((rand()%(range*100))/100.0)+min;
        // cout << number << ", ";
        data.push_back(number);
    }
    
    //cout << endl;
    
}

DataGen::DataGen(const DataGen& gen)
{
    Copy(gen);
}

DataGen::~DataGen()
{
    Destructor();
}

DataGen&
DataGen::operator =(const DataGen &gen)
{
    if(this != &gen)
    {
        Destructor();
        Copy(gen);
    }
    
    return *this;
}

void 
DataGen::Copy(const DataGen &gen)
{
    x = gen.x;
    y = gen.y;
    type = gen.type;
    solid = gen.solid;
    fixed = gen.fixed;
    
    for(unsigned int i = 0; i < gen.data.size(); i++)
    {
        data.push_back(gen.data[i]);
    }
}

void
DataGen::Destructor()
{
    x = y = -1;
    type = EntityNone;
    
    data.clear();
}

bool 
DataGen::Update()
{
    int numbers = (int)data.size();
    int range = max - min;
    
    data.clear();
    for(int i = 0; i < numbers; i++)
    {
        float number = ((rand()%(range*100))/100.0)+min;
        data.push_back(number);
    }
    
    return false;
}
