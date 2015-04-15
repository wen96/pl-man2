#include "CPipeListener.h"
#include <iostream>
#include <stdlib.h>
#include <fcntl.h> //fcntl bloqueante
#include <sys/stat.h> //stat permisos
#include <sstream> //stringstream
#include <sys/resource.h> //setpriority getpriority
#include <signal.h> // kill SIGTERM
#include "CLauncher.h"

namespace masterclient {

CPipeListener::CPipeListener(std::string _program) {
	m_programFile = _program;
	m_outstreamp = NULL;
	m_instreamp = NULL;
	m_dispatcher = NULL;
	m_pipes[0] = -1;
	m_pipes[1] = -1;
	m_blockPipes =  CLauncher::get().getOption(PIPES_OPTION);
	m_childPid = -1;

	m_dispatcher = new CPipeListenerDispatcher();
}

CPipeListener::~CPipeListener() {
	m_programFile = "";

	this->closePipes();

	if (m_dispatcher){
		delete m_dispatcher;
	}
	m_dispatcher = NULL;

	if( m_instreamp != NULL ){
		delete m_instreamp;
	}
	m_instreamp = NULL;
	if( m_outstreamp != NULL ){
		delete m_outstreamp;
	}
	m_outstreamp = NULL;


	m_blockPipes = false;
}

void CPipeListener::runProgramAndReadyPipes() {
	this->closePipes();

	if (m_childPid != -1){
		kill(m_childPid, SIGTERM);
	}

	//Creamos arrays para almacenar los descriptores de los pipes
	int pipe_in[2];
	int pipe_out[2];

	//Creamos un pipe de entrada
	if (pipe(pipe_in)){
		throw "Error: Problema creando el pipe de entrada";
	}

	//Creamos el pipe de salida
	if (pipe(pipe_out)){
		throw  "Error: Problema creando el pipe de salida";
	}
	m_childPid = fork();
	if (m_childPid==0){//el hijo

		// Hacemos el pipe_out la entrada estandar para el hijo
		close(pipe_out[1]);
		dup2(pipe_out[0], STDIN_FILENO);

		// Hacemos el pipe_in la salida estandar
		dup2(pipe_in[1],STDOUT_FILENO);
		close(pipe_in[0]);

		// Make the pipes non-blocking
		if(!m_blockPipes)
		{
			int pd_flags;
			if( (pd_flags = fcntl(pipe_out[0], F_GETFL, 0)) == -1 )
				throw ("Couldn't get pd_flags for pipe_out in file ");
			pd_flags |= O_NONBLOCK;
			if( fcntl(pipe_out[0], F_SETFL, pd_flags) == -1 )
				throw ("Couldn't change pd_flags for pipe_out in file ");
			if( (pd_flags = fcntl(pipe_in[1], F_GETFL, 0)) == -1 )
				throw ("Couldn't get pd_flags for pipe_in in file ");
			pd_flags |= O_NONBLOCK;
			if( fcntl(pipe_in[1], F_SETFL, pd_flags) == -1 )
				throw ("Couldn't change pd_flags for pipe_in in file ");
		}

		// Check file attributes
		struct stat filestat;
		if( 0 != stat(m_programFile.c_str(), &filestat ) )
			throw ("Couldn't get stats for file ");
		if( !S_ISREG( filestat.st_mode) )
			throw ("Client file isn't regular, error for file ");
		if( !(filestat.st_mode & S_IXOTH) )
			throw ("Client file isn't executable for user, error for file ");
		if( (filestat.st_mode & S_ISUID) )
			throw ("Set user ID is not allowed, error for file ");

		// Lower priority by one
		int old;
		if( (old = getpriority (PRIO_PROCESS, 0)) == -1 )
			throw ("Couldn't get priority for robot ");
		if( setpriority (PRIO_PROCESS, 0, old + 1) == -1)
			throw ("Couldn't set priority for robot ");


		if( execl(m_programFile.c_str(), m_programFile.c_str(), NULL) == -1 )
			// we are in another process so exiting does not solve the problem
			throw ("Couldn't open file ");

		throw ("Executable didn't execute, SHOULD NEVER HAPPEN!, error for file");


	}else{//el padre
		close(pipe_out[0]);     // Close input side of pipe_out
		close(pipe_in[1]);      // Close output side of pipe_in

		m_pipes[0] = pipe_out[1];
		m_pipes[1] = pipe_in[0];

		// Make the pipes non-blocking
		int pd_flags;
		if( (pd_flags = fcntl(pipe_in[0], F_GETFL, 0)) == -1 )
			throw ("Couldn't get pd_flags for pipe_in in file ");
		pd_flags |= O_NONBLOCK;
		if( fcntl(pipe_in[0], F_SETFL, pd_flags) == -1 )
			throw ("Couldn't change pd_flags for pipe_in in file ");
		if( (pd_flags = fcntl(pipe_out[1], F_GETFL, 0)) == -1 )
			throw ("Couldn't get pd_flags for pipe_out in file ");
		pd_flags |= O_NONBLOCK;
		if( fcntl(pipe_out[1], F_SETFL, pd_flags) == -1 )
			throw ("Couldn't change pd_flags for pipe_out in file ");

		if( m_instreamp != NULL ) delete m_instreamp;
		m_instreamp = new boost::fdistream(pipe_in[0]);

		if( m_outstreamp != NULL ) delete m_outstreamp;
		m_outstreamp = new boost::fdostream(pipe_out[1]);

	}
}

std::string CPipeListener::getMessage() {
	if (m_instreamp == NULL) throw "Error: In stream is not initialized";

	string result = "";
	char c[1];



	// input stream is set to good status again
	m_instreamp->clear();
	m_instreamp->peek();
	if (!m_instreamp->good()){
		return "";
	}

	m_instreamp->read(c,1);
	while (c[0] != '\n'){
		result += c[0];
		m_instreamp->read(c,1);
	}

	return result;
}

bool CPipeListener::processNextMessage() {
	bool actionCommand = false;
	std::string command = getMessage();
	if (command != ""){
		//onReceiveMessage devuelve true si procesa un comando de accion y false si no
		actionCommand = (m_dispatcher->onReceiveMessage(command));
	}

	return actionCommand;
}

void CPipeListener::processMessages() {
	if (m_instreamp == NULL) throw "Error: In stream is not initialized";

	std::string command = getMessage();
	while (command != ""){
		m_dispatcher->onReceiveMessage(command);
		command = getMessage();
	}

}

void CPipeListener::sendMessage(const std::string& _msg) {
	if (m_outstreamp == NULL) throw "Error: Out stream is not initialized";
	(*m_outstreamp) << _msg << endl;
}

CPipeListener::CPipeListener(const CPipeListener& _obj) {
	copy(_obj);
}

CPipeListener& CPipeListener::operator =(const CPipeListener& _obj) {
	if (&_obj != this){
		this->~CPipeListener();
		copy(_obj);
	}
	return *this;
}

void CPipeListener::closePipes() {
	if (m_pipes[0] != -1) {
		close (m_pipes[0]);
		m_pipes[0] = -1;
	}
	if (m_pipes[1] != -1) {
		close (m_pipes[1]);
		m_pipes[1] = -1;
	}
}


/* namespace masterclient */
void CPipeListener::copy(const CPipeListener& _obj) {
	m_programFile = _obj.getProgramFile();
	m_blockPipes = _obj.isBlockPipes();
	m_dispatcher = new CPipeListenerDispatcher(*_obj.getDispatcher());
	m_instreamp = NULL;
	m_outstreamp = NULL;
	m_pipes[0] = _obj.getPipes()[0];
	m_pipes[1] = _obj.getPipes()[1];
}



/// GETTERS AND SETTERS
bool CPipeListener::isBlockPipes() const {
	return m_blockPipes;
}

void CPipeListener::setBlockPipes(bool blockPipes) {
	m_blockPipes = blockPipes;
}

CPipeListenerDispatcher* CPipeListener::getDispatcher() const {

	return m_dispatcher;
}

void CPipeListener::setDispatcher(CPipeListenerDispatcher* dispatcher) {
	if (m_dispatcher){
		delete m_dispatcher;
	}
	m_dispatcher = dispatcher;
}

boost::fdistream* CPipeListener::getInstreamp() const {
	return m_instreamp;
}

void CPipeListener::setInstreamp(boost::fdistream* instreamp) {
	if (m_instreamp){
		delete m_instreamp;
	}
	m_instreamp = instreamp;
}

boost::fdostream* CPipeListener::getOutstreamp() const {
	return m_outstreamp;
}

void CPipeListener::setOutstreamp(boost::fdostream* outstreamp) {
	if (m_outstreamp){
		delete m_outstreamp;
	}
	m_outstreamp = outstreamp;
}

const int* CPipeListener::getPipes() const {
	return m_pipes;
}

std::string CPipeListener::getProgramFile() const {
	return m_programFile;
}

void CPipeListener::setProgramFile(std::string programFile) {
	m_programFile = programFile;}

}

