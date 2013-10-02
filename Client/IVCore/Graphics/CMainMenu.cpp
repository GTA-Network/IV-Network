
#include "CMainMenu.h"
#include <CCore.h>
#include <IV/CIVScript.h>


extern CCore* g_pCore;

CMainMenu::CMainMenu(CGUI* pGUI)
: m_pGUI(pGUI)
{

}

CMainMenu::~CMainMenu()
{
	SAFE_DELETE(m_pQuickConnectButton);

	SAFE_DELETE(m_pServerBrowserButton);

	SAFE_DELETE(m_pSettingsButton);

	SAFE_DELETE(m_pCreditsButton);

	SAFE_DELETE(m_pExitButton);

	if (m_pBackground)
		m_pGUI->RemoveGUIWindow(m_pBackground);
}

bool CMainMenu::Initialize()
{	
	try
	{
		CEGUI::ImagesetManager::getSingleton().createFromImageFile("Background", "Background.png");
	}
	catch (CEGUI::InvalidRequestException e)
	{
		MessageBox(NULL, "Failed to load Main Menu Background", "IV:Network Error", MB_OK || MB_ICONERROR);
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
	m_pBackground->setSize(CEGUI::UVector2(CEGUI::UDim(m_pGUI->GetDisplayWidth(), 0), CEGUI::UDim(m_pGUI->GetDisplayHeight(), 0)));
	m_pBackground->setProperty("Image", "set:Background image:full_image");
	m_pBackground->setProperty("InheritsAlpha", "false");
	m_pBackground->setAlpha(0.975f);
	m_pBackground->setVisible(false);

#define fY 0.5f

	// Create the Quick Connect Button
	m_pQuickConnectButton = CreateButton("Quick Connect", CEGUI::UVector2(CEGUI::UDim(0.20f, 0), CEGUI::UDim(0.030f, 0)), CEGUI::UVector2(CEGUI::UDim(0.025f, 0), CEGUI::UDim(fY, 0)));
	m_pQuickConnectButton->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CMainMenu::OnQuickConnectButtonMouseEnter, this));
	m_pQuickConnectButton->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CMainMenu::OnQuickConnectButtonMouseExit, this));
	m_pQuickConnectButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&CMainMenu::OnQuickConnectButtonMouseClick, this));
	m_pBackground->addChildWindow(m_pQuickConnectButton);

	// Create the Server Browser Button
	m_pServerBrowserButton = CreateButton("Server Browser", CEGUI::UVector2(CEGUI::UDim(0.20f, 0), CEGUI::UDim(0.030f, 0)), CEGUI::UVector2(CEGUI::UDim(0.275f, 0), CEGUI::UDim(fY, 0)));
	m_pServerBrowserButton->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CMainMenu::OnServerBrowserButtonMouseEnter, this));
	m_pServerBrowserButton->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CMainMenu::OnServerBrowserButtonMouseExit, this));
	m_pBackground->addChildWindow(m_pServerBrowserButton);

	// Create the Settings Button
	m_pSettingsButton = CreateButton("Settings", CEGUI::UVector2(CEGUI::UDim(0.162f, 0), CEGUI::UDim(0.030f, 0)), CEGUI::UVector2(CEGUI::UDim(0.525f, 0), CEGUI::UDim(fY, 0)));
	m_pSettingsButton->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CMainMenu::OnSettingsButtonMouseEnter, this));
	m_pSettingsButton->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CMainMenu::OnSettingsButtonMouseExit, this));
	m_pBackground->addChildWindow(m_pSettingsButton);

	// Create the Credits Button
	m_pCreditsButton = CreateButton("Credits", CEGUI::UVector2(CEGUI::UDim(0.08f, 0), CEGUI::UDim(0.030f, 0)), CEGUI::UVector2(CEGUI::UDim(0.75f, 0), CEGUI::UDim(fY, 0)));
	m_pCreditsButton->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CMainMenu::OnCreditsButtonMouseEnter, this));
	m_pCreditsButton->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CMainMenu::OnCreditsButtonMouseExit, this));
	m_pBackground->addChildWindow(m_pCreditsButton);

	// Create the Exit Button
	m_pExitButton = CreateButton("Exit", CEGUI::UVector2(CEGUI::UDim(0.08f, 0), CEGUI::UDim(0.030f, 0)), CEGUI::UVector2(CEGUI::UDim(0.925f, 0), CEGUI::UDim(fY, 0)));
	m_pExitButton->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CMainMenu::OnExitButtonMouseEnter, this));
	m_pExitButton->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CMainMenu::OnExitButtonMouseExit, this));
	m_pExitButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&CMainMenu::OnExitButtonMouseClick, this));
	m_pBackground->addChildWindow(m_pExitButton);

#undef fY

	return true;
}

void CMainMenu::SetVisible(bool bVisible)
{
	if (bVisible == true)
		g_pCore->GetGraphics()->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	m_bVisible = bVisible;
	
	m_pGUI->SetCursorVisible(bVisible);

	m_pBackground->setVisible(bVisible);
	m_pQuickConnectButton->setVisible(bVisible);
	m_pServerBrowserButton->setVisible(bVisible);
	m_pSettingsButton->setVisible(bVisible);
	m_pCreditsButton->setVisible(bVisible);
	m_pExitButton->setVisible(bVisible);

	m_pBackground->setProperty("Image", "set:Background image:full_image");
	m_pBackground->setAlpha(0.95f);
}

CGUIStaticText * CMainMenu::CreateButton(char * szText, CEGUI::UVector2 vecSize, CEGUI::UVector2 vecPosition)
{
	CGUIStaticText * pButton = m_pGUI->CreateGUIStaticText();
	pButton->setText(CGUI::AnsiToCeguiFriendlyString(szText, strlen(szText)));
	pButton->setSize(vecSize);
	pButton->setPosition(vecPosition);
	pButton->setProperty("FrameEnabled", "false");
	pButton->setProperty("BackgroundEnabled", "false");
	pButton->setFont(m_pGUI->GetFont("pricedown", 20));
	pButton->setProperty("TextColours", "tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFFFFFF");
	return pButton;
}

bool CMainMenu::OnQuickConnectButtonMouseClick(const CEGUI::EventArgs &eventArgs)
{
	CIVScript::DoScreenFadeIn(1000); //TODO: do this after connected to the sever

	// Enable the chat
	g_pCore->GetChat()->SetVisible(true);

	// Output the message in the background of the chat
	//g_pCore->GetChat()->Outputf(true, "#ffffff%s #B9C9BF%s #ffffffStarted", MOD_NAME, MOD_VERSION_STRING);

	// Conneting the player to the server
	g_pCore->ConnectToServer();

	// Hide the main menu elements
	SetVisible(false);
	return true;
}

bool CMainMenu::OnQuickConnectButtonMouseEnter(const CEGUI::EventArgs &eventArgs)
{
	m_pQuickConnectButton->setAlpha(0.5f);
	return true;
}

bool CMainMenu::OnQuickConnectButtonMouseExit(const CEGUI::EventArgs &eventArgs)
{
	m_pQuickConnectButton->setAlpha(1);
	return true;
}

bool CMainMenu::OnServerBrowserButtonMouseEnter(const CEGUI::EventArgs &eventArgs)
{
	m_pServerBrowserButton->setAlpha(0.5f);
	return true;
}

bool CMainMenu::OnServerBrowserButtonMouseExit(const CEGUI::EventArgs &eventArgs)
{
	m_pServerBrowserButton->setAlpha(1);
	return true;
}

bool CMainMenu::OnSettingsButtonMouseEnter(const CEGUI::EventArgs &eventArgs)
{
	m_pSettingsButton->setAlpha(0.5f);
	return true;
}

bool CMainMenu::OnSettingsButtonMouseExit(const CEGUI::EventArgs &eventArgs)
{
	m_pSettingsButton->setAlpha(1);
	return true;
}

bool CMainMenu::OnCreditsButtonMouseEnter(const CEGUI::EventArgs &eventArgs)
{
	m_pCreditsButton->setAlpha(0.5f);
	return true;
}

bool CMainMenu::OnCreditsButtonMouseExit(const CEGUI::EventArgs &eventArgs)
{
	m_pCreditsButton->setAlpha(1);
	return true;
}

bool CMainMenu::OnExitButtonMouseEnter(const CEGUI::EventArgs &eventArgs)
{
	m_pExitButton->setAlpha(0.5f);
	return true;
}

bool CMainMenu::OnExitButtonMouseExit(const CEGUI::EventArgs &eventArgs)
{
	m_pExitButton->setAlpha(1);
	return true;
}

bool CMainMenu::OnExitButtonMouseClick(const CEGUI::EventArgs &eventArgs)
{
	// Are we connected to the network?
	if (g_pCore->GetNetworkManager()->IsConnected())
	{
		// Disconnect and shutdown RakNet
		g_pCore->GetNetworkManager()->Shutdown(500, true);
	}

	// Close IV:Network
	ExitProcess(0);
	return true;
}