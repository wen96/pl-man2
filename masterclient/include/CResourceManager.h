#pragma once

#include <iostream>
#include <vector>
#include <irrlicht.h>
#include "CTileMaped.h"
#include "CLog.h"

using namespace irr;
using namespace std;

namespace masterclient {

/**
 * Clase singleston que gestiona los recursos
 * Carga una sola vez la instancia de un recurso para no tener que recargarla si se reusa
 */
class CResourceManager {
public:
	static CResourceManager& getInstance();
	virtual ~CResourceManager();

	video::SColor getEntityGraphic(int tipe);
	CTileMaped* getEntitySprite(int tipe);

	void setTypeEntitiesCount(int typeEntitiesCount);
	int getTypeEntitiesCount() const;
	int addTypeEntity();

	IrrlichtDevice* getDevice() const;
	void setDevice(IrrlichtDevice* device);

private:
	// Cosas privadas singleton
	CResourceManager();
	CResourceManager(const CResourceManager&);
	CResourceManager& operator=(const CResourceManager&);


	/**
	 * Vecor con los punteros a las texturas
	 */
	std::vector<CTileMaped*> sprites;

	/**
	 * Puntero a device auxiliar para poder cargar las texturas con irrlicht
	 */
	IrrlichtDevice *device;

	/**
	 * Entero que almacena la cantidad de tipos que se tienen
	 */
	int typeEntitiesCount;

	video::ITexture* tileSet;
};

} /* namespace masterclient */
