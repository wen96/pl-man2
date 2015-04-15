#pragma once

#include <irrlicht.h>
#include <iostream>
#include <map>


using namespace irr;

namespace masterclient {

class CLauncherEventReceiver;

/**
 * Class to configure media environment for aplication
 * Creates a windows with forms to leave to the user select a configuration
 * that after will be write to a config file
 */
class CLauncherWindow
{
public:

	CLauncherWindow();

	bool run();

	typedef std::map< std::string, int > TMapOptions;

	TMapOptions m_mapOptions;

	void loadFromFile();
	void saveToFile();

	bool isStart() const;
	void setStart(bool start);
	const std::string& getDefaultScript() const;
	void setDefaultScript(const std::string& defaultScript);
	const std::string& getHost() const;
	void setHost(const std::string& host);
	int getPort() const;
	void setPort(int port);

private:

	gui::IGUIButton* m_startButton;
	IrrlichtDevice * m_menuDevice;
	CLauncherEventReceiver *m_er;
	io::path m_directoryBin;
	s32 m_selected;

	s32 m_windowsWidth;
	s32 m_windowsHeight;

	bool m_start;

	std::string m_fileName;
	std::string m_defaultScript;
	std::string m_host;
	int m_port;

	void createWindow();
	void createMenu();
};

}

