#pragma once

//Incluimos Irrlicht
#include <irrlicht.h>
#include "CResourceManager.h"
#include "CEntityManager.h"
#include "CMainEventReceiver.h"
#include "CServiceLocator.h"
#include "CLog.h"

/*
 Comentarios para el compilador VS++ cargue las librerias
 */
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

#define GAMECLIENT masterclient::CGameClient::getInstance()

namespace masterclient {

/**
 * Clase prinicipal de la aplicacion cliente que hay que instanaciar en un main para arrancarla
 */
class CGameClient
{
public:

	// Instanciadores singleton
	static CGameClient& getInstance();
	~CGameClient(void);

	//Funciones principales
	void run();
	void render();
	void update();
	void init();
	void begin();
	void end();
	bool isRun();

	//Getters y setters
	IrrlichtDevice* getDevice() const;
	void setDevice(IrrlichtDevice* device);
	IVideoDriver* getDriver() const;
	void setDriver(IVideoDriver* driver);
	IGUIEnvironment* getGuienv() const;
	void setGuienv(IGUIEnvironment* guienv);
	ISceneManager* getSceneManager() const;
	void setSceneManager(ISceneManager* sceneManager);
	const core::stringw& getDriverTitle() const;
	void setDriverTitle(const core::stringw& driverTitle);

	void toggleFinishScreen(const core::stringw& _messageScreen=L"You lose!");

private:
	// Canonica privada para singleton
	CGameClient(void);
	CGameClient(const CGameClient&);
	CGameClient& operator=(const CGameClient&);

	/**
	 * Puntero al driver de video para manejear la ventana
	 * Se puede entender driver como ventana
	 */
	IVideoDriver* driver;
	/**
	 * Puntero al sceneManager para manejar los elementos de la escena
	 */
	ISceneManager* sceneManager;
	/**
	 * Puntero al entorno de gui para manejar sus elementos
	 * Se entiende GUI como una capa 2D de elementos de tipo interfaz sobre la escena
	 */
	IGUIEnvironment* guienv;

	/**
	 * Puntero al objeto principal de la aplicacion de Irrlicht
	 */
	IrrlichtDevice *device;


	CMainEventReceiver eventReceiver;

	/**
	 * Titulo de la ventana
	 * Se actualiza automaticamente con los fps y se muestra a cada iteracion actualizado
	 */
	core::stringw m_driverTitle;

	IGUIStaticText* m_staticText;
	core::stringw m_finishMessage;
	bool m_finishScreen;

};
}
