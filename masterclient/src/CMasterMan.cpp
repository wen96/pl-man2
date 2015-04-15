#include "CMasterMan.h"
#include "CGameClient.h"
#include "CNetworkClientDispatcherInitializer.h"
#include "CNetworkClientDispatcherUpdater.h"
#include "CJsonCustomData.h"
#include "CLauncher.h"
#include "CProfiler.h"

namespace masterclient {


//CMasterMan* CMasterMan::m_app;

CMasterMan& CMasterMan::get() {
	static CMasterMan instance;
	return instance;
}

CMasterMan::CMasterMan() {
	CLOG.print("Creando masterman...\n");

	m_nextStep = false;
	m_bot = NULL;
	m_automatic = false;
	m_finished = false;
	m_timeTriggerAutomatic = CServiceLocator::get().getTime();
	m_timeOutToStepAutomatic = 1000;

	CNetwork& net = CNetwork::get();
	net.initialize();
	m_networkClient = net.createClient();

	CLOG.print("masterman creado con dispatcher\n");
}

CMasterMan::~CMasterMan() {
	CLOG.print("CMasterMan destruyendose...");

	m_nextStep = false;

	if (m_bot){
		delete m_bot;
	}
	m_bot = NULL;

	CLOG.print("destruido\n");
}

/**
 * Funcion con el bucle principal del juego
 */
void CMasterMan::run() {
	m_fileBot = CLauncher::get().getScriptFileName();

	//Init updater
	CNetworkClientDispatcherUpdater::getInstance()->setOwner(m_networkClient);

	//Conectamos al servidor
	m_networkClient->connect(CLauncher::get().getHost(), CLauncher::get().getPort());

	//Inicializamos los recursos de dibujos
	GAMECLIENT.init();


	//Inicializamos el mundo
	getWorld();

	//Cargamos el ejecutable del bot y lo lanzamos
	m_bot = new CPipeListener(m_fileBot);
	m_bot->runProgramAndReadyPipes();

	//Bucle principal de la aplicacion
	//Mientras la ventana siga abierta
	while (GAMECLIENT.isRun())
	{
		CProfiler::get().tick("iteration",CServiceLocator::get().getTime());
		//Acciones de inicio
		GAMECLIENT.begin();

		CProfiler::get().tick("update",CServiceLocator::get().getTime());
		update();
		CProfiler::get().tack("update",CServiceLocator::get().getTime());

		CProfiler::get().tick("graphics",CServiceLocator::get().getTime());
		//Acciones de fin
		//Incluye el update y el render
		GAMECLIENT.end();
		CProfiler::get().tack("graphics",CServiceLocator::get().getTime());

		CProfiler::get().tack("iteration",CServiceLocator::get().getTime());

		if (CServiceLocator::get().getTime() - m_timeoutUpdateInfo > 100){
			m_timeoutUpdateInfo = CServiceLocator::get().getTime();

			irr::core::stringw modo = L" | Mode:";
			if (m_automatic) modo += "Automatico";
			else modo += "Manual";

			modo += L" / Velocity:";
			modo += m_timeOutToStepAutomatic;

			modo += L" | ";
			modo += CProfiler::get().getTime("iteration");
			modo += L" | G:";
			modo += CProfiler::get().getPercentage("graphics", "iteration");
			modo += L"% | U:";
			modo += CProfiler::get().getPercentage("update", "iteration");
			modo += L"% | N:";
			modo += CProfiler::get().getPercentage("network", "iteration");
			modo += L"% | P:";
			modo += CProfiler::get().getPercentage("pipes", "iteration");
			modo += L"%";

			GAMECLIENT.setDriverTitle(modo);
		}

	}

	//Me desconecto y vacio la cola de mensajes
	m_networkClient->processEvents();
	m_networkClient->disconnect();
}

void CMasterMan::update() {
	CProfiler::get().tick("network",CServiceLocator::get().getTime());
	CProfiler::get().tick("pipes",CServiceLocator::get().getTime());
	if (!m_finished){
		//Buscamos eventos a procesar en la red
		m_networkClient->processEvents(1);
		CProfiler::get().tack("network",CServiceLocator::get().getTime());

		if (m_nextStep){
			// Buscamos eventos a procesar en el pipe
			// processNextMessage devuelve true si se ha procesado un comando de accion
			m_nextStep = !(m_bot->processNextMessage());
			CProfiler::get().tack("pipes",CServiceLocator::get().getTime());

			m_timeTriggerAutomatic = CServiceLocator::get().getTime();
		}else{
			CProfiler::get().tack("pipes",CServiceLocator::get().getTime());
			if (m_automatic){
				if (CServiceLocator::get().getTime() - m_timeTriggerAutomatic > m_timeOutToStepAutomatic){
					m_nextStep = true;
				}
			}
		}
	}else{
		CProfiler::get().tack("network",CServiceLocator::get().getTime());
	}
}

void CMasterMan::restart() {
	CEntityManager::getInstance().init();
	getWorld();
	m_finished = false;
	GAMECLIENT.toggleFinishScreen();
	//Cargamos el ejecutable del bot y lo lanzamos
	m_bot->runProgramAndReadyPipes();
}
/**
 * Envia el comando getWorld al servidor y reinicia el mundo por lo que tiene un nombre de mierda la funcion
 * ya podria llamarse initWorld
 */
void CMasterMan::getWorld() {
	m_networkClient->setDispatcher(new CNetworkClientDispatcherInitializer(m_networkClient));
	CJsonCommand com = CJsonCommand(CJsonCommand::CM_INIT);
	com.addParameter(new cJsonCustomData("map","mapa.json"));
	launchCommand(com);
	m_networkClient->setDispatcher(CNetworkClientDispatcherUpdater::getInstance());
}

void CMasterMan::move(const std::string& _direction) {
	CJsonCommand com = CJsonCommand(CJsonCommand::CM_MOVE);
	com.addParameter(new CJsonCommand(com.stringToCommand(_direction)));
	launchCommand(com);
}

void CMasterMan::use(const std::string& _direction) {
	CJsonCommand com = CJsonCommand(CJsonCommand::CM_USE);
	com.addParameter(new CJsonCommand(com.stringToCommand(_direction)));
	launchCommand(com);
}

void CMasterMan::see(const std::string& _direction) {
	CJsonCommand com = CJsonCommand(CJsonCommand::CM_SEE);
	com.addParameter(new CJsonCommand(com.stringToCommand(_direction)));
	launchCommand(com);
}

void CMasterMan::launchCommand(const CJsonCommand& _comm) {
	m_networkClient->processEvents(1);
	m_networkClient->sendMessage(_comm.json_serialize());
	m_networkClient->processNextEvent();
}

void CMasterMan::sendMessageToPipe(const std::string& _msg) {
	if (m_bot != NULL){
		m_bot->sendMessage(_msg);
	}
}

bool CMasterMan::isNextStep() const {
	return m_nextStep;
}

void CMasterMan::setNextStep(bool nextStep) {
	m_nextStep = nextStep;
}

bool CMasterMan::isAutomatic() const {
	return m_automatic;
}

void CMasterMan::setAutomatic(bool automatic) {
	m_automatic = automatic;
}
void CMasterMan::switchAutomatic() {
	m_automatic = !m_automatic;
}

void CMasterMan::incrementTimeOut(unsigned int _miliseconds) {
	m_timeOutToStepAutomatic += _miliseconds;
}

void CMasterMan::decrementTimeOut(unsigned int _miliseconds) {
	if (m_timeOutToStepAutomatic > _miliseconds){
		m_timeOutToStepAutomatic -= _miliseconds;
	}
}

bool CMasterMan::isFinished() const {
	return m_finished;
}

void CMasterMan::setFinished(bool _finished, bool _win, int _points) {
	m_finished = _finished;
	irr::core::stringw modo = L"You lose! ";
	if (_win) modo = L"You win! ";
	modo += L" / Score:";
	modo += _points;
	GAMECLIENT.toggleFinishScreen(modo);
}

} /* namespace masterclient */
