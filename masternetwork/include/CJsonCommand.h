#pragma once

#include "CJsonSerializer.h"
#include <vector>
#include <map>
#include <string>

class CJsonCommand : public CJsonSerializer
{
public:
  // Enumeration of command types -------------------------

  /// Enum of all possible CJsonCommands
  enum ECommand {
    CM_NULL,        //< Null command (do nothing)
    CM_INIT,        //< Command to init the world and return them
    CM_SEE,         //< Command to see your environment
    CM_GET,         //< Command to get an object
    CM_DROP,        //< Command to drop an object
    CM_USE,         //< Command to use an object
    CM_MOVE,        //< Command to make movements
    CM_INTERACT,        //< Command to make movements
    CM_EXIT,        //< Command to exit from the game
    
    CM_LEFT,        //< Direction
    CM_UP,        //< Direction
    CM_RIGHT,        //< Direction
    CM_DOWN,        //< Direction
    CM_UPLEFT,        //< Direction
    CM_UPRIGHT,        //< Direction
    CM_DOWNLEFT,        //< Direction
    CM_DOWNRIGHT,        //< Direction
    CM_NONE,
    
    CM_NUMCOMMANDS  //< Item to count the number of commands available
  };

  // Virtual Methods ----------------------------------------------
  virtual ~CJsonCommand();
  virtual void                write2json       (Json::Value& v) const;
  virtual void                setFromJson      (const Json::Value& v);
  virtual IJsonSerializable*  createNewInstance() const;
  virtual void                destroy          ();

  // Methods ----------------------------------------------
  CJsonCommand(ECommand c = CM_NULL);
  CJsonCommand(const CJsonCommand& _comm);
  CJsonCommand& operator=(const CJsonCommand& _comm);
  void    addParameter (IJsonSerializable* p);
  void    reset();
  ECommand getCommand() {return m_command;};
  std::vector<ECommand> getParameters() {
      std::vector<ECommand> parameters;
      
      for(unsigned int i = 0; i < m_parameters.size(); i++)
      {
        parameters.push_back(((CJsonCommand*)m_parameters[i])->getCommand());
      }
      
      return parameters;
  };
  
  IJsonSerializable* getParameter(int i) {
      
      if(i >= 0 && (unsigned int)i < m_parameters.size())
      {
          return m_parameters[i];
      }
     
      return NULL;
  };
  

  ECommand stringToCommand(std::string _cmd){return m_string2Command[_cmd];}

  bool isActionCommand();
  static bool isActionCommand(ECommand c);
private:
  void copy(const CJsonCommand& _comm);

  ECommand                            m_command;        //< The command this object represents
  std::map <ECommand, std::string>    m_command2String; //< Translations from command enumerates to strings
  std::map <std::string, ECommand>    m_string2Command; //< Inverse translations from strings to command enumerates
  std::vector< IJsonSerializable* >   m_parameters;     //< List of parameters for this command
};

