#pragma once

#include <iostream>
#include <vector>
#include <irrlicht.h>
#include "CEntity.h"
#include "CLog.h"

namespace masterclient {


using namespace std;

/**
 * Clase singleton para la gestion de las entidades
 */
class CEntityManager {
public:

	static CEntityManager& getInstance();
	virtual ~CEntityManager();

	// Funciones principales
	void addEntity(int x, int y, int tipe, int id=-1);
	void updateEntities(vector<CEntity*> &entitiesUpdated);
	CEntity* getEntity(int id);
	void refresh();
	void update();
	bool removeEntity(CEntity *_ent);

	// Funciones utiles
	void cleanUpDeads();
	void init();
private:
	//Clases privadas por singleton
	CEntityManager();
	CEntityManager(const CEntityManager&);
	CEntityManager& operator=(const CEntityManager&);

	/**
	 * Vector de elementos a manejar
	 */
	vector<CEntity*> m_entities;

	vector<CEntity*> m_entitiesDeadAndAvailable;

	/**
	 * Contador de enteros asignados a las entidades
	 */
	int m_idCount;
};

} /* namespace masterclient */

