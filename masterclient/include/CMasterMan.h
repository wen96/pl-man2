#pragma once


#include "CNetwork.h"
#include "CNetworkClient.h"
#include "CJsonCommand.h"
#include "CPipeListener.h"

namespace masterclient {

/**
 * Clase principal de toda la aplicacion
 * Lanza el cliente, lo conecta y lanza los comandos
 * Tambien abre el entorno grafico y lo actualiza
 */
class CMasterMan {
public:

	static CMasterMan& get();
	virtual ~CMasterMan();

	//FUnciones principales
	void run();
	void update();
	void restart();

	// Funciones auxiliares
	void move(const std::string& _direction);
	void use(const std::string& _direction);
	void see(const std::string& _direction);
	void launchCommand(const CJsonCommand& _comm);
	void sendMessageToPipe(const std::string& _msg);

	// GETTERS AND SETTERS
	bool isNextStep() const;
	void setNextStep(bool nextStep);
	bool isAutomatic() const;
	void setAutomatic(bool automatic);
	void switchAutomatic();
	void incrementTimeOut(unsigned int _miliseconds);
	void decrementTimeOut(unsigned int _miliseconds);
	bool isFinished() const;
	void setFinished(bool _finished, bool win, int _points);

private:

	void getWorld();

	// Privados por singleton
	CMasterMan();
	CMasterMan(const CMasterMan&);
	CMasterMan& operator=(const CMasterMan&);

	/**
	 * Cliente de ENet para la conexion con el servidor
	 */
	CNetworkClient  *m_networkClient;

	/**
	 * Booleano para controlar si avanzar o no
	 */
	bool m_nextStep;

	CPipeListener *m_bot;

	std::string m_fileBot;

	int m_timeTriggerAutomatic;

	bool m_automatic;

	bool m_finished;

	unsigned int m_timeOutToStepAutomatic;

	unsigned int m_timeoutUpdateInfo;
};

} /* namespace masterclient */
