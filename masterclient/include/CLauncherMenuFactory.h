#pragma once

#include <irrlicht.h>
#include <iostream>
#include <map>

using namespace irr;

namespace masterclient {

class CLauncherMenuFactory {
public:
	static CLauncherMenuFactory& get();
	virtual ~CLauncherMenuFactory();

	void createMenuTabControl(
			gui::IGUIEnvironment* _guienv,
			int _windowsWidth,
			int _windowsHeight,
			std::map< std::string, int >& _mapOptions,
			gui::IGUIButton*& _startButton,
			const std::string& _scriptName);

	void createTabCredits(
			gui::IGUITabControl *_tabctrl,
			gui::IGUIEnvironment* _guienv,
			int _tabControlMargin,
			int _tabControlWidth);

	void createTabPLManConfig(
			gui::IGUITabControl *_tabctrl,
			gui::IGUIEnvironment* _guienv,
			int _tabControlMargin,
			int _tabControlWidth,
			const std::string& _scriptName);

private:

	CLauncherMenuFactory();

};

} /* namespace masterclient */
