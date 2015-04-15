#pragma once

#include<iostream>
#include<string>
#include<vector>

namespace masterclient {

class CPipeListenerDispatcher {
public:
	// Forma canonica
	CPipeListenerDispatcher();
	virtual ~CPipeListenerDispatcher();
	CPipeListenerDispatcher(const CPipeListenerDispatcher& _obj);
	CPipeListenerDispatcher & operator=(const CPipeListenerDispatcher& _obj);

	// Funrionces principales
	bool onReceiveMessage(const std::string& _msg);
	void defaultHandler(const std::string& _msg);
	void splitBy(const std::string& _text, std::vector<std::string>& _vec, char _separator);
};

} /* namespace masterclient */
