#include "cnetworkserverdispatcherJSON.h"
#include "CLog.h"
#include <boost/tokenizer.hpp>
#include <vector>
#include <string>
#include "CNetworkServer.h"
#include "CJsonCustomData.h"
#include "CNetworkServerClient.h"
//#include "MasterNetworkssd.h"


///////////////////////////////////////////////////////////////////////////////
/// \brief Constructs a dispatcher
///////////////////////////////////////////////////////////////////////////////

CNetworkServerDispatcherJSON::CNetworkServerDispatcherJSON(CNetworkServer *owner, string map)
: CNetworkServerDispatcher(owner)
{
    iters = 0;
    /// Fill in the table of commands to handle in this state
    /// m_methodTable["LOGIN"] = boost::bind(&CWaitForPlayers_Dispatcher::handleLogin, this, _1, _2)
    masterMan = new MasterMan(map);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Destructs a dispatcher
///////////////////////////////////////////////////////////////////////////////

CNetworkServerDispatcherJSON::~CNetworkServerDispatcherJSON()
{
    if(masterMan != NULL)
    {
        delete masterMan;
        masterMan = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Runs operations for this state of the dispatcher
///
/// \returns Next dispatcher that will continue event processing
///////////////////////////////////////////////////////////////////////////////

CNetworkServerDispatcher*
CNetworkServerDispatcherJSON::run()
{
    return this;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Manages client connetion events
///
/// \param event    Enet event struct with all the information of the connection
///////////////////////////////////////////////////////////////////////////////

void
CNetworkServerDispatcherJSON::onConnect(const ENetEvent& event)
{
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
CNetworkServerDispatcherJSON::onReceiveMessage(const ENetEvent& event)
{
    CLOG.logToConsole(false);
    CLOG.print("DISPATCHER: [%s] received from %u:%u (%s) \n", event.packet->data,
            event.peer->address.host, event.peer->address.port, event.peer->data);
    analizeAndHandleMessage(event);
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Manages client disconnections
///
/// \param event    Enet event struct with all the information about the disconnection
///////////////////////////////////////////////////////////////////////////////

void
CNetworkServerDispatcherJSON::onDisconnect(const ENetEvent& event)
{
    CLOG.logToConsole(false);
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

void CNetworkServerDispatcherJSON::analizeAndHandleMessage(const ENetEvent &event)
{
    // Get the client, if exists. If it does not exist, we ignore it.
    NSClient *c = m_owner->getClient(event.peer);
    if (c && iters <= MAX_ITER)
    {

        string response = masterMan->getWorld();

        std::string str((const char*) event.packet->data);
        try
        {
            CJsonCommand command;

            CJsonCommand *deserielized;
            deserielized = (CJsonCommand *) command.json_deserialize(str);


            if (deserielized != NULL)
            {
                switch (deserielized->getCommand())
                {
                    case CJsonCommand::CM_MOVE:
                        if (deserielized->getParameters().size() == 1)
                        {
                            response = move(deserielized->getParameters()[0]);
                            iters++;
                        }

                        break;
                    case CJsonCommand::CM_SEE:
                        if (deserielized->getParameters().size() == 1)
                        {
                            response = see(deserielized->getParameters()[0]);
                        }
                        break;
                    case CJsonCommand::CM_INTERACT:
                        if (deserielized->getParameters().size() == 1)
                        {
                            response = interact(deserielized->getParameters()[0]);
                        }
                        break;
                    case CJsonCommand::CM_USE:
                        if (deserielized->getParameters().size() == 1)
                        {
                            response = use(deserielized->getParameters()[0]);
                            iters++;
                        }
                        break;
                    case CJsonCommand::CM_GET:
                        if (deserielized->getParameters().size() == 1)
                        {
                            response = take(deserielized->getParameters()[0]);
                            iters++;
                        }
                        break;
                    case CJsonCommand::CM_DROP:
                        if (deserielized->getParameters().size() == 1)
                        {
                            response = put(deserielized->getParameters()[0]);
                            iters++;
                        }
                        break;
                    case CJsonCommand::CM_INIT:
                        //cout << "Funciona" << endl;
                        if (deserielized->getParameter(0) != NULL)
                        {
                            masterMan = new MasterMan(((cJsonCustomData*)deserielized->getParameter(0))->getValue());
                         //cout << "Si" << endl;
                            response = masterMan->getWorld();
                        }
                                                 //cout << "Si" << endl;
						 iters = 0;
                        //masterMan = new MasterMan("fuego.json");
                        //response = masterMan->getWorld();
                        break;
                    default:
                        break;
                }
                
                delete deserielized;
                deserielized = NULL;
            }

        } catch (const char * e)
        {
            cerr << e << endl;
        }

        m_owner->sendMessage(*c, response);
    }
    

}

string
CNetworkServerDispatcherJSON::move(CJsonCommand::ECommand dir)
{
    string response = "";
    switch (dir)
    {
        case CJsonCommand::CM_UP:
            response = masterMan->move(Up);
            break;
        case CJsonCommand::CM_DOWN:
            response = masterMan->move(Down);
            break;
        case CJsonCommand::CM_LEFT:
            response = masterMan->move(Left);
            break;
        case CJsonCommand::CM_RIGHT:
            response = masterMan->move(Right);
            break;
        case CJsonCommand::CM_NONE:
				response = masterMan->move(None);
				break;
        default:
            break;
    }
    return response;
}

string
CNetworkServerDispatcherJSON::see(CJsonCommand::ECommand dir)
{
    string response = "";
    switch (dir)
    {
        case CJsonCommand::CM_UP:
            response = masterMan->see(Up);
            break;
        case CJsonCommand::CM_DOWN:
            response = masterMan->see(Down);
            break;
        case CJsonCommand::CM_LEFT:
            response = masterMan->see(Left);
            break;
        case CJsonCommand::CM_RIGHT:
            response = masterMan->see(Right);
            break;
        case CJsonCommand::CM_UPLEFT:
            response = masterMan->see(UpLeft);
            break;
        case CJsonCommand::CM_UPRIGHT:
            response = masterMan->see(UpRight);
            break;
        case CJsonCommand::CM_DOWNLEFT:
            response = masterMan->see(DownLeft);
            break;
        case CJsonCommand::CM_DOWNRIGHT:
            response = masterMan->see(DownRight);
            break;
        default:
            break;
    }

    return response;
}

string
CNetworkServerDispatcherJSON::interact(CJsonCommand::ECommand dir)
{
    string response = "";
    switch (dir)
    {
        case CJsonCommand::CM_UP:
            response = masterMan->interact(Up);
            break;
        case CJsonCommand::CM_DOWN:
            response = masterMan->interact(Down);
            break;
        case CJsonCommand::CM_LEFT:
            response = masterMan->interact(Left);
            break;
        case CJsonCommand::CM_RIGHT:
            response = masterMan->interact(Right);
            break;
        case CJsonCommand::CM_UPLEFT:
            response = masterMan->interact(UpLeft);
            break;
        case CJsonCommand::CM_UPRIGHT:
            response = masterMan->interact(UpRight);
            break;
        case CJsonCommand::CM_DOWNLEFT:
            response = masterMan->interact(DownLeft);
            break;
        case CJsonCommand::CM_DOWNRIGHT:
            response = masterMan->interact(DownRight);
            break;
        default:
            break;
    }

    return response;
}

string
CNetworkServerDispatcherJSON::use(CJsonCommand::ECommand dir)
{
    string response = "";
    switch (dir)
    {
        case CJsonCommand::CM_UP:
            response = masterMan->use(Up);
            break;
        case CJsonCommand::CM_DOWN:
            response = masterMan->use(Down);
            break;
        case CJsonCommand::CM_LEFT:
            response = masterMan->use(Left);
            break;
        case CJsonCommand::CM_RIGHT:
            response = masterMan->use(Right);
            break;
        case CJsonCommand::CM_UPLEFT:
            response = masterMan->use(UpLeft);
            break;
        case CJsonCommand::CM_UPRIGHT:
            response = masterMan->use(UpRight);
            break;
        case CJsonCommand::CM_DOWNLEFT:
            response = masterMan->use(DownLeft);
            break;
        case CJsonCommand::CM_DOWNRIGHT:
            response = masterMan->use(DownRight);
            break;
        default:
            break;
    }

    return response;
}

string
CNetworkServerDispatcherJSON::take(CJsonCommand::ECommand dir)
{
    string response = "";
    switch (dir)
    {
        case CJsonCommand::CM_UP:
            response = masterMan->take(Up);
            break;
        case CJsonCommand::CM_DOWN:
            response = masterMan->take(Down);
            break;
        case CJsonCommand::CM_LEFT:
            response = masterMan->take(Left);
            break;
        case CJsonCommand::CM_RIGHT:
            response = masterMan->take(Right);
            break;
        case CJsonCommand::CM_UPLEFT:
            response = masterMan->take(UpLeft);
            break;
        case CJsonCommand::CM_UPRIGHT:
            response = masterMan->take(UpRight);
            break;
        case CJsonCommand::CM_DOWNLEFT:
            response = masterMan->take(DownLeft);
            break;
        case CJsonCommand::CM_DOWNRIGHT:
            response = masterMan->take(DownRight);
            break;
        default:
            break;
    }

    return response;
}

string
CNetworkServerDispatcherJSON::put(CJsonCommand::ECommand dir)
{
    string response = "";
    switch (dir)
    {
        case CJsonCommand::CM_UP:
            response = masterMan->put(Up);
            break;
        case CJsonCommand::CM_DOWN:
            response = masterMan->put(Down);
            break;
        case CJsonCommand::CM_LEFT:
            response = masterMan->put(Left);
            break;
        case CJsonCommand::CM_RIGHT:
            response = masterMan->put(Right);
            break;
        case CJsonCommand::CM_UPLEFT:
            response = masterMan->put(UpLeft);
            break;
        case CJsonCommand::CM_UPRIGHT:
            response = masterMan->put(UpRight);
            break;
        case CJsonCommand::CM_DOWNLEFT:
            response = masterMan->put(DownLeft);
            break;
        case CJsonCommand::CM_DOWNRIGHT:
            response = masterMan->put(DownRight);
            break;
        default:
            break;
    }

    return response;
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
CNetworkServerDispatcherJSON::defaultMessageHandler(NSClient &c, std::string str)
{
    // Notify the client of incorrect message and disconnect
    m_owner->disconnect(c, "ERROR 1 Message_Incorrect_or_Unexpected (" + str + ")");
}

