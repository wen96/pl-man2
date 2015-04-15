#pragma once

#include "CNetworkClientDispatcher.h"
#include "IComponent.h"
#include "CEntity.h"
#include "CVisualMap.h"

namespace masterclient {

/**
 * Clase Dispatcher de cliente para recibir la diferentes actualizaciones que se iran recibiendo
 * desde el servidor
 */
class CNetworkClientDispatcherUpdater: public CNetworkClientDispatcher {
public:
	//TODO: Singleton implementado mal, ahora mismo le hace delete CMasterMan
	static CNetworkClientDispatcherUpdater* getInstance();

	virtual ~CNetworkClientDispatcherUpdater();

	// Herencia CNetworkClientDispatcher
	virtual void onReceiveMessage(const ENetEvent& _event);
	virtual void defaultMessageHandler(const std::string& str);
	void destroy();

	//Acciones especificas
	virtual void handleVisualMap(const std::string& _str);
	virtual void handleVisualEntity(const std::string& _str);

	VisualMap* getUpdate() const;
private:
	static CNetworkClientDispatcherUpdater *m_instance;
	CNetworkClientDispatcherUpdater(CNetworkClient* _owner);

	VisualMap *m_update;
};

} /* namespace masterclient */
