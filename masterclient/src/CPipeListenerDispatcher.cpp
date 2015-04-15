#include "CPipeListenerDispatcher.h"
#include "CLog.h"
#include "CJsonCommand.h"
#include "CMasterMan.h"
#include <string>
#include <sstream>

namespace masterclient {

CPipeListenerDispatcher::CPipeListenerDispatcher() {
	// TODO Auto-generated constructor stub

}

CPipeListenerDispatcher::~CPipeListenerDispatcher() {
	// TODO Auto-generated destructor stub
}

CPipeListenerDispatcher::CPipeListenerDispatcher(
		const CPipeListenerDispatcher& _obj) {
}

CPipeListenerDispatcher& CPipeListenerDispatcher::operator =(
		const CPipeListenerDispatcher& _obj) {

	return *this;
}

void CPipeListenerDispatcher::splitBy(const std::string& _text, std::vector<std::string>& _vec, char _separator) {
	std::istringstream bufferstream;
	bufferstream.clear();
	bufferstream.str(_text);
	bufferstream >> std::ws;
	std::string command = "";

	_vec.clear();
	while(std::getline(bufferstream,command,_separator)){
		_vec.push_back(command);
	}
}


bool CPipeListenerDispatcher::onReceiveMessage(const std::string& _msg) {
	// Trocemos el comando por espacios
	std::vector<std::string> commands;
	splitBy(_msg,commands,' ');

	// Comprobamos el tipo de comando que es
	CJsonCommand helper;
	CJsonCommand::ECommand comm1 = helper.stringToCommand(commands[0]);

	CLOG.print("PIPE >> Get it command %s\n",_msg.c_str());

	//Si no es un comando valido lo procesamos mostranco por pantalla
	if (comm1 == CJsonCommand::CM_NULL){
		defaultHandler(_msg);
	}else{
		//Creamos el commando
		CJsonCommand com = CJsonCommand(comm1);

		//Anyadimos sus parametros
		if (commands.size()>1){
			com.addParameter(new CJsonCommand(com.stringToCommand(commands[1])));
		}
		//Y lo lanzamos al servidor
		CMasterMan::get().launchCommand(com);
	}

	//Comprobamos si un comando de accion o no
	return CJsonCommand::isActionCommand(comm1);
}



void CPipeListenerDispatcher::defaultHandler(const std::string& _msg) {
	CLOG.print("Pipe receive >> %s\n", _msg.c_str());
}

}




/* namespace masterclient */
