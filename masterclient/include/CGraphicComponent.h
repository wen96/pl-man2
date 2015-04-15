#pragma once

#include <irrlicht.h>
#include "CResourceManager.h"
#include "IComponent.h"

using namespace irr;

namespace masterclient {

class CEntity;

/**
 * Componente grafico para anyadir a las entidades y que estan puedan dibujarse con el arbol
 * Hereda de ISceneNode para transformarlo en un nodo del arbol del motor gráfico y que se dibuje con Irrlicht
 */
class CGraphicComponent : public scene::ISceneNode, public masterclient::IComponent {
public:
	// Forma canonica
	CGraphicComponent(core::vector2d<s32> p, int tipe, scene::ISceneNode* parent,
			scene::ISceneManager* mgr, s32 id);
	virtual ~CGraphicComponent();
	CGraphicComponent(const CGraphicComponent& _gc);
	CGraphicComponent& operator=(const CGraphicComponent& _gc);

	// Herencia de ISceneNode  -------------------------
	virtual void OnRegisterSceneNode();
	virtual void render();
	const virtual core::aabbox3d<f32>& getBoundingBox() const;
	virtual u32 getMaterialCount() const;
	virtual video::SMaterial& getMaterial(u32 i);
	//---------------------------------------------------

	// Herencia de IComponent
	void refresh(CEntity* _entity);
	void destroy();

	// Getters y setters
	core::vector2d<s32> getPositionInMatrix() const;
	void setPositionInMatrix(core::vector2d<s32> position);
	CTileMaped* getTile() const;
	void setTile(CTileMaped* tile);
	video::SColor getColor() const;
	core::vector2d<s32> getPositionReal() const;
	core::vector2d<s32> getPositionRelative() const;
	int getSizeRectangle() const;

private:
	/**
	 * Caja de represntacion del bounding para el culling y otras cuestiones
	 */
	core::aabbox3d<f32> m_Box;
	/**
	 * Posicion central del recuadro
	 */
	core::vector2d<s32> m_position;
	/**
	 * Posicion superior izquierda del recuadro
	 */
	core::vector2d<s32> m_positionRelative;
	core::vector2d<s32> m_positionInMatrix;

	/**
	 * Material del objeto
	 */
	video::SMaterial m_Material;

	/**
	 * Color del objeto
	 */
	video::SColor m_color;

	/**
	 * Tamanyo del cuadrado que se genera alrededor del punto
	 */
	int m_sizeRectangle;

	CTileMaped* m_tile;


	void copiar(const CGraphicComponent& _gc);
};

} /* namespace masterclient */
