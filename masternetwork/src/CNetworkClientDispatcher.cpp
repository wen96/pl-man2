#include "CNetworkClientDispatcher.h"
#include "CNetworkServer.h"
#include "CLog.h"
#include <boost/tokenizer.hpp>
#include <vector>
#include <string>

/**
 * Constructor con un owner
 * @param _owner con el puntero al cliente
 */
CNetworkClientDispatcher::CNetworkClientDispatcher(CNetworkClient *_owner) : m_owner(_owner){}

CNetworkClientDispatcher::~CNetworkClientDispatcher() {
	m_owner = NULL;
}

CNetworkClientDispatcher* CNetworkClientDispatcher::run(){
	return this;
}

/**
 * Funcion que se llama al conectarse
 * @param event
 */
void CNetworkClientDispatcher::onConnect(const ENetEvent& event) {
	CLOG.print("CLIENT DISPATCHER: Connected from [%u:%u]\n", event.peer->address.host,
			event.peer->address.port);
}

/**
 * Funcion que se llama cuando se recibe un mensaje en el host
 * @param event
 */
void CNetworkClientDispatcher::onReceiveMessage(const ENetEvent& event) {
	CLOG.print("CLIENT DISPATCHER: [%s] received from %u:%u (%s) \n", event.packet->data,
			event.peer->address.host, event.peer->address.port, event.peer->data);
}

/**
 * Cuando se desconecta el cliente
 * @param event
 */
void CNetworkClientDispatcher::onDisconnect(const ENetEvent& event) {
	CLOG.print("CLIENT DISPATCHER: Client disconnected [%u:%u]\n", event.peer->address.host,
			event.peer->address.port);
}

/**\brief  Analizes an incoming message from a client and calls a handle if any
 * This method analizes an incoming message from a client and generates
 * corresponding method call to handle the message, if there is a defined
 * handler.
 * @param event
 */
void CNetworkClientDispatcher::analizeAndHandleMessage(const ENetEvent &event)
{
	// Get the client, if exists. If it does not exist, we ignore it.
	/*NSClient *c = m_owner->getClient(event.peer);
    if ( c ) {
        // Tokenize input
        std::vector<std::string> vTokens;
        std::string str((const char*)event.packet->data);
        boost::tokenizer<> t(str);
        boost::tokenizer<>::iterator it = t.begin();

        CLOG.print("DISPATCHER[TOKENIZING]: %s\n", str.c_str());

        while (it != t.end()) {
            CLOG.print("DISPATCHER[TOKEN]: %s\n", it->c_str());
            vTokens.push_back(*it);
            it++;
        }

        // Call handler method if correct syntax (COMMAND ARG)
        if (vTokens.size() == 2 && m_methodTable.count(vTokens[0]) ) {
            m_methodTable[vTokens[0]](*c, vTokens[1]);
        } else {
            defaultMessageHandler(*c, str);
        }

    }*/
	//TODO analizeAndHandleMessage
	CLOG.print("analizeAndHandleMessage: Is not implemented");
}

/**
 * Manejador por defecto al que pasaran los mensaje
 * Solo muestra por la salida estandar el mensaje
 * @param str
 */
void
CNetworkClientDispatcher::defaultMessageHandler(std::string str) {
	// Notify the client of incorrect message and disconnect
	m_owner->disconnect();
	CLOG.print("DEFAULT MESSAGE HANDLER: %s",str.c_str());
}

void CNetworkClientDispatcher::destroy() {
	delete this;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Sets the server that owns this dispatcher
///
/// \param owner    The server that now owns this dispatcher
///////////////////////////////////////////////////////////////////////////////
void
CNetworkClientDispatcher::setOwner(CNetworkClient* _owner) {
	m_owner = _owner;
}
