#include "CNetworkClientDispatcherInitializer.h"
#include "CEntityManager.h"

namespace masterclient {

CNetworkClientDispatcherInitializer::CNetworkClientDispatcherInitializer(CNetworkClient* _owner):CNetworkClientDispatcher(_owner) {
	CLOG.print("Initializer > Creado\n");
}

CNetworkClientDispatcherInitializer::~CNetworkClientDispatcherInitializer() {
	// TODO Auto-generated destructor stub
}

void CNetworkClientDispatcherInitializer::onConnect(const ENetEvent& event) {
	CLOG.print("Initializer > Conected to server\n");
}

void CNetworkClientDispatcherInitializer::onReceiveMessage(
		const ENetEvent& event) {
	CLOG.print("Initializer > Mensaje del servidor inicializando\n");
	//Convertimos a string el mensaje
	std::string res((const char*)event.packet->data);
	//y se lo pasamos al handler por defecto que lo interpretara como el mundo serializado
	defaultMessageHandler(res);

}

void CNetworkClientDispatcherInitializer::onDisconnect(const ENetEvent& event) {
	CLOG.print("Initializer > Desconectado\n");
}

void CNetworkClientDispatcherInitializer::defaultMessageHandler(
		std::string str) {
	//Deseralizo de json el mapa pasado
	VisualMap vmEstupido;
	VisualMap* vm = (VisualMap*)vmEstupido.json_deserialize(str);

	//Recorro el vector de las entidades y voy anyadiendolas al mundo para pintarlas
	vector<IJsonSerializable*> world = vm->getWorld();
	for (unsigned int i = 0; i < world.size(); i++){
		VisualEntity * entAux = (VisualEntity*)world[i];

		CEntityManager::getInstance().addEntity(entAux->getX(),entAux->getY(), entAux->getType(),entAux->getID());
	}
	if (vm){
		delete vm;
	}
}

void CNetworkClientDispatcherInitializer::destroy() {
	delete this;
}

CNetworkClientDispatcher* CNetworkClientDispatcherInitializer::run() {
	return this;
}

} /* namespace masterclient */
