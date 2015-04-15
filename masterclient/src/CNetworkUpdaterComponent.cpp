#include "CNetworkUpdaterComponent.h"
#include "CVisualMap.h"
#include "CEntityManager.h"
#include "CNetworkClientDispatcherUpdater.h"

namespace masterclient {

CNetworkUpdaterComponent::CNetworkUpdaterComponent() {}

CNetworkUpdaterComponent::~CNetworkUpdaterComponent() {}

CNetworkUpdaterComponent::CNetworkUpdaterComponent(
		const CNetworkUpdaterComponent& _nuc) {
}

CNetworkUpdaterComponent& CNetworkUpdaterComponent::operator =(
		const CNetworkUpdaterComponent& _nuc) {
	if (this != &_nuc){
		this->~CNetworkUpdaterComponent();
	}
	return *this;
}

/**
 * Recibe la entidad que la posee, busca si existe una actualizacion en el vector de
 * actualizacion del disptacher CNetworkClientDispatcherUpdater comparando el id
 * Si la encuentra actualiza el resto de propiedades (que no son el id) al nuevo valor
 * Si la entidad esta muerta se marca para borrar con EntityManager
 * @param _entity con la entidad propietaria
 */
void CNetworkUpdaterComponent::refresh(CEntity* _entity) {
	VisualMap *update = CNetworkClientDispatcherUpdater::getInstance()->getUpdate();
	if (update) {
		for (unsigned int i = 0; i < update->getWorld().size(); ++i) {
			VisualEntity * entAux = (VisualEntity*) (update->getWorld()[i]);
			if (_entity->getId() == entAux->getID()) {
				if (entAux->getAlive()) {
					_entity->setPosition(
							irr::core::vector2d < irr::s32
							> (entAux->getX(), entAux->getY()));
				} else {
					//La hacemos invisible
					_entity->setVisible(false);
					//La borramos del vector principal y la ponemos para ser borrada
					CEntityManager::getInstance().removeEntity(_entity);
				}
				break;
			}

		}

	}

}

/**
 * Constructor para llamarlo cuando se necesite y decidir lo que se hace
 * Por defecto se suicida
 */
void CNetworkUpdaterComponent::destroy() {
	delete this;
}
/* namespace masterclient */

}

