#pragma once

/// Includes
extern "C" {
    #include <enet/enet.h>
}
#include <map>
#include <boost/function.hpp>

/// Forward declarations
class CNetworkServer;
class CNetworkServerClient;

///////////////////////////////////////////////////////////////////////////////
/// \brief Interface to implement concrete management of server events and behaviours
///////////////////////////////////////////////////////////////////////////////
class CNetworkServerDispatcher
{
public:
    // types------------------------------------------
    typedef CNetworkServerClient NSClient;

    // methods----------------------------------------
    CNetworkServerDispatcher(CNetworkServer* owner);
    virtual ~CNetworkServerDispatcher();

    // Methods for proccessng messages
    virtual void onConnect(const ENetEvent& event);
    virtual void onReceiveMessage(const ENetEvent& event);
    virtual void onDisconnect(const ENetEvent& event);
    virtual void analizeAndHandleMessage(const ENetEvent& event);
    virtual void defaultMessageHandler(NSClient& c, std::string str);

    // Main run method
    virtual CNetworkServerDispatcher* run();

    // Setter methods
    void    setOwner(CNetworkServer* owner);

protected:
    CNetworkServer* m_owner;                                                      //! Server that owns this dispatcher
    std::map< std::string, boost::function<void(NSClient&, std::string)> >   m_methodTable;  //! Actual method table to call methods for each command
};
