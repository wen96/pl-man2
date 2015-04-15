#include "CNetworkServer.h"
#include "CNetworkServerDispatcher.h"
#include "CNetworkServerClient.h"
#include "CLog.h"
#include <iostream>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
/// \brief Creates and sets up a network server ready to listen for clients
///////////////////////////////////////////////////////////////////////////////
CNetworkServer::CNetworkServer(enet_uint16  port,       enet_uint32 host,
                               size_t       peerCount,  size_t      channelLimit,
                               enet_uint32  incomingBandwidth,
                               enet_uint32  outgoingBandwidth)
    : m_serverAddress(),       m_server(NULL),
      m_dispatcher(NULL),      m_serverSendChannel(1)
{
    // Server Address
    m_serverAddress.host = host;
    m_serverAddress.port = port;

    /// TODO: Improve error checking
    // Create the server
    if ( NULL == (m_server = enet_host_create(&m_serverAddress,
                                              peerCount,
                                              channelLimit ,
                                              incomingBandwidth,
                                              outgoingBandwidth)) )
        throw "ERROR: An error ocurred while trying to set up host and port\n";

    // Create the default dispatcher
    m_dispatcher = new CNetworkServerDispatcher(this);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroys the server, disconnecting all the clients
///////////////////////////////////////////////////////////////////////////////
CNetworkServer::~CNetworkServer() {
  if (m_server) {
    /// TODO: Disconnect all client peers
    CLOG.print("SERVER: Destroying server %d\n", m_server->address);
    enet_host_destroy(m_server);
    m_server = NULL;
  }
  clearDispatcher();
}


///////////////////////////////////////////////////////////////////////////////
/// \brief Clears the present dispatcher
///////////////////////////////////////////////////////////////////////////////
void
CNetworkServer::clearDispatcher()
{
    if (m_dispatcher) {
        delete m_dispatcher;
        m_dispatcher = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Sets a new dispatcher for events and behaviours
///
/// \param d    New network dispatcher to use within this server.
///////////////////////////////////////////////////////////////////////////////
void
CNetworkServer::setDispatcher(CNetworkServerDispatcher* d) {
    // Set new dispatcher only it its different than previous
    if (m_dispatcher != d) {
        clearDispatcher();
        m_dispatcher = d;
        m_dispatcher->setOwner(this);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Creates and adds a new client to the server list
///
/// \param c    New client peer information
///
/// \returns (CClient&) A reference to the client to further modify it
///////////////////////////////////////////////////////////////////////////////
CNetworkServer::NSClient&
CNetworkServer::addClient(ENetPeer *c) {
    NSClient *nc = new NSClient(c);
    /// TODO: Check for memory reservation fail
    m_Clients[c] = nc;

    return *nc;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Removes an existing client from the client list
///
/// \param c    Peer that identifies the client to remove
///////////////////////////////////////////////////////////////////////////////
void
CNetworkServer::removeClient(const ENetPeer *c) {
    // If the peer is present in the vector, we remove it
    TClients::iterator it = m_Clients.find(c);
    if ( it != m_Clients.end() ) {
        delete it->second;
        m_Clients.erase(it);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Returns a client reference if the client exists, NULL otherwise
///
/// \param c    Peer that identifies the client to retrieve
///
/// \returns (const CClient *) Pointer to client found or NULL
///////////////////////////////////////////////////////////////////////////////
CNetworkServer::NSClient *
CNetworkServer::getClient(const ENetPeer *c) {
    if ( m_Clients.count(c) ) {
        return m_Clients[c];
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Gives a constant reference to the client map
///
/// \returns (CNetworkServer::TClientPeers&) Map of clients
///////////////////////////////////////////////////////////////////////////////
const CNetworkServer::TClients&
CNetworkServer::getClients() const {
    return m_Clients;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Returns the total number of clients connected to the server
///
/// \returns (unsigned) Number of connected clients
///////////////////////////////////////////////////////////////////////////////
unsigned
CNetworkServer::getClientCount() const {
    return m_Clients.size();
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Processes the next event, if any, or returns after timeout
///
/// \param timeout  Miliseconds to wait for the event until timeout (default 1000)
///
/// \returns (int) Number of proccessed events
///////////////////////////////////////////////////////////////////////////////
unsigned
CNetworkServer::processNextEvent(unsigned long timeout) {
    unsigned  numProcessedEvents = 0;
    ENetEvent event;
    if (enet_host_service(m_server, &event, timeout) > 0) {
        numProcessedEvents++;
        switch(event.type) {
            case ENET_EVENT_TYPE_CONNECT:   { m_dispatcher->onConnect(event);        break;}
            case ENET_EVENT_TYPE_RECEIVE:   { m_dispatcher->onReceiveMessage(event); break;}
            case ENET_EVENT_TYPE_DISCONNECT:{ m_dispatcher->onDisconnect(event);     break;}
            default: break;
        }
        CLOG.logToConsole(false);
        CLOG.print("SERVER: Event Processed. %d Clients connected\n", m_Clients.size());
    }

    return numProcessedEvents;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Runs the server until it finishes
///////////////////////////////////////////////////////////////////////////////
void CNetworkServer::run() {
    // The server will run until there is no dispatcher to proccess messages
    while( m_dispatcher ) {
        while( processNextEvent() );            // Proccess all pending messages
        setDispatcher( m_dispatcher->run() );   // Run dispatcher main proccess
    }
}

void CNetworkServer::stop() {
    // The server will run until there is no dispatcher to proccess messages
    m_dispatcher = NULL;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Sends a message to a client
///
/// \param c    Reference to the client who to send the message
/// \param msg  Message to send
///////////////////////////////////////////////////////////////////////////////
void
CNetworkServer::sendMessage(NSClient &c, const std::string &msg) {
    ENetPeer   *peer    = c.getPeer();
    ENetPacket *packet  = enet_packet_create(msg.c_str(), msg.size() + 1,
                                             ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, m_serverSendChannel, packet);
    enet_host_flush(m_server);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Sends a message to all the clients connected to the server
///
/// \param msg  Message to send
///////////////////////////////////////////////////////////////////////////////
void CNetworkServer::broadcastMessage(const std::string& msg) {
    TClients::iterator it = m_Clients.begin();
    while (it != m_Clients.end()) {
        sendMessage(*(it->second), msg);
        it++;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Disconnects a client from the server
///
/// \param c        Client to disconnect
/// \param reason   String describing the reason of the disconnection
///////////////////////////////////////////////////////////////////////////////
void
CNetworkServer::disconnect(NSClient &c, const std::string &reason) {
    ENetPeer* peer = c.getPeer();
    if ( reason.compare("") ) {
        sendMessage(c, reason);
        enet_peer_disconnect_later(peer, 0);
    } else {
        enet_peer_disconnect(peer, 0);
    }
    enet_host_flush(m_server);
    removeClient(peer);
}
