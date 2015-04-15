//#include "MasterNetwork.h"
#include "cnetworkserverdispatcherJSON.h"
#include "CNetworkServer.h"
#include "CNetwork.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>

const enet_uint16 server_port = 1234;

void * callServer(void *);
void * callClose(void *);

int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        pthread_t t1, t2;

        string map = argv[1];
        //Creamos el servidor y lo iniciamos
        CNetwork& net = CNetwork::get();
        net.initialize();
        CNetworkServer &server = net.createServer(server_port, ENET_HOST_ANY);
        
        CNetworkServerDispatcher *dispatcher = new CNetworkServerDispatcherJSON(&server, map);
        server.setDispatcher(dispatcher);

        pthread_create(&t1, NULL, callServer, &server);
        pthread_create(&t2, NULL, callClose, &server);
        
        int hola;
        cin >> hola;
        


    
    }
    else
    {
        cout << "Necesito un mapa para funcionar :(" << endl;
    }
    
    
    return 0;
}

void * callServer(void * context)
{
    CNetworkServer *server = (CNetworkServer *) context;
    server->run();
    return NULL;
}

void * callClose(void * context)
{
    string salir = "";

    while (salir != "quit")
    {
        cout << "Teclea quit para cerrar el Servidor" << endl;
        
        cin >> salir;
    }
    
    CNetworkServer *server = (CNetworkServer *) context;
    server->stop();
    return NULL;

}
