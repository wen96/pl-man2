#pragma once

#include <string>
#include "fdstream.h"
#include "CPipeListenerDispatcher.h"

namespace masterclient {

/**
 * Clase a la que se le pasa la ruta a un ejecutable, lo lanza y se comunica con el
 * a traves de pipes conectados a su salida y su entrada estandar
 */
class CPipeListener {
public:
	//Forma canonica
	CPipeListener(std::string _program);
	virtual ~CPipeListener();
	CPipeListener(const CPipeListener& _obj);
	CPipeListener & operator=(const CPipeListener& _obj);

	// Funciones prinicipales
	void runProgramAndReadyPipes();
	std::string getMessage();
	void sendMessage(const std::string& _msg);
	void processMessages();
	bool processNextMessage();
	void closePipes();

	// GETTERS AND SETTERS
	bool isBlockPipes() const;
	void setBlockPipes(bool blockPipes);
	CPipeListenerDispatcher* getDispatcher() const;
	void setDispatcher(CPipeListenerDispatcher* dispatcher);
	boost::fdistream* getInstreamp() const;
	void setInstreamp(boost::fdistream* instreamp);
	boost::fdostream* getOutstreamp() const;
	void setOutstreamp(boost::fdostream* outstreamp);
	const int* getPipes() const;
	std::string getProgramFile() const;
	void setProgramFile(std::string programFile);
private:
	void copy(const CPipeListener& _obj);

	std::string m_programFile;

	boost::fdostream* m_outstreamp;
	boost::fdistream* m_instreamp;

	int m_pipes[2];
	int m_childPid;

	CPipeListenerDispatcher *m_dispatcher;

	bool m_blockPipes;
};

} /* namespace masterclient */
