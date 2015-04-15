#include "CLauncherMenuFactory.h"
#include "SLauncherData.h"

namespace masterclient {

CLauncherMenuFactory&
CLauncherMenuFactory::get() {
	static CLauncherMenuFactory j;
	return j;
}

CLauncherMenuFactory::CLauncherMenuFactory() {}

CLauncherMenuFactory::~CLauncherMenuFactory() {}


void CLauncherMenuFactory::createMenuTabControl(
		gui::IGUIEnvironment* _guienv,
		int _windowsWidth,
		int _windowsHeight,
		std::map< std::string, int >& _mapOptions,
		gui::IGUIButton*& _startButton,
		const std::string& _scriptName){

	const s32 leftX = ((float)_windowsWidth)*0.66f;

	// add tab control
	gui::IGUITabControl* tabctrl = _guienv->addTabControl(
			core::rect<int>(leftX,10,_windowsWidth-10,_windowsHeight-10),
			0,
			true,
			true,
			TAB_CONTROL);



	// add list box
	s32 tabControlMargin = 10;
	s32 tabControlWidth = _windowsWidth-leftX-tabControlMargin*3;

	createTabPLManConfig(tabctrl,_guienv,tabControlMargin,tabControlWidth, _scriptName);
	gui::IGUITab* optTab = tabctrl->addTab(L"Configuration");
	createTabCredits(tabctrl,_guienv,tabControlMargin,tabControlWidth);

	s32 listBoxHeight = 110;
	gui::IGUIListBox* box = _guienv->addListBox(
			core::rect<int>(
					tabControlMargin,
					tabControlMargin,
					tabControlWidth+tabControlMargin,
					listBoxHeight+tabControlMargin),
					optTab,
					LST_BOX_DRIVER);
	box->addItem(L"OpenGL 1.5");
	box->addItem(L"Direct3D 8.1");
	box->addItem(L"Direct3D 9.0c");
	box->addItem(L"Burning's Video 0.47");
	box->addItem(L"Irrlicht Software Renderer");
	box->setSelected(_mapOptions["driver"]);

	// add checkbox
	const s32 d = 50;

	_guienv->addCheckBox(_mapOptions["fullscreen"], core::rect<int>(20,85+d,130,110+d),
			optTab, CHK_BOX_FULLSCREEN, L"Fullscreen");
	_guienv->addCheckBox(_mapOptions["music"], core::rect<int>(135,85+d,245,110+d),
			optTab, CHK_BOX_MUSIC, L"Music & Sfx");
	_guienv->addCheckBox(_mapOptions["shadows"], core::rect<int>(20,110+d,135,135+d),
			optTab, CHK_BOX_SHADOWS, L"Realtime shadows");
	_guienv->addCheckBox(_mapOptions["additive"], core::rect<int>(20,135+d,230,160+d),
			optTab, CHK_BOX_ADDITIVE, L"Old HW compatible blending");
	_guienv->addCheckBox(_mapOptions["vsync"], core::rect<int>(20,160+d,230,185+d),
			optTab, CHK_BOX_VSYNC, L"Vertical synchronisation");
	_guienv->addCheckBox(_mapOptions["aa"], core::rect<int>(20,185+d,230,210+d),
			optTab, CHK_BOX_AA, L"Antialiasing");

}


void CLauncherMenuFactory::createTabCredits(
		gui::IGUITabControl *_tabctrl,
		gui::IGUIEnvironment* _guienv,
		int _tabControlMargin,
		int _tabControlWidth) {

	gui::IGUITab* aboutTab = _tabctrl->addTab(L"About");

	// add about text
	const wchar_t* text2 = L"This a AI Learning platform to test your AI algorithms.\n"\
			L"This windows it's a launcher to configure media environment.\n"\
			L"Powered by Irrlicht 3D Engine.\n"\
			L"Developed by:\n Sergio Gallardo\n Rubén Pardo\n  to University of Alicante\n"\
			L"Sponsored by:\n Francisco Gallego.";


	_guienv->addStaticText(
			text2,
			core::rect<int>(
					_tabControlMargin,
					_tabControlMargin,
					_tabControlWidth+_tabControlMargin*2,
					320),
					true,
					true,
					aboutTab);
}

void CLauncherMenuFactory::createTabPLManConfig(
		gui::IGUITabControl *_tabctrl,
		gui::IGUIEnvironment* _guienv,
		int _tabControlMargin,
		int _tabControlWidth,
		const std::string& _scriptName) {



	gui::IGUITab* plmanTab = _tabctrl->addTab(L"PLMan");

	int actualHeight = _tabControlMargin;
	int widthWidgets = 25;

	_guienv->addButton(
			core::rect<int>(
					_tabControlMargin,
					actualHeight,
					30+_tabControlMargin,
					actualHeight+widthWidgets),
					plmanTab,
					BTN_FILE_SCRIPT,
					L"...",
					L"Select script...");

	std::wstring ws;
	ws.assign(_scriptName.begin(), _scriptName.end());
	_guienv->addEditBox(
			ws.c_str(),
			core::rect<int>(
					_tabControlMargin + 50,
					actualHeight,
					_tabControlWidth - (30 + _tabControlMargin),
					actualHeight+widthWidgets),
					true,
					plmanTab,
					EDT_FILE_SCRIPT);

	actualHeight += widthWidgets + _tabControlMargin;

	int editWidth = _tabControlWidth - (50 + _tabControlMargin);
	_guienv->addEditBox(
			L"localhost",
			core::rect<int>(
					_tabControlMargin,
					actualHeight,
					editWidth,
					actualHeight+widthWidgets),
					true,
					plmanTab,
					EDT_SERVER_HOST);

	_guienv->addEditBox(
			L"1234",
			core::rect<int>(
					editWidth + 10,
					actualHeight,
					_tabControlWidth - _tabControlMargin,
					actualHeight+widthWidgets),
					true,
					plmanTab,
					EDT_SERVER_PORT);

	actualHeight += widthWidgets + _tabControlMargin;

	_guienv->addCheckBox(
			true,
			core::rect<int>(
					_tabControlMargin,
					_tabControlMargin + 80,
					_tabControlWidth - _tabControlMargin,
					actualHeight+widthWidgets),
					plmanTab,
					CHK_BOX_BLOCK_PIPES,
					L"Blocking pipes");

}


} /* namespace masterclient */
