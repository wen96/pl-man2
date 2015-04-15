#ifndef CNETWORKSERVERDISPATCHERJSON_H
#define CNETWORKSERVERDISPATCHERJSON_H

/// Includes
extern "C" {
    #include <enet/enet.h>
}

#include "MasterMan.h"
#include "Core.h"
#include <map>
#include <boost/function.hpp>
#include "CNetworkServerDispatcher.h"
#include "CJsonCommand.h"

using namespace Map;
/// Forward declarations
class CNetworkServer;
class CNetworkServerClient;
const int MAX_ITER = 20000;
///////////////////////////////////////////////////////////////////////////////
/// \brief Interface to implement concrete management of server events and behaviours
///////////////////////////////////////////////////////////////////////////////
class CNetworkServerDispatcherJSON : public CNetworkServerDispatcher
{
    
    
public:
    // types------------------------------------------
    //typedef CNetworkServerClient NSClient;

    // methods----------------------------------------
    CNetworkServerDispatcherJSON(CNetworkServer* owner, string);
    virtual ~CNetworkServerDispatcherJSON();

    // Methods for proccessng messages
    virtual void onConnect(const ENetEvent& event);
    virtual void onReceiveMessage(const ENetEvent& event);
    virtual void onDisconnect(const ENetEvent& event);
    virtual void analizeAndHandleMessage(const ENetEvent& event);
    virtual void defaultMessageHandler(NSClient& c, std::string str);

    // Main run method
    virtual CNetworkServerDispatcher* run();


protected:
    
    MasterMan *masterMan;
    
private:
    string see(CJsonCommand::ECommand);
    string move(CJsonCommand::ECommand);
    string interact(CJsonCommand::ECommand);
    string use(CJsonCommand::ECommand);
    string take(CJsonCommand::ECommand);
    string put(CJsonCommand::ECommand);
    int iters;
};

#endif // CNETWORKSERVERDISPATCHERJSON_H
