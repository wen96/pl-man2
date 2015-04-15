/* 
 * File:   MapReader.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on December 26, 2013, 6:34 PM
 */

#ifndef MAPREADER_H
#define	MAPREADER_H
#include <iostream>
using namespace std;

#include "IJsonSerializable.h"

class MapReader {
public:
    MapReader();
    MapReader(const MapReader& orig);
    virtual ~MapReader();
    void ReadMap(string);
private:

};

#endif	/* MAPREADER_H */

