/*
 * Server.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: maktub82
 */

#include "Server.h"

Server::Server() {
	// TODO Auto-generated constructor stub

}

Server::~Server() {
	// TODO Auto-generated destructor stub
}

void
Server::Init()
{

	cout << "Inicializando ENet..." << endl;

	//Inicializo Enet
	if (enet_initialize() != 0)
	{
		fprintf (stderr, "An error occurred while initializing ENet.\n");
		exit(EXIT_FAILURE);
	}
	atexit (enet_deinitialize);

	cout << "ENet inicializado [X]" << endl;


	cout << "Creando Servidor..." << endl;

	address.host = ENET_HOST_ANY;
	/* Bind the server to port 1234. */
	address.port = 1234;
	server = enet_host_create (& address /* the address to bind the server host to */,
	                             32      /* allow up to 32 clients and/or outgoing connections */,
	                              2      /* allow up to 2 channels to be used, 0 and 1 */,
	                              0      /* assume any amount of incoming bandwidth */,
	                              0      /* assume any amount of outgoing bandwidth */);
	if (server == NULL)
	{
	    fprintf (stderr,
	             "An error occurred while trying to create an ENet server host.\n");
	    exit (EXIT_FAILURE);
	}

	cout << "Servidor creado en " << address.host << ":" << address.port << endl;
}

void
Server::Run()
{
	ENetEvent event;

	string clave = "hola";
	string foo = "";
	cout << "Servido a la escucha..." << endl;
	while (true)
	{
		foo = "";
		enet_host_service (server, & event, 10000);
	    switch (event.type)
	    {

	    //Si se ha producido un evento de conexion
	    case ENET_EVENT_TYPE_CONNECT:

	        cout << "Nuevo cliente conectado. " <<
	        event.peer->address.host << ":" <<
	        event.peer->address.port << endl;

	        break;
	    //Evento de recibo de mensajes
	    case ENET_EVENT_TYPE_RECEIVE:


	    	foo.append(reinterpret_cast<const char*>(event.packet->data));

	    	if(foo == clave)
	    	{
	    		ENetPacket *response = enet_packet_create ("pepe", strlen
	    			        	("pepe") + 1, ENET_PACKET_FLAG_RELIABLE);
	    		enet_host_broadcast (server, 0, response);
	    	}
	    	else
	    	enet_host_broadcast (server, 0, event.packet);
	        /*cout << "Se ha recibido del cliente: " << event.packet->data << endl;
	        stringstream ss;
	        ss << event.packet->data;
	        ENetPacket *response = enet_packet_create (ss.str(), strlen
	        	(event.packet->data) + 1, ENET_PACKET_FLAG_RELIABLE);
	        enet_host_broadcast (server, 0, response);

	        enet_host_broadcast (server, 0, response);
	        enet_packet_destroy (event.packet);*/
	        break;

	    case ENET_EVENT_TYPE_DISCONNECT:
	    	cout << "Se ha desconectado el cliente" << endl;
	        event.peer -> data = NULL;
	        break;
	    case ENET_EVENT_TYPE_NONE:
	    	cout << "Se ha desconectado el cliente" << endl;
	    	        break;

	    }
	}


	enet_host_destroy(server);
}
