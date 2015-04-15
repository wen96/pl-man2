/*
 * Server.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: maktub82
 */

#include "ENetHelper.h"

ENetHelper::ENetHelper() {

}

ENetHelper::~ENetHelper() {
}

void
ENetHelper::Init()
{

	cout << "Inicializando ENet..." << endl;

	//Inicializo Enet
	if (enet_initialize() != 0)
	{
		fprintf (stderr, "An error occurred while initializing ENet.\n");
		exit(EXIT_FAILURE);
	}
	atexit (enet_deinitialize);

	cout << "ENet inicializado " << endl;
}

ENetHost*
ENetHelper::CreateClient()
{
	ENetHost *client = enet_host_create (NULL /* create a client host */,
	            1 /* only allow 1 outgoing connection */,
	            2 /* allow up 2 channels to be used, 0 and 1 */,
	            57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
	            14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);
	if (client == NULL)
	{
	    fprintf (stderr,
	             "An error occurred while trying to create an ENet client host.\n");
	    exit (EXIT_FAILURE);
	}

	return client;
}


ENetHost*
ENetHelper::CreateServer(ENetAddress & address)
{
	
	ENetHost *server = enet_host_create (& address /* the address to bind the server host to */,
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

	return server;
}

string 
ENetHelper::uchar2string(u_char* data)
{
	string message = "";
	
	message.append(reinterpret_cast<const char*>(data));

	return message;
}

ENetPacket* 
ENetHelper::CreatePacket(string data)
{
	ENetPacket *packet = enet_packet_create (data.c_str(),
						  strlen(data.c_str()) + 1,
						  ENET_PACKET_FLAG_RELIABLE);
	return packet;
}

ENetPeer *
ENetHelper::ConnectToServer(ENetHost * client, ENetAddress & address, string server, int port)
{	
	ENetPeer *peer;
	ENetEvent event;

	//Set Server address
	enet_address_set_host (& address, server.c_str());
	address.port = port;

	
	peer = enet_host_connect (client, & address, 2, 0);
	if (peer == NULL)
	{
	   fprintf (stderr,
	            "No available peers for initiating an ENet connection.\n");
	   exit (EXIT_FAILURE);
	}
	

	if (enet_host_service (client, & event, 5000) > 0 &&
	    event.type == ENET_EVENT_TYPE_CONNECT)
	{
	    puts ("Connection to some.server.net:1234 succeeded.");

	}
	else
	{
	    enet_peer_reset (peer);
	    puts ("Connection to some.server.net:1234 failed.");
	}

	return peer;
}

void
ENetHelper::SendPaket(ENetPeer *peer, string data, int channel)
{
	ENetPacket *packet = ENetHelper::CreatePacket(data);
	enet_peer_send (peer, channel, packet);
};


string
ENetHelper::WaitResponse(ENetHost* client)
{
    string response;
    ENetEvent event;
    int serviceResult = 1;
    enet_host_service (client, &event, 5000);

    if (serviceResult > 0)
    {
        switch (event.type)
        {

        case ENET_EVENT_TYPE_RECEIVE:
            
            response = ENetHelper::uchar2string(event.packet->data);
            enet_packet_destroy (event.packet);     
            break;
        default:
            break;
        }
    }
    else if (serviceResult > 0)
    {
        response = "No se ha recibido respuesta del servidor en 5 segundos";
    }
   
    return response;

}

