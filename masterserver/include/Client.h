/*
 * Client.h
 *
 *  Created on: Nov 7, 2013
 *      Author: maktub82
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <iostream>
#include <enet/enet.h>
using namespace std;
#include <stdio.h>
#include <cstring>

#include "ENetHelper.h"

class Client {
private:
	ENetHost * client;
	ENetAddress address;
	ENetPeer *peer;
public:
	Client();
	virtual ~Client();
	void Init();
	void Connect(string, int);
        void Disconnect();
	string SendCommand(string);
};

#endif /* CLIENT_H_ */
