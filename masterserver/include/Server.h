/*
 * Server.h
 *
 *  Created on: Nov 6, 2013
 *      Author: maktub82
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <iostream>
#include <enet/enet.h>
using namespace std;
#include <stdio.h>
#include <cstring>
#include <sstream>


class Server {
private:
	int port;
	string adress;
	ENetAddress address;
	ENetHost * server;
public:
	Server();
	virtual ~Server();
	void Init();
	void Run();
};

#endif /* SERVER_H_ */
