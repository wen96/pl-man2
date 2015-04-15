#pragma once

#include <irrlicht.h>

/*
In the Irrlicht Engine, everything can be found in the namespace 'irr'.
*/
using namespace irr;

namespace masterclient {
/**
 * Clase que recibe los eventos en la ventana del cliente
 */
class CMainEventReceiver : public IEventReceiver
{
public:
	//Forma canonica
	CMainEventReceiver();
	~CMainEventReceiver();
	CMainEventReceiver(const CMainEventReceiver& _mer);
	CMainEventReceiver& operator=(const CMainEventReceiver& _mer);

	//Funciones para moverse por el mapa
	void moveMapRight();
	void moveMapLeft();
	void moveMapDown();
	void moveMapUp();

	void doScreenshot();

	//Funciones principales
	virtual bool OnEvent(const SEvent& event);

	// Getters y setters
	int getDisplacementVelocity() const;
	void setDisplacementVelocity(int displacementVelocity);

private:
	/**
	 * Velocidad de desplazamiento al moverse por el mapa
	 */
	int m_displacementVelocity;
};

}
