#include "CJsonCommand.h"
#include <boost/assign/list_of.hpp>
#include <string>
#include <jsoncpp/json/json.h>

///////////////////////////////////////////////////////////////////////////////
/// \brief CJsonCommand constructor
///////////////////////////////////////////////////////////////////////////////
CJsonCommand::CJsonCommand(ECommand c)
: CJsonSerializer("command"),
  m_command(c)
{
	// Assign command string to enum values for each command
	m_command2String = boost::assign::map_list_of
			(CM_NULL,         "null")
	(CM_INIT,          "init")
	(CM_SEE,          "see")
	(CM_GET,          "get")
	(CM_DROP,         "drop")
	(CM_USE,          "use")
	(CM_MOVE,         "move")
	(CM_EXIT,         "exit")
	(CM_INTERACT,         "interact")

	(CM_UP,         "up")
	(CM_LEFT,          "left")
	(CM_RIGHT,          "right")
	(CM_DOWN,         "down")
	(CM_UPLEFT,          "upleft")
	(CM_UPRIGHT,         "upright")
	(CM_DOWNLEFT,         "downleft")
	(CM_DOWNRIGHT,         "downright")
	(CM_NONE,         "none")
	(CM_NUMCOMMANDS,  "");

	// And automatically assing values in reverse to the second map
	std::map <ECommand, std::string>::iterator it;
	for (it = m_command2String.begin(); it != m_command2String.end(); ++it )
		m_string2Command[it->second] = it->first;
}

CJsonCommand::CJsonCommand(const CJsonCommand& _comm)
: CJsonSerializer("command"){
	copy(_comm);
}

CJsonCommand& CJsonCommand::operator =(const CJsonCommand& _comm) {
	if (this != &_comm){
		this->destroy();
		copy(_comm);
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Reset a command to null command
///////////////////////////////////////////////////////////////////////////////
void
CJsonCommand::reset() {
	m_command = CM_NULL;
}


///////////////////////////////////////////////////////////////////////////////
/// \brief CJsonCommand destructor
///////////////////////////////////////////////////////////////////////////////
CJsonCommand::~CJsonCommand() {
	for (unsigned i=0; i < m_parameters.size(); i++){
		delete m_parameters[i];
	}
	reset();
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Writes the contents of the object to a json value
///
/// \param v JSon value reference where to write the content
///////////////////////////////////////////////////////////////////////////////
void
CJsonCommand::write2json(Json::Value& v) const {
	Json::Value dataVector(Json::arrayValue);

	// JSON Command value
	v["type"]    = "command";
	v["command"] = m_command2String.at(m_command);

	// JSON Parameters value
	if (m_parameters.size() > 0 ) {
		for(unsigned i=0; i < m_parameters.size(); i++) {
			Json::Value pv;
			m_parameters[i]->write2json(pv);
			dataVector.append( pv );
		}

		v["data"] = dataVector;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Set the contents of the object from a Json input
/// Gets a Json Object and set the values of the object from it
/// \param json  Json::Value cointaining the information to set the object values
///////////////////////////////////////////////////////////////////////////////
void
CJsonCommand::setFromJson(const Json::Value& json) {
	// Check that we actually receive a command
	if(json.get("type", "").asString().compare("command") != 0)
		throw "Exception: Trying to deserialize a non-command as a command";

	// Get the command from json
	std::string command = json.get("command", "").asString();
	if(command.compare("") == 0)
		throw "Exception: Error deserializing a command (no command attribute)";

	// Find the string of the command in the table
	if (m_string2Command.find(command) == m_string2Command.end())
		throw "Exception: Command got from json deserialization not found.";

	// Finally, set the command
	m_command = m_string2Command[command];

	// Go for the parameters
	Json::Value paramArray = json["data"];
	for (unsigned i=0; i < paramArray.size(); i++) {
		addParameter( createObjectFromJson(paramArray[i]) );
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Create a new instance
///
/// \returns New instance of CJsonCommand as IJSonSerializable Object pointer
///////////////////////////////////////////////////////////////////////////////
IJsonSerializable*
CJsonCommand::createNewInstance() const {
	return new CJsonCommand();
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroys an object that has been dynamically created
///////////////////////////////////////////////////////////////////////////////
void
CJsonCommand::destroy() {
	for (unsigned i=0; i < m_parameters.size(); i++){
		m_parameters[i]->destroy();
	}
	delete this;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Adds a new parameter to the command
/// Adds an IJsonSerializable object to the command as parameter
/// \param p  Pointer to an IJsonSerializable object that will be a parameter
///////////////////////////////////////////////////////////////////////////////
void
CJsonCommand::addParameter(IJsonSerializable* p) {
	m_parameters.push_back(p);
}

bool CJsonCommand::isActionCommand() {
	return isActionCommand(m_command);
}

bool CJsonCommand::isActionCommand(ECommand _c) {
	return (_c == CM_MOVE || _c == CM_USE ||
			_c == CM_INTERACT || _c ==CM_NULL || _c == CM_DROP || _c == CM_GET);
}

void CJsonCommand::copy(const CJsonCommand& _comm) {
	/*m_command = _comm.getCommand();
	for (unsigned i=0; i < _comm.m_parameters.size(); i++){
		m_parameters.push_back(new CJsonCommand(_comm.m_parameters[i]));
	}*/
	throw "No se como copiar CJsonCommand";
}




