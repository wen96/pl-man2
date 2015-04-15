/*
 * Client.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: maktub82
 */

#include "Client.h"

Client::Client() {
	// TODO Auto-generated constructor stub

}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

void
Client::Init()
{
	ENetHelper::Init();
	client = ENetHelper::CreateClient();
}

void
Client::Connect(string server, int port)
{
	peer = ENetHelper::ConnectToServer(client, address, server, port);

}

void
Client::Disconnect()
{
	enet_host_flush (client);
	enet_host_destroy(client);
}

string
Client::SendCommand(string command)
{
	string response = "";
	
	ENetHelper::SendPaket(peer, command, 0);

	
        response = ENetHelper::WaitResponse(client);

	return response;
}

