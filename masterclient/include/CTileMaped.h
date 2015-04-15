#pragma once

#include <irrlicht.h>
#include <iostream>
#include <string>

using namespace irr;
using namespace video;
using namespace std;

namespace masterclient {

/**
 * Almaceno un tile mapeado en una imagen
 */
class CTileMaped {
public:

	CTileMaped(ITexture *text, int w, int h, int c, int tc);
	virtual ~CTileMaped();
	void draw(IVideoDriver * pDriver, core::position2d<s32> position, irr::core::rect<s32> * r = 0);
private:
	/**
	 * Puntero a la textura con el tileset
	 */
	ITexture * texture;
	unsigned short width;
	unsigned short height;
	unsigned short collumns;
	unsigned short tileNum;
};

} /* namespace masterclient */
