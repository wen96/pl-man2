#pragma once

#include <vector>
extern "C" {
    #include <enet/enet.h>
}

#include "CNetworkClient.h"

/// Forward declarations
class CNetworkServer;

///////////////////////////////////////////////////////////////////////////////
/// \brief Class that encapsulates all network-related issues
///////////////////////////////////////////////////////////////////////////////
class CNetwork
{
public:
    static CNetwork& get() { static CNetwork p; return p; }
    void            initialize();
    CNetworkServer& createServer(enet_uint16 port, enet_uint32 host = ENET_HOST_ANY,
                                 size_t peerCount = 100, size_t channelLimit = 2,
                                 enet_uint32 incomingBandwidth  = 0,
                                 enet_uint32 outgoingBandwidth  = 0);
    /**\brief Devuelve un cliente para un servidor con ENet
     * Instancia un nuevo cliente lo mete en el vector de clientes y lo devuelve
     * Si no se ha inicializado enet devuelve NULL
     * @return CNetworkClient con un cliente instanciado
     */
    CNetworkClient* createClient();
    ~CNetwork();
private:
    CNetwork();

    bool                            m_networkInitialized;
    std::vector<CNetworkServer*>    m_vecServers;
    std::vector<CNetworkClient*>    m_vecClients;
};
