#include "CLauncher.h"

namespace masterclient {

CLauncher& CLauncher::get() {
	static CLauncher instance;
	return instance;
}

bool CLauncher::run() {
	return m_windowLauncher.run();
}

const std::string& CLauncher::getScriptFileName() const {
	return m_windowLauncher.getDefaultScript();
}

void CLauncher::loadConfig() {
	m_windowLauncher.loadFromFile();
}

std::map<std::string, int> CLauncher::getOptions() {
	return m_windowLauncher.m_mapOptions;
}

int CLauncher::getOption(std::string _option) {
	return m_windowLauncher.m_mapOptions[_option];
}

const std::string& CLauncher::getHost() const {
	return m_windowLauncher.getHost();
}

int CLauncher::getPort() {
	return m_windowLauncher.getPort();
}

CLauncher::CLauncher() {
	// TODO Auto-generated constructor stub

}

CLauncher::~CLauncher() {
	// TODO Auto-generated destructor stub
}

} /* namespace masterclient */
