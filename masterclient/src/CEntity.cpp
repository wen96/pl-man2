#include "CEntity.h"
#include "IComponent.h"
#include <boost/foreach.hpp>

namespace masterclient {

/** Constructor por defecto
 * Se le pasan los parámetros necesarios para poder dibujarlo
 * ANYADE EL ELEMENTO AL ARBOL, CUIDADO: Esto cambiara cuando termine con los componentes
 * @param p posicion en el tablero
 * @param tipe entero que representa el tipo de entidad que se desea crear
 * @param parent nodo padre del que cogarlo en el arbol del motor
 * @param mgr puntero al SceneManager
 * @param id entero que lo identifica tanto en el motor grafico como en el juego
 */
CEntity::CEntity(irr::core::vector2d<irr::s32> _p, int _tipe, irr::s32 _id, int _nComponents,
		IComponent *c1, IComponent *c2) {
	//asignamos el tipo
	m_tipe = _tipe;
	//Asignamos la posicion en la matriz
	m_position = _p;
	// Generamos el componente grafico
	components.clear();
	//components.push_back(new GraphicComponent(p, tipe, parent, mgr, id));
	m_id = _id;

	m_visible = true;


	components.push_back(c1);
	components.push_back(c2);
	//Recorro la lista de componentes que me hayan pasado
	/*va_list vl;
	va_start(vl,_nComponents);
		for (int i = 0; i < _nComponents; i++){
			components.push_back(va_arg(vl,IComponent*));//Y los voy guardando en el vector
		}
	va_end(vl);*/
}

/**
 * Constructor que no engancha al arbol de irrlicht
 * @param p
 * @param tipe
 */
CEntity::CEntity(irr::core::vector2d<irr::s32> p, int tipe, int id){
	m_tipe = tipe;
	//Asignamos la posicion en la matriz
	m_position = p;
	m_id = id;
	components.clear();
	m_visible = true;
}
/**
 * Destructor
 */
CEntity::~CEntity() {
	for (unsigned int i = 0; i < components.size(); i++){
		IComponent *comp = components[i];
		if (comp){
			comp->destroy();
			comp = NULL;
		}
		components[i] = NULL;
	}
	components.clear();

}
/*
 * Constructor de copia
 */
CEntity::CEntity(const CEntity& e) {
	copiar(e);
}
/**
 * Sobrecarga del operador igual
 * @param e
 * @return
 */
CEntity& CEntity::operator =(const CEntity& e) {
	if (this != &e) {
		this->~CEntity();
		copiar(e);
	}
	return *this;
}

/**
 * No se hace una copia se actualizan los datos que son necesarios:
 * m_tipe y m_position
 * @param _entity con la entidad con la que actualizar
 */
void CEntity::refresh(CEntity* _entity) {
	this->setPosition(_entity->getPosition());
	this->setTipe(_entity->getTipe());
	this->setVisible(_entity->isVisible());
	this->refresh();
}
/**
 * Actualiza todos los componentes con la funcion refresh del componente
 */
void CEntity::refresh() {
	for (unsigned int i = 0; i < components.size(); i++){
		components[i]->refresh(this);
	}
}

void CEntity::update() {

}

/**
 * Devuelve el tipo de entidad
 * @return
 */
int CEntity::getTipe() const {
	return m_tipe;
}
/**
 * Devuelve el tipo de puntero
 * @param tipe
 */
void CEntity::setTipe(int tipe) {
	m_tipe = tipe;
}

int CEntity::getId() const {
	return m_id;
}

void CEntity::setId(int id) {
	m_id = id;
}

irr::core::vector2d<irr::s32> CEntity::getPosition() const {
	return m_position;
}

void CEntity::setPosition(irr::core::vector2d<irr::s32> position) {
	m_position = position;
}



bool CEntity::isVisible() const {
	return m_visible;
}

void CEntity::setVisible(bool visible) {
	m_visible = visible;
}

void CEntity::copiar(const CEntity& e) {
	//TODO: m_gc = e.getGc();
	m_tipe = e.getTipe();
	m_id = e.getId();
	m_position = e.getPosition();
	m_visible = e.isVisible();
}

} /* namespace masterclient */
