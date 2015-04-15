#pragma once


extern "C" {
    #include <enet/enet.h>
}
#include <string>

#include "CENetHelper.h"
#include "CNetworkClientDispatcher.h"

/**
 * Forward declaration entre el dispatcher y el cliente. Se necesitan entre ellos.
 * El Dispatcher tiene un owner CNetworkClient
 */
class CNetworkClientDispatcher;

/**
 * Clase cliente de un servidor. Contiene las funciones necesarias para realizar las opciones necesaria
 * desde el lado cliente en una conexion cliente servidor.
 */
class CNetworkClient {
public:
	// Forma canonica
	CNetworkClient();
	virtual ~CNetworkClient();
	CNetworkClient(const CNetworkClient& _cl);
	CNetworkClient& operator=(const CNetworkClient& _cl);


	// Funciones principales
	void 					Init();
	void 					connect(std::string _host, int _port);
	void 					disconnect();
	void 					setDispatcher(CNetworkClientDispatcher* _d);
	unsigned           		processNextEvent(unsigned long timeout = 1000);
	void                	processEvents(unsigned long timeout = 1000);
	void					waitForEvents();
	void                	sendMessage(const std::string& _msg);

private:

	void clearDispatcher();
	void copy(const CNetworkClient& _cl);

	/**
	 * Datos de direccion del cliente
	 */
	ENetAddress m_address;
	/**
	 * Objeto host que almacena el cliente de Enet
	 */
	ENetHost * m_client;
	/**
	 * Dispatcher activo en el servidor.
	 * El dispatcher es el encargado de procesar los eventos que se producen en el cliente.
	 * Segun el dispatcher activo se procesaran los eventos de una forma u otra
	 */
	CNetworkClientDispatcher *m_dispatcher;
	/**
	 * Canal de comunicacion usado entre el cliente y el servidor
	 */
	enet_uint8 m_serverSendChannel;
	/**
	 * Objedo de enlace entre el cliente y el servidor
	 */
	ENetPeer *m_peer;
};

