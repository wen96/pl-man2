#include "CMainEventReceiver.h"
#include "CLog.h"
#include "CServiceLocator.h"
#include "CMasterMan.h"

namespace masterclient
{

CMainEventReceiver::CMainEventReceiver()
{
	m_displacementVelocity = 50;
}

CMainEventReceiver::~CMainEventReceiver()
{
	// TODO Auto-generated destructor stub
}

CMainEventReceiver::CMainEventReceiver(const CMainEventReceiver& _mer)
{
	m_displacementVelocity = _mer.getDisplacementVelocity();
}

CMainEventReceiver& CMainEventReceiver::operator =(
		const CMainEventReceiver& _mer)
{
	return *this;
}

bool CMainEventReceiver::OnEvent(const SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
	{
		switch (event.KeyInput.Key)
		{
		case KEY_F9:
			doScreenshot();
			break;
		case KEY_RIGHT:
			moveMapRight();
			break;
		case KEY_LEFT:
			moveMapLeft();
			break;
		case KEY_DOWN:
			moveMapDown();
			break;
		case KEY_UP:
			moveMapUp();
			break;
		case KEY_SPACE:
			CLOG.print("step\n");
			CMasterMan::get().setNextStep(true);
			break;
		case KEY_KEY_M:
			CMasterMan::get().switchAutomatic();
			break;
		case KEY_MINUS:
		case KEY_SUBTRACT:
			CMasterMan::get().incrementTimeOut(50);
			break;
		case KEY_PLUS:
		case KEY_ADD:
			CMasterMan::get().decrementTimeOut(50);
			break;
		case KEY_KEY_W:
			CMasterMan::get().move("up");
			break;
		case KEY_KEY_A:
			CMasterMan::get().move("left");
			break;
		case KEY_KEY_S:
			CMasterMan::get().move("down");
			break;
		case KEY_KEY_D:
			CMasterMan::get().move("right");
			break;
			//Usar objeto
		case KEY_KEY_I:
			CMasterMan::get().use("up");
			break;
		case KEY_KEY_J:
			CMasterMan::get().use("left");
			break;
		case KEY_KEY_K:
			CMasterMan::get().use("down");
			break;
		case KEY_KEY_L:
			CMasterMan::get().use("right");
			break;
		case KEY_KEY_R:
			CMasterMan::get().restart();
			break;
		default:
			break;
		}
	} else if (event.EventType == irr::EET_LOG_TEXT_EVENT)
	{
		CLOG.print("Irrlicht >> %s\n", event.LogEvent.Text);
		return true;
	}


	return false;
}

void CMainEventReceiver::moveMapRight()
{
	irr::core::vector3df desplacedPosition = CSERVICELOCATOR.getRootSceneNode()->getPosition();
	desplacedPosition.X -= m_displacementVelocity;
	CSERVICELOCATOR.getRootSceneNode()->setPosition(desplacedPosition);
}

void CMainEventReceiver::moveMapLeft()
{
	irr::core::vector3df desplacedPosition = CSERVICELOCATOR.getRootSceneNode()->getPosition();
	desplacedPosition.X += m_displacementVelocity;
	CSERVICELOCATOR.getRootSceneNode()->setPosition(desplacedPosition);
}

void CMainEventReceiver::moveMapDown()
{
	irr::core::vector3df desplacedPosition = CSERVICELOCATOR.getRootSceneNode()->getPosition();
	desplacedPosition.Y -= m_displacementVelocity;
	CSERVICELOCATOR.getRootSceneNode()->setPosition(desplacedPosition);
}

void CMainEventReceiver::moveMapUp()
{
	irr::core::vector3df desplacedPosition = CSERVICELOCATOR.getRootSceneNode()->getPosition();
	desplacedPosition.Y += m_displacementVelocity;
	CSERVICELOCATOR.getRootSceneNode()->setPosition(desplacedPosition);
}

int CMainEventReceiver::getDisplacementVelocity() const {
	return m_displacementVelocity;
}

void CMainEventReceiver::doScreenshot() {
	video::IImage* image = CSERVICELOCATOR.getDriver()->createScreenShot();
	if (image)
	{
		CSERVICELOCATOR.getDriver()->writeImageToFile(image, "screenshot_main.jpg");
		image->drop();
	}
}

void CMainEventReceiver::setDisplacementVelocity(int displacementVelocity) {
	m_displacementVelocity = displacementVelocity;
}

} /* namespace masterclient */
