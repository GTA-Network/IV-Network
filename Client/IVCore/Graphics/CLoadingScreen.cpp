#include "CLoadingScreen.h"
#include <CCore.h>
#include <IV/CIVScript.h>

extern CCore* g_pCore;

CLoadingScreen::CLoadingScreen(CGUI* pGUI) :
	m_pGUI(pGUI)
{

}

CLoadingScreen::~CLoadingScreen()
{
	if (m_pBackground)
		m_pGUI->RemoveGUIWindow(m_pBackground);
}

bool CLoadingScreen::Initialize()
{
	try
	{
		CEGUI::ImagesetManager::getSingleton().createFromImageFile("Loading", "Loading.png");
	}
	catch (CEGUI::InvalidRequestException e)
	{
		MessageBox(NULL, "Failed to load loading screen background", "IV:Network Error", MB_OK || MB_ICONERROR);
		ExitProcess(0);
	}
	catch (CEGUI::Exception e)
	{
		MessageBox(NULL, "IV:Network failed to load, please check the CEGUI.log for more details", "IV:Network Error", MB_OK || MB_ICONERROR);
		ExitProcess(0);
	}

	// Create the Main Menu Background
	m_pBackground = m_pGUI->CreateGUIStaticImage(m_pGUI->GetDefaultWindow());
	m_pBackground->setProperty("FrameEnabled", "false");
	m_pBackground->setProperty("BackgroundEnabled", "false");
	m_pBackground->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));
	m_pBackground->setSize(CEGUI::UVector2(CEGUI::UDim(1.0f, 0), CEGUI::UDim(1.0f, 0)));
	m_pBackground->setProperty("Image", "set:Loading image:full_image");
	m_pBackground->setVisible(false);

	return true;
}

void CLoadingScreen::SetVisible(bool bVisible)
{
	m_pBackground->setVisible(bVisible);
}