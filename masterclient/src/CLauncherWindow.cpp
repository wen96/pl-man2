#include "CLauncherWindow.h"
#include "CLauncherMenuFactory.h"
#include "CLauncherEventReceiver.h"
#include "SLauncherData.h"

#include <fstream>
#include <string>
#include <sstream>

namespace masterclient {

CLauncherWindow::CLauncherWindow()
: m_startButton(0), m_menuDevice(0), m_er(0), m_selected(2),
  m_windowsWidth(800), m_windowsHeight(600), m_start(false),
  m_fileName("./plman.config"), m_defaultScript("")
{
	// You need to initialize value for save it in saveToFile function
	m_mapOptions["driver"] = 2;
	m_mapOptions["fullscreen"] = false;
	m_mapOptions["music"] = false;
	m_mapOptions["shadows"] = false;
	m_mapOptions["additive"] = false;
	m_mapOptions["vsync"] = false;
	m_mapOptions["aa"] = false;
	m_mapOptions["pipes"] = false;
	m_host = "localhost";
	m_port = 1234;
}


bool CLauncherWindow::run()
{
	loadFromFile();

	createWindow();

	createMenu();

	video::IVideoDriver* driver = m_menuDevice->getVideoDriver();
	scene::ISceneManager* smgr = m_menuDevice->getSceneManager();
	gui::IGUIEnvironment* guienv = m_menuDevice->getGUIEnvironment();

	// set ambient light (no sun light in the catacombs)
	smgr->setAmbientLight( video::SColorf(0.2f, 0.2f, 0.2f) );

	// create a fixed camera
	smgr->addCameraSceneNode(0, core::vector3df(45,0,0), core::vector3df(0,0,10));

	video::ITexture* irrlichtBack = driver->getTexture("../MasterClient/media/plmanback.png");

	bool oldMipMapState = driver->getTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS);
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, oldMipMapState);

	// draw all

	while(m_menuDevice->run())
	{
		if (m_menuDevice->isWindowActive())
		{
			driver->beginScene(false, true, video::SColor(0,0,0,0));

			if (irrlichtBack)
				driver->draw2DImage(irrlichtBack,
						core::position2d<int>(0,0));

			smgr->drawAll();
			guienv->drawAll();
			driver->endScene();
		}
	}

	saveToFile();

	m_menuDevice->drop();
	delete m_er;

	return m_start;
}
void CLauncherWindow::createWindow() {
	video::E_DRIVER_TYPE driverType = video::EDT_SOFTWARE;

	m_er = new CLauncherEventReceiver(NULL, this);
	m_menuDevice = createDevice(
			driverType,
			core::dimension2d<u32>(m_windowsWidth, m_windowsHeight),
			16, false, false, false,
			m_er);
	m_er->setMenuDevice(m_menuDevice);

	core::stringw str = "PLMan v2.0";
	m_menuDevice->setWindowCaption(str.c_str());
	m_directoryBin = m_menuDevice->getFileSystem()->getWorkingDirectory();
}

const std::string& CLauncherWindow::getHost() const {
	return m_host;
}

void CLauncherWindow::setHost(const std::string& host) {
	m_host = host;
}

int CLauncherWindow::getPort() const {
	return m_port;
}

void CLauncherWindow::setPort(int port) {
	m_port = port;
}

void CLauncherWindow::createMenu() {
	gui::IGUIEnvironment* guienv = m_menuDevice->getGUIEnvironment();

	s32 margin = 10;

	// set new Skin
	gui::IGUISkin* newskin = guienv->createSkin(gui::EGST_BURNING_SKIN);
	gui::IGUIFont* font = guienv->getFont("../MasterClient/media/fontcourier.bmp");
	newskin->setFont(font);
	guienv->setSkin(newskin);

	// add button
	s32 buttonHeight = 40;
	s32 buttonWidth = 250;
	m_startButton = guienv->addButton(
			core::rect<int>(
					margin,
					m_windowsHeight-(buttonHeight+margin),
					buttonWidth+margin,
					m_windowsHeight-margin),
					0,
					BTN_START,
					L"Start PLMan");
	m_startButton->setToolTipText(L"Click to start the game");

	newskin->drop();

	// add tab control
	CLauncherMenuFactory::get().createMenuTabControl(
			guienv,
			m_windowsWidth,
			m_windowsHeight,
			m_mapOptions,
			m_startButton,
			m_defaultScript);

}

void CLauncherWindow::loadFromFile() {
	std::ifstream myfile;
	myfile.open (m_fileName.c_str());
	std::string line = "";
	while (getline(myfile,line)){
		std::istringstream bufferstream;
		bufferstream.clear();
		bufferstream.str(line);
		bufferstream >> std::ws;

		std::string key = "",value = "";
		std::getline(bufferstream,key,':');
		std::getline(bufferstream,value,':');

		if (key == "script")
		{
			m_defaultScript = value.c_str();

		} else if (key == "host"){
			m_host = value.c_str();
		} else if (key == "port"){
			m_port = atoi(value.c_str());
		} else {
			// Testing if key is a valid value (is set it in the constructor)
			std::map<std::string, int>::iterator iter = m_mapOptions.find(key);
			if (iter != m_mapOptions.end()){
				m_mapOptions[key] = atoi(value.c_str());
			}
		}
	}
	myfile.close();
}

const std::string& CLauncherWindow::getDefaultScript() const {
	return m_defaultScript;
}

void CLauncherWindow::setDefaultScript(const std::string& defaultScript) {
	m_defaultScript = defaultScript;
}

void CLauncherWindow::saveToFile() {
	m_menuDevice->getFileSystem()->changeWorkingDirectoryTo(m_directoryBin);
	std::ofstream myfile;
	myfile.open (m_fileName.c_str());

	std::map<std::string, int>::iterator iter;

	for (iter = m_mapOptions.begin(); iter != m_mapOptions.end(); ++iter) {
		myfile << (iter->first) << ":" << (iter->second) << "\n";
	}
	myfile << "script:" << m_defaultScript << "\n";
	myfile << "host:" << m_host << "\n";
	myfile << "port:" << m_port << "\n";

	myfile.close();
}


bool CLauncherWindow::isStart() const {
	return m_start;
}

void CLauncherWindow::setStart(bool start) {
	m_start = start;
}

}


