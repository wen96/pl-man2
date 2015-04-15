#include "CEntityManager.h"
#include "CGraphicComponent.h"
#include "CNetworkUpdaterComponent.h"
#include "CServiceLocator.h"

namespace masterclient {

/**
 * Instanciador para singleton
 * @return
 */
CEntityManager& CEntityManager::getInstance() {
	static CEntityManager instance;
	return instance;
}

/**
 * Destructor
 */
CEntityManager::~CEntityManager() {
	CLOG.print("EntityManager destruyendose...");
	init();
	CLOG.print("EntityManager destruido\n");
}
/**
 * Anyade una entidad de un tipo en un punto
 * @param p posicion en la matriz
 * @param tipe entero representante del tipo de entidad
 */
void CEntityManager::addEntity(int _x, int _y, int _tipe, int _id) {
	int finalId = m_idCount++;
	if (_id != -1){
		finalId = _id;
	}

	//cout << "Entity "<< finalId << " added" << endl;
	irr::core::position2d<irr::s32> p = irr::core::position2d<irr::s32>(_x,_y);

	CNetworkUpdaterComponent *cnu = new CNetworkUpdaterComponent();
	CGraphicComponent *gc =new CGraphicComponent(p,
			_tipe, CSERVICELOCATOR.getRootSceneNode(), CSERVICELOCATOR.getSceneManager(), finalId);
	// IMPORTANTE: Hay que pasar primero el componente de actualizacion para que luego se pinte correctamente
	m_entities.push_back(new CEntity(p,
			_tipe,
			finalId,
			2,
			cnu,
			gc));
}

/**
 * Llega un vector entidades para modificar
 * Buscar en el vector de entidades por el id y si lo encuentra lo modifica
 * @param entitiesUpdated vector con las entidades para actualizar
 */
void CEntityManager::updateEntities(vector<CEntity*> &entitiesUpdated) {
	for (unsigned int i = 0; i < entitiesUpdated.size(); i++){
		int entId = entitiesUpdated[i]->getId();
		CEntity* entToModify = this->getEntity(entId);
		if (entToModify!=NULL){
			entToModify->refresh(entitiesUpdated[i]);
		}
	}
}
/**
 * Devuelve una entidad segun el id
 * @param id con el id de la entidad
 * @return con un puntero a la entidad
 */
CEntity* CEntityManager::getEntity(int id) {
	for (unsigned int i = 0; i < m_entities.size(); i++){
		if (m_entities[i]->getId()==id) return m_entities[i];
	}

	return NULL;
}
/**
 * Funcion que ejecuta el refresh de todas las entidades
 * Cuando se produce un evento que necesita actualizar todas la entidades esto
 * se realizara con esta funcion. No confundir con update, que se ejecutara todas las
 * iteraciones del juego
 */
void CEntityManager::refresh() {
	for (unsigned int i = 0; i < m_entities.size(); i++){
		if (m_entities[i] != NULL){
			m_entities[i]->refresh();
		}
	}
}
/**
 * Llama al metodo update de todas las entidades
 */
void CEntityManager::update() {
	for (unsigned int i = 0; i < m_entities.size(); i++){
		if (m_entities[i] != NULL){
			m_entities[i]->update();
		}
	}
}
/**
 * Borra entidades comparando punteros no por id
 * Con borrar me refiero a meter en un vector de entidades muertas y poner esa posicion del vector a null
 * @param _ent con la entidad a borrar
 * @return booleano con si se ha borrado o no
 */
bool CEntityManager::removeEntity(CEntity* _ent) {
	for (unsigned int i = 0; i < m_entities.size(); i++){
		if (m_entities[i] == _ent){
			m_entities[i] = NULL;
			m_entitiesDeadAndAvailable.push_back(_ent);
			return true;
		}
	}
	return false;
}

/**
 * Recorre el vector de entidades y elimina las posiciones que estan a null porque han muerto
 * Luego vacia el vector de entidades muertas liberando la memoria de las entidades muertas
 */
void CEntityManager::cleanUpDeads() {
	vector<CEntity*>::iterator iter;
	for (iter = m_entities.begin(); iter != m_entities.end();/* iter++*/) {
		if ((*iter)==NULL){
			m_entities.erase(iter);
		}else{
			++iter;
		}
	}

	iter = m_entitiesDeadAndAvailable.begin();
	while (!m_entitiesDeadAndAvailable.empty()) {
		delete (*iter);
		m_entitiesDeadAndAvailable.erase(iter);
		iter = m_entitiesDeadAndAvailable.begin();
	}
	m_entitiesDeadAndAvailable.clear();
}

/**
 *  Vacia el gestor completo de entidades liberando su memoria
 */
void CEntityManager::init() {
	cleanUpDeads();
	for (unsigned int i = 0; i < m_entities.size(); i++){
		CEntity *ent = m_entities[i];
		if (ent){
			delete ent;
			ent = NULL;
		}
		m_entities[i] = NULL;
	}
	m_entities.clear();
}

/**
 * Constructor privado
 */
CEntityManager::CEntityManager() {
	m_idCount = 100;
	m_entities.clear();
}




} /* namespace masterclient */
