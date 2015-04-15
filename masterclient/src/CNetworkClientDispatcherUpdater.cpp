#include "CNetworkClientDispatcherUpdater.h"
#include "CEntityManager.h"
#include "CMasterMan.h"
#include "CJsonCustomData.h"

namespace masterclient {
CNetworkClientDispatcherUpdater* CNetworkClientDispatcherUpdater::m_instance;

CNetworkClientDispatcherUpdater* CNetworkClientDispatcherUpdater::getInstance() {
	if (m_instance == NULL){
		m_instance = new CNetworkClientDispatcherUpdater(NULL);
	}
	return m_instance;
}

void CNetworkClientDispatcherUpdater::destroy() {
}

CNetworkClientDispatcherUpdater::CNetworkClientDispatcherUpdater(
		CNetworkClient* _owner) :
														CNetworkClientDispatcher(_owner) {
	m_update = NULL;
}

CNetworkClientDispatcherUpdater::~CNetworkClientDispatcherUpdater() {
	if (m_update){
		delete m_update;
		m_update = NULL;
	}
}


void CNetworkClientDispatcherUpdater::onReceiveMessage(const ENetEvent& _event) {

	//Convertimos a string el mensaje
	std::string res((const char*) (((_event.packet->data))));

	//CLOG.print("Updater >> Mensaje del servidor Actualizando %s\n",res.c_str());

	//y se lo pasamos al handler por defecto que lo interpretara como el mundo serializado
	defaultMessageHandler(res);
}

void CNetworkClientDispatcherUpdater::defaultMessageHandler(const std::string& _str) {
	CJsonSerializer helper("");
	CJsonSerializer *c2 = (CJsonSerializer *)helper.json_deserialize(_str);
	std::string type = c2->typeName();
	//CLOG.print("Updater >> Getting from server message type %s.\n",type.c_str());
	//CLOG.print("Updater >> Getting from server message %s.\n",_str.c_str());

	if (type=="visual_map"){
		handleVisualMap(_str);
	}else if (type=="visual_entity") {
		handleVisualEntity(_str);
	}
	if (c2) delete c2;
}
/**
 * Acciones cuando se recibe un visual map
 */
void CNetworkClientDispatcherUpdater::handleVisualMap(const std::string& _str) {
	CJsonSerializer helper("");
	VisualMap* vm = (VisualMap*) ((helper.json_deserialize(_str)));

	if (m_update){
		delete m_update;
		m_update = NULL;
	}
	m_update = vm;

	if (vm->getWorld().size()>0){
		CEntityManager::getInstance().refresh();
	}

	std::string messageToPipe = "continue";
	if (vm->getFinish()){
		if (vm->getWin()){
			messageToPipe = "win";
		}else{
			messageToPipe = "lose";
		}
	}

	cJsonCustomData jsData = cJsonCustomData("status", messageToPipe);
	CMasterMan::get().sendMessageToPipe(jsData.json_serialize());

	if (vm->getFinish()){
		CMasterMan::get().setFinished(true, vm->getWin(), vm->getHeight());//TODO
	}
}
/**
 * Acciones cuando se devuelve un visual entity
 */
void CNetworkClientDispatcherUpdater::handleVisualEntity(const std::string& _str) {
	CJsonSerializer helper("");
	VisualEntity* vm = (VisualEntity*) ((helper.json_deserialize(_str)));
	std::stringstream stream;
	stream << _str.c_str();
	CMasterMan::get().sendMessageToPipe(stream.str());
	delete vm;
}

/**
 * Devuelve la ultima actualizacion que se recibio desde el servidor
 * @return
 */
VisualMap* CNetworkClientDispatcherUpdater::getUpdate() const {
	return m_update;
}

/* namespace masterclient */

}

