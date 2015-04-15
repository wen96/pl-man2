#include "CGameClient.h"
#include "CLauncher.h"
#include "SLauncherData.h"

namespace masterclient {

/**
 * Instanciado singleton
 * @return
 */
CGameClient& CGameClient::getInstance() {
	static CGameClient instance;
	return instance;
}

/**
 * Constructor por defecto
 */
CGameClient::CGameClient(void)
{

	SIrrlichtCreationParameters params = SIrrlichtCreationParameters();
	params.AntiAlias = CLauncher::get().getOption(AA_OPTION);
	params.DriverType = (irr::video::E_DRIVER_TYPE)CLauncher::get().getOption(DRIVER_OPTION);
	params.WindowSize = core::dimension2d<u32>(800, 600);
	params.Fullscreen = CLauncher::get().getOption(FULLSCREEN_OPTION);
	params.Stencilbuffer = CLauncher::get().getOption(SHADOWS_OPTION);
	params.Vsync = CLauncher::get().getOption(VSYNC_OPTION);
	params.ZBufferBits = 32;
	params.EventReceiver = &eventReceiver;

	device = irr::createDeviceEx(params);
	driver = device->getVideoDriver();
	sceneManager = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	CResourceManager::getInstance().setDevice(device);

	m_driverTitle = L"MasterMan Client";

	m_staticText = NULL;
	m_finishMessage = L"You lose!";
	m_finishScreen = false;

	CSERVICELOCATOR.setDevice(device);
}

/**
 * Destructor
 */
CGameClient::~CGameClient(void)
{
	CLOG.print("GameClient destruyendose...");
	//El irrlicht  la forma real de borrar los punteros es esta
	//Cada vez que se cree un objeto con alguna funcion que comience por create se debe llamar a esta funcion
	//para liberar sus memoria
	device->drop();

	//delete ResourceManager::getInstance();
	//delete EntityManager::getInstance();
	CLOG.print("destruido\n");
}

/**
 * Funcion para arrancar la aplicacion lanzando el bucle principal de pintado y actualizacion
 * hasta que la ventana se cierre
 */
void CGameClient::run(){
	//Mientras la ventana este abierda (se cierra pulsando el boton de cerrar)
	while(device->run()){
		//Si la ventana esta activa dibujamos
		if (device->isWindowActive())
		{
			this->update();
			this->render();
		}//Si no dejamos descansar el procesador
		else
			device->yield();
	}
}
/**
 * Limpia la ventana y pinta las entidades
 */
void CGameClient::render(){
	if (m_finishScreen){
		driver->beginScene(true, true, SColor(255, 255, 255, 255));
	} else {
		//Limpiamos la ventana
		driver->beginScene(true, true, SColor(255, 104, 167, 66));

		//Pintamos las escena
		sceneManager->drawAll();
	}

	//Pintamos el GUI
	guienv->drawAll();

	//Terminamos de dibujar
	driver->endScene();
}

void CGameClient::toggleFinishScreen(const core::stringw& _messageScreen) {
	m_finishScreen = !m_finishScreen;
	m_finishMessage = _messageScreen;
	if (m_finishScreen){
		guienv->addStaticText(m_finishMessage.c_str(), core::rect<s32>(10,10,260,50));
	} else {
		guienv->clear();
	}
}

/**
 * Llamara al update de manager y lo que necesite cuando esas funciones hagan algo
 */
void CGameClient::update(){
}

/**
 * Inicializa la ventana y algunas cuestiones grafica de irrlicht pinta un loading para espera mientras se carga la
 * aplicacion
 */
void CGameClient::init() {
	device->setWindowCaption(L"MasterMan Client");
	//TODO: Desactivar el log output: Crear un event reciber que se coma el log output y no lo pinte

	//sceneManager->addCameraSceneNode(0, core::vector3df(0,-400,1231), core::vector3df(0,1221,0));
	//sceneManager->getRootSceneNode()->setScale(vector3df(0.5,0.5,0.5));

	//No se pa que sirve, pero pone que sale bonito asi que voy a ponerlo a ver
	driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
	driver->getMaterial2D().AntiAliasing=video::EAAM_FULL_BASIC;

	//Una pequenya ventana de carga
	driver->beginScene(true, true, SColor(255,255,255,255));
	device->getGUIEnvironment()->addStaticText(L"Loading",core::rect<s32>(10,10,260,20));
	guienv->drawAll();
	driver->endScene();
	device->getGUIEnvironment()->clear();
}

/**
 * Realiza las operaciones iniciales del bucle principal
 */
void CGameClient::begin(){
	int fps = driver->getFPS();
	core::stringw str = m_driverTitle+" [";
	str += fps;
	str += " FPS]";
	device->setWindowCaption(str.c_str());
}
/**
 * Llama a las funciones update y render
 */
void CGameClient::end(){
	this->update();
	this->render();
}

/**
 * Comprueba si la ventana del juego sigue abierta
 * @return bool
 */
bool CGameClient::isRun(){
	return (device!= NULL && device->run());
}

IrrlichtDevice* CGameClient::getDevice() const {
	return device;
}

void CGameClient::setDevice(IrrlichtDevice* device) {
	this->device = device;
}

IVideoDriver* CGameClient::getDriver() const {
	return driver;
}

void CGameClient::setDriver(IVideoDriver* driver) {
	this->driver = driver;
}

IGUIEnvironment* CGameClient::getGuienv() const {
	return guienv;
}

void CGameClient::setGuienv(IGUIEnvironment* guienv) {
	this->guienv = guienv;
}

ISceneManager* CGameClient::getSceneManager() const {
	return sceneManager;
}

void CGameClient::setSceneManager(ISceneManager* sceneManager) {
	this->sceneManager = sceneManager;}

const core::stringw& CGameClient::getDriverTitle() const {
	return m_driverTitle;
}

/**
 * Contatena el texto pasado como parametro a MasterMan Client:
 * @param _driverTitle
 */
void CGameClient::setDriverTitle(const core::stringw& _driverTitle) {
	m_driverTitle = L"MasterMan Client";
	m_driverTitle += _driverTitle.c_str();
}

}
