#include "CResourceManager.h"

namespace masterclient {

CResourceManager& CResourceManager::getInstance() {
	static CResourceManager instance;
	return instance;
}

/**
 * Borra todos los sprites y tiles
 */
CResourceManager::~CResourceManager() {
	CLOG.print("ResourceManager destruyendose...");
	for (unsigned int i = 0; i < sprites.size(); i++){
		CTileMaped* tile = sprites[i];
		if (tile){
			delete tile;
			tile = NULL;
		}
		sprites[i] = NULL;
	}
	sprites.clear();

	CLOG.print("ResourceManager detruido\n");
}

/**
 * Funcion provisional que devuelve el color correspondiente a un tipo
 * @param tipe entero con el tipo
 * @return color resultante
 */
video::SColor CResourceManager::getEntityGraphic(int tipe) {
	video::SColor color = video::SColor(150,255,0,0);
	switch(tipe){
	case 0:
		color = video::SColor(50,0,255,0);
		break;
	case 1:
		color = video::SColor(50,0,0,255);
		break;
	case 2:
		color = video::SColor(50,255,255,0);
		break;
	case 3:
		color = video::SColor(50,0,255,255);
		break;
	default:
		color = video::SColor(50,255,0,255);
		break;
	}
	return color;
}

/**
 * Funcion para cargar el sprite de una entidad
 * Coge el sprite del vector de sprites si ya existe y si no lo instancia y lo devuelve
 * @param tipe con el entero que identifica el tipo
 * @return puntero a TileMaped con el sprite cargado
 */
CTileMaped* CResourceManager::getEntitySprite(int tipe) {
	if (sprites[tipe]==NULL){
		sprites[tipe] = new CTileMaped(tileSet,50,50,9,tipe);//device->getVideoDriver()->getTexture("../../media/terrain.png");
	}

	return sprites[tipe];

}

/**
 * Inicializa los vectores de sprites y nombres y reserva espacio para ellos
 * @param typeEntitiesCount con el numero de entidades que va a haber
 */
void CResourceManager::setTypeEntitiesCount(int typeEntitiesCount) {
	this->typeEntitiesCount = typeEntitiesCount;
	sprites.clear();
	sprites = vector<CTileMaped*>(typeEntitiesCount);
}

/**
 * Devuelve el la cantidad de entidades que existen
 * @return
 */
int CResourceManager::getTypeEntitiesCount() const {
	return typeEntitiesCount;
}

int CResourceManager::addTypeEntity() {
	return this->typeEntitiesCount++;
}

CResourceManager::CResourceManager() :sprites(81) {

	/*for (int i = 0; i < 81; i++)
		this->sprites.push_back(NULL);*/

	this->typeEntitiesCount = 0;

	this->device = NULL;
	this->tileSet = NULL;
}



IrrlichtDevice* CResourceManager::getDevice() const {

	return device;
}

void CResourceManager::setDevice(IrrlichtDevice* device) {
	if (tileSet == NULL){
		this->tileSet = device->getVideoDriver()->getTexture("../MasterClient/media/mainTileSet.png");
		//device->getVideoDriver()->makeColorKeyTexture(this->tileSet, core::position2d<s32>(0,0));

	}
	this->device = device;
}

} /* namespace masterclient */
