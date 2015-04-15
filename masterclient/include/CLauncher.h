#pragma once

#include <iostream>

#include "CLauncherWindow.h"
#include "SLauncherData.h"

namespace masterclient {

class CLauncher {
public:

	static CLauncher& get();
	virtual ~CLauncher();

	bool run();


	const std::string& getScriptFileName() const;
	const std::string& getHost() const;
	int getPort();
	void loadConfig();
	std::map< std::string, int > getOptions();
	int getOption(std::string _option);

private:
	CLauncher();

	CLauncherWindow m_windowLauncher;
};

} /* namespace masterclient */

