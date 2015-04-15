#pragma once

/// Includes
extern "C" {
    #include <enet/enet.h>
}
#include <map>
#include <string>

/// Forward declarations
class CNetworkServerClient;
class CNetwork;
class CNetworkServerDispatcher;

///////////////////////////////////////////////////////////////////////////////
/// \brief Class that represents a server and its methods to manage clients
///////////////////////////////////////////////////////////////////////////////
class CNetworkServer
{
    friend class CNetwork;  // Online CNetwork will be allowed to create CNetworkServers
public:
    // Types --------------------------
    typedef CNetworkServerClient NSClient;
    typedef std::map<const ENetPeer*, NSClient*> TClients;


    // Methods ------------------------
    ~CNetworkServer();
    void                setDispatcher(CNetworkServerDispatcher* d);
    NSClient&           addClient(ENetPeer *c);
    void                removeClient(const ENetPeer *c);
    NSClient*           getClient(const ENetPeer *c);
    const TClients&     getClients() const;
    unsigned            getClientCount() const;
    unsigned            processNextEvent(unsigned long timeout = 1000);
    void                run();
    void                stop();
    void                sendMessage(NSClient& c, const std::string& msg);
    void                broadcastMessage(const std::string& msg);
    void                disconnect(NSClient& c, const std::string& reason = "");

private:
    // Methods ------------------------
    void clearDispatcher();
    CNetworkServer(enet_uint16 port, enet_uint32 host, size_t peerCount, size_t channelLimit,
                   enet_uint32 incomingBandwidth, enet_uint32 outgoingBandwidth);

    // Attributes ---------------------
    ENetAddress                 m_serverAddress;      //! Address where the server will be listening
    ENetHost                    *m_server;            //! Server host instance
    TClients                    m_Clients;            //! Hash map with all the client peers
    CNetworkServerDispatcher    *m_dispatcher;        //! Dispatcher object that proccesses events and behaviours
    bool                        m_defaultDispatcher;  //! True if this server is using the default network dispatcher
    enet_uint8                  m_serverSendChannel;  //! Server channel used to send messages to clients (default 1)
};

