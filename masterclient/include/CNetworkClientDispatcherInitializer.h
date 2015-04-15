#pragma once
#include "CNetworkClientDispatcher.h"
#include "CVisualMap.h"
#include "CLog.h"
#include <string>

namespace masterclient {

/**\brief Inicializa el mundo pidiendolo por el servidor
 * Dispatcher de cliente para controlar los eventos al inicio del juego.
 * Se encargara de enviar el mensaje de conseguir el mundo por primera vez
 * Luego lo instanciara con EntityManager
 */
class CNetworkClientDispatcherInitializer : public CNetworkClientDispatcher {
public:
	//Commments in parent class
	CNetworkClientDispatcherInitializer(CNetworkClient* _owner);
	virtual ~CNetworkClientDispatcherInitializer();

	// Methods for proccessng messages
	virtual void onConnect(const ENetEvent& event);
	virtual void onReceiveMessage(const ENetEvent& event);
	virtual void onDisconnect(const ENetEvent& event);
	virtual void defaultMessageHandler(std::string str);
	void destroy();

	// Main run method
	virtual CNetworkClientDispatcher* run();


};

} /* namespace masterclient */
