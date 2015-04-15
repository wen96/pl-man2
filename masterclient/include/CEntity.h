#pragma once

#include <vector>
#include <iostream>
#include <irrlicht.h>
#include <stdarg.h>

namespace masterclient {

/**
 * Dependencia circular por el tema de componentes
 */
class IComponent;
/**
 * Clase Entity que representa una entidad en el juego.
 * En este caso representa una casilla del tablero, ya que el juego esta discretizado en una matriz
 */
class CEntity {
public:
	// Constructores y forma canonica
	CEntity(irr::core::vector2d<irr::s32> _p, int _tipe, irr::s32 id, int _nComponents, IComponent *c1, IComponent *c2);
	CEntity(irr::core::vector2d<irr::s32> p, int tipe, int id = 0);
	virtual ~CEntity();
	CEntity(const CEntity& e);
	CEntity& operator =(const CEntity& e);

	//Componentes
	void refresh(CEntity* _entity);
	//No se usa
	void refresh();

	void update();

	//Getters y setters
	int getTipe() const;
	void setTipe(int tipe);
	int getId() const;
	void setId(int id);
	irr::core::vector2d<irr::s32> getPosition() const;
	void setPosition(irr::core::vector2d<irr::s32> position);
	bool isVisible() const;
	void setVisible(bool visible);


private:
	/**
	 * Componente grafico que proporciona la funcionalidad de pintarse
	 */
	std::vector<IComponent*> components;
	/**
	 * Posicion real en la matriz
	 */
	irr::core::vector2d<irr::s32> m_position;

	/**
	 * Entero que representa el tipo de entidad
	 */
	int m_tipe;

	/**
	 * Funcion auxiliar par hacer las copias del objeto
	 * @param e
	 */
	void copiar(const CEntity& e);

	/**
	 * Id interno
	 */
	int m_id;

	/**
	 * Visibilidad logica no grafica
	 */
	bool m_visible;
};

} /* namespace masterclient */
