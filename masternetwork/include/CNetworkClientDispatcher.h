#pragma once

#include <enet/enet.h>
#include "CNetworkClient.h"

/**
 * Forward declaration entre el dispatcher y el cliente. Se necesitan entre ellos.
 */
class CNetworkClient;

/**
 * Clase que representa un dispatcher para un cliente
 * IMPORRANTE: Si se quieren hacer implementaciones de esta dispatcher hay que heredar de el
 * IMPORTANTE: NO COPIAR Y PEGAR Y CAMBIAR CNetworkClient
 */
class CNetworkClientDispatcher {
public:

	CNetworkClientDispatcher(CNetworkClient *_owner);
	virtual ~CNetworkClientDispatcher();

	// Methods for proccessng messages   --------------------
	virtual void onConnect(const ENetEvent& event);
	virtual void onReceiveMessage(const ENetEvent& event);
	virtual void onDisconnect(const ENetEvent& event);
	virtual void analizeAndHandleMessage(const ENetEvent& event);
	virtual void defaultMessageHandler(std::string str);
	// ----------------------------   --------------------

	virtual void destroy();

	// Main run method
	virtual CNetworkClientDispatcher* run();

	// Setter methods
	void    setOwner(CNetworkClient* _owner);



protected:
	CNetworkClient* m_owner;	//! Server that owns this dispatcher
};

