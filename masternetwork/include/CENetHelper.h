#pragma once

#include <string>
#include <iostream>
#include <enet/enet.h>
using namespace std;
#include <cstring>
#include <sstream>


class ENetHelper {
private:
public:
	ENetHelper();
	virtual ~ENetHelper();
	static void Init();
	static ENetHost* CreateClient();
	static ENetHost* CreateServer(ENetAddress &);
	static string uchar2string(u_char*); 
	static ENetPacket * CreatePacket(string); 
	static ENetPeer* ConnectToServer(ENetHost *, ENetAddress &, string, int);
	static void SendPaket(ENetPeer *, string, int);
        static string WaitResponse(ENetHost *);
};

