#include "CNetworkServerDispatcher.h"
#include "CNetworkServer.h"
#include "CLog.h"
#include <boost/tokenizer.hpp>
#include <vector>
#include <string>


///////////////////////////////////////////////////////////////////////////////
/// \brief Constructs a dispatcher
///////////////////////////////////////////////////////////////////////////////
CNetworkServerDispatcher::CNetworkServerDispatcher(CNetworkServer *owner)
    : m_owner(owner),
      m_methodTable()
{
    /// Fill in the table of commands to handle in this state
    /// m_methodTable["LOGIN"] = boost::bind(&CWaitForPlayers_Dispatcher::handleLogin, this, _1, _2);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Destructs a dispatcher
///////////////////////////////////////////////////////////////////////////////
CNetworkServerDispatcher::~CNetworkServerDispatcher() {
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Runs operations for this state of the dispatcher
///
/// \returns Next dispatcher that will continue event processing
///////////////////////////////////////////////////////////////////////////////
CNetworkServerDispatcher*
CNetworkServerDispatcher::run(){
    return this;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Manages client connetion events
///
/// \param event    Enet event struct with all the information of the connection
///////////////////////////////////////////////////////////////////////////////
void
CNetworkServerDispatcher::onConnect(const ENetEvent& event) {
    m_owner->addClient(event.peer);
    CLOG.print("DISPATCHER: New client connected from [%u:%u]\n", event.peer->address.host,
               event.peer->address.port);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Manages reception of client messages
///
/// \param event    Enet event struct with all the information about the message
///////////////////////////////////////////////////////////////////////////////
void
CNetworkServerDispatcher::onReceiveMessage(const ENetEvent& event) {
    CLOG.print("DISPATCHER: [%s] received from %u:%u (%s) \n", event.packet->data,
               event.peer->address.host, event.peer->address.port, event.peer->data);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Manages client disconnections
///
/// \param event    Enet event struct with all the information about the disconnection
///////////////////////////////////////////////////////////////////////////////
void
CNetworkServerDispatcher::onDisconnect(const ENetEvent& event) {
    m_owner->removeClient(event.peer);
    CLOG.print("DISPATCHER: Client disconnected [%u:%u]\n", event.peer->address.host,
               event.peer->address.port);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Analizes an incoming message from a client and calls a handle if any
///
/// This method analizes an incoming message from a client and generates
/// corresponding method call to handle the message, if there is a defined
/// handler.
///
/// \param event    Enet event struct with all the information about the message
///////////////////////////////////////////////////////////////////////////////
void CNetworkServerDispatcher::analizeAndHandleMessage(const ENetEvent &event)
{
    // Get the client, if exists. If it does not exist, we ignore it.
    NSClient *c = m_owner->getClient(event.peer);
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

    }
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Handles messages by default, when no other handle does.
///
/// This method is intended to be called to handle messages comming from client
/// when no other handle is available to handle them. This is, if the server
/// receives an erroneous or unexpected message, this handle will take care
/// to notify the client and or take necessary actions.
/// Default action will be to notify them of their error and disconnect them.
///
/// \param c    Client sending the message
/// \param str  String with the complete message received
///////////////////////////////////////////////////////////////////////////////
void
CNetworkServerDispatcher::defaultMessageHandler(NSClient &c, std::string str) {
    // Notify the client of incorrect message and disconnect
    m_owner->disconnect(c, "ERROR 1 Message_Incorrect_or_Unexpected (" + str + ")");
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Sets the server that owns this dispatcher
///
/// \param owner    The server that now owns this dispatcher
///////////////////////////////////////////////////////////////////////////////
void
CNetworkServerDispatcher::setOwner(CNetworkServer* owner) {
    m_owner = owner;
}
