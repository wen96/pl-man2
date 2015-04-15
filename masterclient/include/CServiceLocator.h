#pragma once

#include <irrlicht.h>

#define CSERVICELOCATOR CServiceLocator::get()

namespace masterclient {


/**
 * En una clase que simplemente se dedica a ofrecer punteros a ciertas clases que se usan mucho
 */
class CServiceLocator {
public:

	virtual ~CServiceLocator();
	static CServiceLocator& get();

	irr::scene::ISceneManager * getSceneManager() const;
	irr::IrrlichtDevice* getDevice() const;
	irr::video::IVideoDriver* getDriver() const;
	irr::scene::ISceneNode* getRootSceneNode() const;
	irr::u32 getTime() const;

	void setDevice(irr::IrrlichtDevice* _device);


private:

	CServiceLocator();

	irr::IrrlichtDevice * m_device;
};

} /* namespace masterclient */
