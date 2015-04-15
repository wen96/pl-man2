#include "CNetwork.h"
#include "CNetworkServer.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Network constructor
///////////////////////////////////////////////////////////////////////////////
CNetwork::CNetwork()
: m_networkInitialized(false)
{}

///////////////////////////////////////////////////////////////////////////////
/// \brief Network initialization
///
/// It initializes network modules an prepares everything to start creating
/// servers or connecting to peers
///////////////////////////////////////////////////////////////////////////////
void
CNetwork::initialize() {
	// INITIALIZE ENET
	if (enet_initialize() != 0)
		throw "ERROR: There was an error initializing enet and network could"
		" not be started\n";
	m_networkInitialized = true;
}

/////////////////////////////////////////////////////////////////////////////
/// \brief Creates a server and puts it into listening
///
/// \param port                 Port where to listen for clients
/// \param host                 Host where to listen for clients     (default ANY)
/// \param peerCount            Maximum simultaneous connected peers (default 100)
/// \param channelLimit         Number of communication channels (default 2)
/// \param incomingBandwidth    Maximum incoming bandwidth in Bps (default to max)
/// \param outgoingBandwidth    Maximum outgoing bandwidth in Bps (default to max)
///////////////////////////////////////////////////////////////////////////////
CNetworkServer&
CNetwork::createServer(enet_uint16 port, enet_uint32 host, size_t peerCount,
		size_t channelLimit, enet_uint32 incomingBandwidth,
		enet_uint32 outgoingBandwidth) {
	CNetworkServer* newserver = NULL;
	if (m_networkInitialized) {
		/// TODO: Check for exceptions
		newserver = new CNetworkServer(port, host,peerCount, channelLimit,
				incomingBandwidth, outgoingBandwidth);
		m_vecServers.push_back(newserver);
	} else {
		/// TODO: What to do when network is not initialized
	}

	return *newserver;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Restores network state to previous at closing
///////////////////////////////////////////////////////////////////////////////
CNetwork::~CNetwork() {
	if (m_networkInitialized) {
		//enet_deinitialize();
		atexit (enet_deinitialize);
		m_networkInitialized = false;

	}
	for (unsigned int i = 0; i < m_vecClients.size(); i++){
		delete m_vecClients[i];
		m_vecClients[i] = NULL;
	}
	m_vecClients.clear();
	for (unsigned int i = 0; i < m_vecServers.size(); i++){
		delete m_vecServers[i];
		m_vecServers[i] = NULL;
	}
	m_vecServers.clear();
}

CNetworkClient* CNetwork::createClient() {
	CNetworkClient* newclient = NULL;
	if (m_networkInitialized) {
		/// TODO: Check for exceptions
		newclient = new CNetworkClient();
		m_vecClients.push_back(newclient);
	} else {
		throw "Exception: The network has not been initialized before create a client";
	}

	return newclient;
}

