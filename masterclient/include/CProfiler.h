#pragma once

#include <iostream>
#include <map>

namespace masterclient {

class CProfiler {
public:

	virtual ~CProfiler();
	static CProfiler& get();

	void tick(const std::string &_key, unsigned int _value);
	void tack(const std::string &_key, unsigned int _value);

	unsigned int getTime(const std::string &_key);
	int getPercentage(const std::string &_key, const std::string &_about);
	void print();
private:
	CProfiler();
	std::map< std::string, unsigned int > m_ticks;
	std::map< std::string, unsigned int > m_tacks;
};

} /* namespace masterclient */

