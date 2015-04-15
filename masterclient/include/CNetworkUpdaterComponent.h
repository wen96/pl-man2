#pragma once

#include "IComponent.h"

namespace masterclient {

/**
 * Componente que consulta la actualizacion del dispatcher de actualizacion y actualiza la entidad
 * al respecto de la misma
 */
class CNetworkUpdaterComponent : public IComponent {
public:
	// Forma canonica
	CNetworkUpdaterComponent();
	virtual ~CNetworkUpdaterComponent();
	CNetworkUpdaterComponent(const CNetworkUpdaterComponent& _nuc);
	CNetworkUpdaterComponent& operator=(const CNetworkUpdaterComponent& _nuc);

	// Herencia IComponent
	void refresh(CEntity* _entity);
	void destroy();
};

} /* namespace masterclient */
