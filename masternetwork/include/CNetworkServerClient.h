#pragma once

/// Includes
extern "C" {
    #include <enet/enet.h>
}
#include <string>

///////////////////////////////////////////////////////////////////////////////
/// \brief Information about a client connected to a server
///////////////////////////////////////////////////////////////////////////////
class CNetworkServerClient
{
public:
    CNetworkServerClient(ENetPeer* p);
    bool                isLoggined() const;
    void                setLoggined(bool l);
    ENetPeer*           getPeer();
    void                setUsername(std::string u);
    const std::string&  getUsername() const;

private:
    bool            m_loggined;     //! True if the client has loggined in
    ENetPeer*       m_peer;         //! Pointer to the peer that represents this client
    std::string     m_username;     //! Username of the client
};
