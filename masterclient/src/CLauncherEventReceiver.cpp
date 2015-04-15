#include "CLauncherEventReceiver.h"
#include "SLauncherData.h"

namespace masterclient {

CLauncherEventReceiver::CLauncherEventReceiver(
		IrrlichtDevice *_device,
		CLauncherWindow* _window) {
	m_menuDevice = _device;
	m_launcherWindow = _window;
}

CLauncherEventReceiver::~CLauncherEventReceiver() {}

bool CLauncherEventReceiver::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_KEY_INPUT_EVENT &&
			event.KeyInput.Key == KEY_F9 &&
			event.KeyInput.PressedDown == false)
	{
		video::IImage* image = m_menuDevice->getVideoDriver()->createScreenShot();
		if (image)
		{
			m_menuDevice->getVideoDriver()->writeImageToFile(image, "screenshot_main.jpg");
			image->drop();
		}
	}
	else if (event.EventType == EET_GUI_EVENT)
	{
		return OnGUIElementEvent(event);

	}

	return false;
}

bool CLauncherEventReceiver::OnGUIElementEvent(const SEvent& event) {
	if (event.GUIEvent.EventType == gui::EGET_FILE_SELECTED){
		// show the model filename, selected in the file dialog
		gui::IGUIFileOpenDialog* dialog =
				(gui::IGUIFileOpenDialog*)event.GUIEvent.Caller;

		std::wstring ws = dialog->getFileName();
		std::string s;
		s.assign(ws.begin(), ws.end());
		m_launcherWindow->setDefaultScript(s);
		gui::IGUIEditBox *elem =
				(gui::IGUIEditBox *)event.GUIEvent.Caller->
				getParent()->getParent()->getElementFromId(EDT_FILE_SCRIPT,true);
		if (elem)
		{
			elem->setText(dialog->getFileName());
		}
	}else{
		s32 id = event.GUIEvent.Caller->getID();
		switch(id)
		{
		case LST_BOX_DRIVER:
			if (event.GUIEvent.EventType == gui::EGET_LISTBOX_CHANGED ||
					event.GUIEvent.EventType == gui::EGET_LISTBOX_SELECTED_AGAIN)
			{
				m_launcherWindow->m_mapOptions[DRIVER_OPTION] = ((gui::IGUIListBox*)event.GUIEvent.Caller)->getSelected()+1;
			}
			break;
		case BTN_START:
			if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
			{
				m_menuDevice->closeDevice();
				m_launcherWindow->setStart(true);
			}
			break;
		case CHK_BOX_FULLSCREEN:
			if (event.GUIEvent.EventType == gui::EGET_CHECKBOX_CHANGED )
				m_launcherWindow->m_mapOptions[FULLSCREEN_OPTION] = ((gui::IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
			break;
		case CHK_BOX_MUSIC:
			if (event.GUIEvent.EventType == gui::EGET_CHECKBOX_CHANGED )
				m_launcherWindow->m_mapOptions[MUSIC_OPTION] = ((gui::IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
			break;
		case CHK_BOX_SHADOWS:
			if (event.GUIEvent.EventType == gui::EGET_CHECKBOX_CHANGED )
				m_launcherWindow->m_mapOptions[SHADOWS_OPTION] = ((gui::IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
			break;
		case CHK_BOX_ADDITIVE:
			if (event.GUIEvent.EventType == gui::EGET_CHECKBOX_CHANGED )
				m_launcherWindow->m_mapOptions[ADDITIVE_OPTION] = ((gui::IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
			break;
		case CHK_BOX_VSYNC:
			if (event.GUIEvent.EventType == gui::EGET_CHECKBOX_CHANGED )
				m_launcherWindow->m_mapOptions[VSYNC_OPTION] = ((gui::IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
			break;
		case CHK_BOX_AA:
			if (event.GUIEvent.EventType == gui::EGET_CHECKBOX_CHANGED )
				m_launcherWindow->m_mapOptions[AA_OPTION] = ((gui::IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
			break;
		case BTN_FILE_SCRIPT:
			if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
				m_menuDevice->getGUIEnvironment()->addFileOpenDialog(L"Select script");
			break;
		}
	}

	return false;
}

void CLauncherEventReceiver::setLauncherWindow(
		CLauncherWindow* launcherWindow) {
	m_launcherWindow = launcherWindow;
}

void CLauncherEventReceiver::setMenuDevice(IrrlichtDevice* menuDevice) {
	m_menuDevice = menuDevice;
}

} /* namespace masterclient */
