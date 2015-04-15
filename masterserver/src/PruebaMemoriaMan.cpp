/* 
 * File:   PruebaMemoriaMan.c
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on December 26, 2013, 5:49 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "MasterMan.h"
using namespace Map;
/*
 * 
 */
int main(int argc, char** argv) {

    MasterMan master("../maps/linea.json");
    
    master.move(Down);
    master.see(Down);
    master.use(Down);
    master.put(Down);
    master.take(Down);
    master.interact(Down);
    master.move(Down);
    master.move(Down);
    master.move(Down);
    master.move(Down);
    master.move(Down);
    master.move(Down);
    master.move(Down);
    master.move(Down);
    master.move(Down);
    master.move(Down);
    master.move(Down);
    master.move(Down);
    
}

