#pragma once

namespace masterclient {

class CEntity;

class IComponent {
public:
	virtual void refresh(CEntity* _entity) = 0;
	virtual void destroy() = 0;

	virtual ~IComponent() {};
};

} /* namespace masterclient */
