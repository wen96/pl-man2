#include "CGraphicComponent.h"
#include "CEntity.h"

namespace masterclient {

/**
 * Constructor del componente con todos los parametros necesarios para crearlo y crear el nodo de Irrlicht
 * @param p posicion
 * @param tipe tipo de elemento para sacar su respresentacion grafica
 * @param parent nodo del que cuelga
 * @param mgr puntero al SceneManager
 * @param id que lo identifica en el arbol
 */
CGraphicComponent::CGraphicComponent(core::vector2d<s32> p, int tipe,
		scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) :
												scene::ISceneNode(parent, mgr, id) {
	m_Material.Wireframe = false;
	m_Material.Lighting = false;
	m_sizeRectangle = 50 / 2;

	m_positionInMatrix = p;
	//Calculamos la posicion real respecto de la posicion en el rectangulo
	m_position.X = p.X * (m_sizeRectangle * 2) + m_sizeRectangle;
	m_position.Y = p.Y * (m_sizeRectangle * 2) + m_sizeRectangle;
	m_positionRelative.X = m_position.X - m_sizeRectangle;
	m_positionRelative.Y = m_position.Y - m_sizeRectangle;
	m_color = CResourceManager::getInstance().getEntityGraphic(tipe);
	// TODO: Mirara exactamente como debe ser el bounding de un objeto 2D
	m_Box.reset(m_position.X, m_position.Y, 0);
	m_tile = CResourceManager::getInstance().getEntitySprite(tipe);
}

CGraphicComponent::~CGraphicComponent() {
}
CGraphicComponent::CGraphicComponent(const CGraphicComponent& _gc):
														scene::ISceneNode(_gc.getParent(), _gc.getSceneManager(), _gc.getID()) {
	copiar(_gc);
}

CGraphicComponent& CGraphicComponent::operator =(const CGraphicComponent& _gc) {
	if (&_gc != this){
		this->~CGraphicComponent();
		copiar(_gc);
	}
	return *this;
}

/**
 * Capturador del evento del registro para la renderizacion
 */
void CGraphicComponent::OnRegisterSceneNode() {
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}
/**
 * Funcion de dibujado en la ventana
 */
void CGraphicComponent::render() {
	//u16 indices[] = {	0,2,3, 2,1,3, 1,0,3, 2,0,1	};
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	driver->setMaterial(m_Material);
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	;

	m_tile->draw(driver, core::vector2d<s32>(
			AbsoluteTransformation.getTranslation().X+m_positionRelative.X,
			AbsoluteTransformation.getTranslation().Y+m_positionRelative.Y));

}
/**
 * Devuelve el bounding del objeto
 * @return caja que represnta el bounding
 */
const core::aabbox3d<f32>& CGraphicComponent::getBoundingBox() const {
	return m_Box;
}
/**
 * Dvuelve la cantidad de materiales que tiene el nodo
 * @return entero con el numero de materiales
 */
u32 CGraphicComponent::getMaterialCount() const {
	return 1;
}
/**
 * Devuelve el material con el indice indicado
 * @param i indice del material
 * @return material pedido
 */
video::SMaterial& CGraphicComponent::getMaterial(u32 i) {
	return m_Material;
}

void CGraphicComponent::refresh(CEntity* _entity) {
	setVisible(_entity->isVisible());
	setPositionInMatrix(_entity->getPosition());
	setTile(
			CResourceManager::getInstance().getEntitySprite(_entity->getTipe()));
}

void CGraphicComponent::destroy() {
	//this->~GraphicComponent();
	this->drop();
	this->remove();
}

void CGraphicComponent::setPositionInMatrix(core::vector2d<s32> position) {
	this->m_positionInMatrix = position;
	//Calculamos la posicion real respecto de la posicion en el rectangulo
	this->m_position.X = position.X * (m_sizeRectangle * 2) + m_sizeRectangle;
	this->m_position.Y = position.Y * (m_sizeRectangle * 2) + m_sizeRectangle;
	this->m_positionRelative.X = this->m_position.X - m_sizeRectangle;
	this->m_positionRelative.Y = this->m_position.Y - m_sizeRectangle;
}

core::vector2d<s32> CGraphicComponent::getPositionInMatrix() const {
	return m_positionInMatrix;
}

CTileMaped* CGraphicComponent::getTile() const {
	return m_tile;
}

void CGraphicComponent::setTile(CTileMaped* tile) {
	m_tile = tile;
}


video::SColor CGraphicComponent::getColor() const {
	return m_color;
}

core::vector2d<s32> CGraphicComponent::getPositionReal() const {
	return m_position;
}

core::vector2d<s32> CGraphicComponent::getPositionRelative() const {
	return m_positionRelative;
}

int CGraphicComponent::getSizeRectangle() const {
	return m_sizeRectangle;
}

void CGraphicComponent::copiar(const CGraphicComponent& _gc) {
	m_tile = _gc.getTile();
	m_Box = _gc.getBoundingBox();
	//TODO m_Material = _gc.getMaterial(0);
	m_color = _gc.getColor();
	m_position = _gc.getPositionReal();
	m_positionInMatrix = _gc.getPositionInMatrix();
	m_positionRelative = _gc.getPositionRelative();

	m_sizeRectangle = _gc.getSizeRectangle();
	m_tile = _gc.getTile();
}

}

