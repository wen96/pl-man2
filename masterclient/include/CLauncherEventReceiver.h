#pragma once

#include <irrlicht.h>
#include <iostream>
#include <map>

#include "CLauncherWindow.h"

using namespace irr;

namespace masterclient {

class CLauncherEventReceiver : public IEventReceiver {
public:
	CLauncherEventReceiver(
			IrrlichtDevice *_device,
			CLauncherWindow* _window);
	virtual ~CLauncherEventReceiver();

	virtual bool OnEvent(const SEvent& event);
	bool OnGUIElementEvent(const SEvent& event);

	void setLauncherWindow(CLauncherWindow* launcherWindow);
	void setMenuDevice(IrrlichtDevice* menuDevice);

private:
	IrrlichtDevice * m_menuDevice;

	CLauncherWindow * m_launcherWindow;
};

} /* namespace masterclient */
