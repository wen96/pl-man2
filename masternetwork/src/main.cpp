#include <iostream>
#include "CNetworkServer.h"
#include "CNetworkClient.h"
#include "CNetwork.h"

int main(void) {
	try{
		CNetwork& net = CNetwork::get();
		net.initialize();

		CNetworkClient *client = net.createClient();
		client->setDispatcher(new CNetworkClientDispatcher(client));
		client->connect("localhost",1234);
		client->sendMessage("asdfsdfa");
		client->processEvents();

		//delete client;
	}
	catch(const char * msg){
		std::cout << msg << std::endl;
	}
	return 0;
}
