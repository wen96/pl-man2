#include "CTileMaped.h"

namespace masterclient {

/**
 * Constructor sobrecargado
 * @param text textura de la que obtener el tile
 * @param w ancho del tile
 * @param h alto del tile
 * @param c tamanyo de la columna en pixeles
 * @param tc numero de tile que queremos coger, en orden habitual occidental (izquierda -> derecha, arriba -> bajo)
 */
CTileMaped::CTileMaped(ITexture *text, int w, int h, int c, int tc) {
	width = w;
	height = h;
	collumns = c;
	tileNum = tc;
	texture = text;
}

CTileMaped::~CTileMaped() {}

void CTileMaped::draw(IVideoDriver * pDriver, core::position2d<s32> position, irr::core::rect<s32> * r)
{
	// get the source coordinates
	int sx = (tileNum % collumns) * width;
	int sy = (tileNum / collumns) * height;

	if (texture == NULL){
		throw "Exception: Texture for tile not found";
	}
	pDriver->draw2DImage(texture,position,
			core::rect<s32>(sx, sy, sx + width, sy + height),
			0/*new core::rect<s32>(position.X, position.Y,position.X+ 100,position.Y+ 100)*/, SColor(255,255,255,255), true);
}

} /* namespace masterclient */
