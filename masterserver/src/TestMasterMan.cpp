/* 
 * File:   TestMasterMan.c
 * Author: maktub82
 *
 * Created on November 9, 2013, 1:14 PM
 */

#include <stdio.h>
#include <stdlib.h>


#include "MasterMan.h"
#include "MasterManAPI.h"
#include "Core.h"

using namespace Map;
/*
 * 
 */
int main(int argc, char** argv) {

    /*MasterMan master = MasterMan();
    MasterManAPI *api = MasterManAPI::getInstance();
    
    string command;
    
    system("clear");
    cout << master.drawWorld();
    while(!api->getFinish())
    {
        cout << "Movimiento [u]p/[d]own/[l]eft/[r]ight\n ";
        cout << "Usar uu/ud/ul/ur\n ";
        cin >> command;
        
        if(command == "u" || command == "up")
        {
            master.move(Up);
        }
        else if(command == "d" || command == "down")
        {
            master.move(Down);
        }
        else if(command == "l" || command == "left")
        {
            master.move(Left);
        }
        else if(command == "r" || command == "right")
        {
            master.move(Right);
        }
        else if(command == "uu" )
        {
            master.use(Up);
        }
        else if(command == "ud")
        {
            master.use(Down);
        }
        else if(command == "ul")
        {
            master.use(Left);
        }
        else if(command == "ur")
        {
            master.use(Right);
        }
        else
        {
            cout << endl;
        }
        
        
        system("clear");
        cout << master.drawWorld();
        cout << "Points: " << master.getPoints() << endl;
    }
    
    if(api->getWin())
    {
        cout << "El Player gana" << endl;
    }
    else
    {
        cout << "El Player pierde :(" << endl;
    }*/
}

