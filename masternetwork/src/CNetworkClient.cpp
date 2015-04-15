#include "CNetworkClient.h"
#include "CNetworkClientDispatcher.h"
#include "CLog.h"

/**
 * Crea un dispatcher por defecto y ejecuta la funcion Init que inicializar lo necesario
 * para que la rede este lista par trasmitir
 */
CNetworkClient::CNetworkClient():
m_address(), m_client(NULL), m_dispatcher(NULL),
m_serverSendChannel(1), m_peer(NULL) {

	Init();
}
/**
 * Hace enet_host_destroy del cliente
 */
CNetworkClient::~CNetworkClient() {
	if (m_client){
		if (m_peer) enet_peer_reset(m_peer);
		enet_host_destroy(m_client);
		m_client = NULL;
	}
	clearDispatcher();
}

CNetworkClient::CNetworkClient(const CNetworkClient& _cl) {
	copy(_cl);
}

CNetworkClient& CNetworkClient::operator =(const CNetworkClient& _cl) {
	if (this != &_cl){
		this->~CNetworkClient();
		copy(_cl);
	}
	return *this;
}

/**
 * Inicializa los recursos necesario de Enet
 */
void CNetworkClient::Init() {

	m_client = enet_host_create (0 /* create a client host */,
			1 /* only allow 1 outgoing connection */,
			2 /* allow up 2 channels to be used, 0 and 1 */,
			57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
			14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);
	if (m_client == NULL){
		throw ("Error: Problem creating client host\n");
	}

	CLOG.print("CLIENT >> ENet initialized\n");
}

/**
 * Se conecta a un servidor pasado como parametro
 * @param _host string con la ip o ombre del host
 * @param _port entero con el puerto
 */
void CNetworkClient::connect(std::string _host, int _port) {
	if (m_client){
		m_peer = ENetHelper::ConnectToServer(m_client, m_address, _host, _port);
		if (m_peer == NULL){
			throw "Exception: Can create conexion with server";
		}
		CLOG.print("Client >> Conected to server %d\n",m_dispatcher, m_address.host);
	}
}

/**
 * Se desconecta del servidor al que este conectado
 */
void CNetworkClient::disconnect() {
	CLOG.print("CLIENT >> Disconnecting client\n");
	if (m_peer != NULL){
		enet_peer_disconnect(m_peer,0);
		//enet_peer_reset(m_peer);
		m_peer = NULL;
	}
	if (m_client != NULL){
		enet_host_flush (m_client);
		enet_host_destroy(m_client);
		m_client = NULL;
	}
}

/**
 * Cambia el dispatcher que maneja el cliente en ese momento.
 * Si no es el mismo dispatcher, elmina la memoria del dispatcher anterior y lo cambia
 * por el nuevo pasado por parametro
 * @param _d nuevo dispatcher
 */
void CNetworkClient::setDispatcher(CNetworkClientDispatcher* _d) {
	CLOG.print("CLIENT >> Changing dispatcher from %d to %d\n",m_dispatcher,_d);
	if (_d != m_dispatcher){
		clearDispatcher();
		m_dispatcher = _d;
	}
}

/**
 * Procesa un evento pendiente
 * Llama a enet_host_service y compueba que tipo de evento es llamando a la correspondiente funcion
 * del dispatcher
 * @param timeout timeout para la espera de peticion
 */
unsigned CNetworkClient::processNextEvent(unsigned long timeout) {
	unsigned  numProcessedEvents = 0;
	if (m_client){
		ENetEvent event;
		if (enet_host_service(m_client, &event, timeout) > 0) {
			numProcessedEvents++;
			switch(event.type) {
			case ENET_EVENT_TYPE_CONNECT:   {
				m_dispatcher->onConnect(event);
				event.peer->data = NULL;
				break;}
			case ENET_EVENT_TYPE_RECEIVE:   {
				m_dispatcher->onReceiveMessage(event);
				enet_packet_destroy(event.packet);
				break;}
			case ENET_EVENT_TYPE_DISCONNECT:{
				m_dispatcher->onDisconnect(event);
				event.peer->data = NULL;
				break;}
			default: break;
			}
		}
	}else {
		throw ("Exception: Trying process events without conection\n");
	}
	return numProcessedEvents;
}
/**
 * Procesa todos los eventos que hay en la cola con processNextEvent hasta que deja de averlos
 */
void CNetworkClient::processEvents(unsigned long timeout) {
	unsigned eventsProcesed = 0;
	do{
		eventsProcesed = processNextEvent(timeout);
	}while( eventsProcesed );
}

/**
 * Espera hasta recibir algun evento
 */
void CNetworkClient::waitForEvents() {
	while (!processNextEvent());
}

/**
 * Envia un mensaje al servidor conectado
 * @param _msg string con el mensaje a enviar
 */
void CNetworkClient::sendMessage(const std::string& _msg) {
	ENetPacket *packet  = enet_packet_create(_msg.c_str(), _msg.size() + 1,
			ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(m_peer, m_serverSendChannel, packet);
	enet_host_flush(m_client);
	CLOG.print("CLIENT >> Message sended to host\n");
}

/**
 * Libera la memoria del dispatcher actual si es que hay
 */
void CNetworkClient::clearDispatcher() {
	if (m_dispatcher){
		m_dispatcher->destroy();
		m_dispatcher = NULL;
	}
}

void CNetworkClient::copy(const CNetworkClient& _cl) {
	cerr << "########TODO################################## copy CNetworkClient\n";
}




