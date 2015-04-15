/* 
 * File:   TestJson.c
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 10, 2013, 8:34 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "MasterMan.h"
#include "CVisualMap.h"
#include "CJsonCommand.h"
/*
 * 
 */
int main(int argc, char** argv) {
/*try{
    
    MasterMan masterMan;
    string world = masterMan.getWorld();
    cout <<  world << endl; 
    VisualMap map;
    VisualMap *mapaDes = (VisualMap*)map.json_deserialize(world);
    
    cout << mapaDes->getHeight() << endl;
    cout << mapaDes->getWidth() << endl;
} catch (const char * e){
	cout << e << endl;
}*/
    
    //Para crear un comando creas un objeto con el comando
    CJsonCommand command(CJsonCommand::CM_MOVE);
    
    //Como parámetro le añades otro comando (puntero) con la dir
    command.addParameter(new CJsonCommand(CJsonCommand::CM_RIGHT));
    
    string seri = command.json_serialize();
    cout <<  seri << endl;
    CJsonCommand *des = (CJsonCommand*)command.json_deserialize(seri);
    
    cout << des->getCommand() << endl;
    cout << des->getParameters()[0] << endl;
    return (EXIT_SUCCESS);
}

