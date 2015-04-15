//============================================================================
// Name        : MasterServer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "Client.h"
#include "CVisualMap.h"
#include "CJsonCommand.h"
#include <enet/enet.h>
#include <algorithm>
#include "Core.h"

using namespace Entities;
        
int main(void) {

    //Creamos el servidor y lo iniciamos
    Client client = Client();
    client.Init();
    client.Connect("localhost", 1234);


    string command;


    cout << "Client> ";
    cin >> command;

    while (command != "exit" && command != "quit") {

        VisualMap map;
        CJsonCommand JSONcommand(CJsonCommand::CM_MOVE);
    
        //Como parámetro le añades otro comando (puntero) con la dir
        
        
        
        if(command == "w")
        {
            JSONcommand.addParameter(new CJsonCommand(CJsonCommand::CM_UP));
        }
        else if(command == "a")
        {
            JSONcommand.addParameter(new CJsonCommand(CJsonCommand::CM_LEFT));
        }
        else if(command == "s")
        {
            JSONcommand.addParameter(new CJsonCommand(CJsonCommand::CM_DOWN));
        }
        else if(command == "d")
        {
            JSONcommand.addParameter(new CJsonCommand(CJsonCommand::CM_RIGHT));
        }
            
        command = JSONcommand.json_serialize();
        string response = client.SendCommand(command);
        cout << response << endl;
        
        
        VisualMap *mapaDes = (VisualMap*)map.json_deserialize(response);
        
        cout << "DESERIALIZADO" << mapaDes->getWidth()  << " "  << mapaDes->getWorld().size() << endl;
        
        int x = 0;
        int y = 0;
        
        for(unsigned int i = 0; i < mapaDes->getWorld().size(); i++)
        {
          VisualEntity *entityObj = ((VisualEntity*)mapaDes->getWorld()[i]);
          int entity = EntityNone;
          
          if(x == entityObj->getX() && y == entityObj->getY())
          {
              entity = entityObj->getType();
          }
          else if(x < entityObj->getX() && y < entityObj->getY())
          {
              i--;
          }
          
          //cout << entityObj->getX() << " " << entityObj->getY() << endl;
          switch(entity)
                {
                    case EntityNone:
                        cout << " ";
                        break;
                    case EntityPlayer:
                        cout << "@";
                        break;
                        case EntityDot:
                            cout << ".";
                        break;
                        case EntityEnemy:
                            cout << "E";
                        break;
                        case EntityWall:
                            cout << "#";
                        break;
                        case EntityFireDoor:
                            cout << "O";
                        break;
                        case EntityDataGen:
                            cout << "$";
                        break;
                    default:
                        cout << entity;
                        break;
                }
          
          x++;
          
          if(y >= mapaDes->getWidth())
          {
              x++;
              y = 0;
              cout << endl;
          }
          
          
        }
        /*for(int i = 0; i < mapaDes->getWidth(); i++)
            
        {
            for(int j = 0; j < mapaDes->getHeight(); j++)
            {
                int entity = ((VisualEntity*)mapaDes->getWorld()[j*mapaDes->getWidth() + i])->getType();
               
                //int entity = 2;
                switch(entity)
                {
                    case EntityNone:
                        cout << " ";
                        break;
                    case EntityPlayer:
                        cout << "@";
                        break;
                        case EntityDot:
                            cout << ".";
                        break;
                        case EntityEnemy:
                            cout << "E";
                        break;
                        case EntityWall:
                            cout << "#";
                        break;
                        case EntityFireDoor:
                            cout << "O";
                        break;
                        case EntityDataGen:
                            cout << "$";
                        break;
                    default:
                        cout << entity;
                        break;
                }
            }
            
            cout << endl;
        }*/
        
        cout << "Client> ";
        cin >> command;
    }


    client.Disconnect();

    return 0;
}
