#include "CProfiler.h"

namespace masterclient {

CProfiler& CProfiler::get() {
	static CProfiler serv;
	return serv;
}

void CProfiler::tick(const std::string& _key, unsigned int _value) {
	m_ticks[_key] = _value;
}

void CProfiler::tack(const std::string& _key, unsigned int _value) {
	m_tacks[_key] = _value;
}

unsigned int CProfiler::getTime(const std::string& _key) {
	return m_tacks[_key] - m_ticks[_key];
}

void CProfiler::print() {
	std::map<std::string, unsigned int>::iterator iter;
	for (iter = m_ticks.begin(); iter != m_ticks.end(); ++iter) {
		std::cout << (iter->first) << ":" << (iter->second) << "\n";
	}
	std::map<std::string, unsigned int>::iterator iter2;
	for (iter2 = m_tacks.begin(); iter2 != m_tacks.end(); ++iter2) {
		std::cout << (iter2->first) << ":" << (iter2->second) << "\n";
	}
	std::cout << "------------------------------" << std::endl;
}

int CProfiler::getPercentage(const std::string& _key,
		const std::string& _about) {
	return (int) (( ((float)getTime(_key)) / ((float)getTime(_about)) )*100.0f);
}

CProfiler::CProfiler() {
	// TODO Auto-generated constructor stub

}

CProfiler::~CProfiler() {
	// TODO Auto-generated destructor stub
}

} /* namespace masterclient */
