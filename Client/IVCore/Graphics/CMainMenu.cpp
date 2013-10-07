//========== IV:Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CMainMenu.cpp
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CMainMenu.h"
#include <CCore.h>
#include <IV/CIVScript.h>

extern CCore* g_pCore;

CMainMenu::CMainMenu(CGUI* pGUI) :
	m_pGUI(pGUI)
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

	if (m_pQuickConnectWindow)
		m_pGUI->RemoveGUIWindow(m_pQuickConnectWindow);
}

bool CMainMenu::Initialize()
{	
	try
	{
		CEGUI::ImagesetManager::getSingleton().createFromImageFile("Background", "Background.png");
	}
	catch (CEGUI::InvalidRequestException e)
	{
		MessageBox(NULL, "Failed to load main menu background", "IV:Network Error", MB_OK || MB_ICONERROR);
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
	m_pBackground->setProperty("Image", "set:Background image:full_image");
	/*m_pBackground->setProperty("InheritsAlpha", "false");
	m_pBackground->setAlpha(0.975f);*/
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
	m_bVisible = bVisible;
	
	m_pGUI->SetCursorVisible(bVisible);

	m_pBackground->setVisible(bVisible);
	m_pQuickConnectButton->setVisible(bVisible);
	m_pServerBrowserButton->setVisible(bVisible);
	m_pSettingsButton->setVisible(bVisible);
	m_pCreditsButton->setVisible(bVisible);
	m_pExitButton->setVisible(bVisible);
}

void CMainMenu::SetQuickConnectVisible(bool bVisible)
{
	m_pQuickConnectWindow->setVisible(bVisible);
	m_pQuickConnectWindow->setProperty("AlwaysOnTop", "true");
	m_pQuickConnectWindow->activate();

	m_bVisibleEx = bVisible;
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
	float fWidth = (float) m_pGUI->GetDisplayWidth();
	float fHeight = (float) m_pGUI->GetDisplayHeight();

	m_pQuickConnectWindow = m_pGUI->CreateGUIFrameWindow();
	m_pQuickConnectWindow->setText("IV:Network Quick Connect");
	m_pQuickConnectWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0, 300), CEGUI::UDim(0, 240)));
	m_pQuickConnectWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, fWidth / 2 - 150.0f), CEGUI::UDim(0, fHeight / 2 - 120.0f)));
	m_pQuickConnectWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&CMainMenu::OnQuickConnectCloseClick, this));
	m_pQuickConnectWindow->setProperty("FrameEnabled", "false");
	m_pQuickConnectWindow->setVisible(true);

	m_pQuickConnectIPStaticText = m_pGUI->CreateGUIStaticText(m_pQuickConnectWindow);
	m_pQuickConnectIPStaticText->setText("IP Address:");
	m_pQuickConnectIPStaticText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 260), CEGUI::UDim(0, 20)));
	m_pQuickConnectIPStaticText->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 20), CEGUI::UDim(0, 20)));
	m_pQuickConnectIPStaticText->setProperty("FrameEnabled", "false");
	m_pQuickConnectIPStaticText->setProperty("BackgroundEnabled", "false");
	//m_pQuickConnectIPStaticText->setFont(m_pGUI->GetFont("tahoma-bold"));

	m_pQuickConnectIPEditBox = m_pGUI->CreateGUIEditBox(m_pQuickConnectWindow);
	m_pQuickConnectIPEditBox->setText("");
	m_pQuickConnectIPEditBox->setSize(CEGUI::UVector2(CEGUI::UDim(0, 260), CEGUI::UDim(0, 30)));
	m_pQuickConnectIPEditBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 20), CEGUI::UDim(0, 50)));
	m_pQuickConnectIPEditBox->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&CMainMenu::OnQuickConnectIPEditBoxKeyUp, this));

	m_pQuickConnectPasswordStaticText = m_pGUI->CreateGUIStaticText(m_pQuickConnectWindow);
	m_pQuickConnectPasswordStaticText->setText("Password:");
	m_pQuickConnectPasswordStaticText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 260), CEGUI::UDim(0, 20)));
	m_pQuickConnectPasswordStaticText->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 20), CEGUI::UDim(0, 90)));
	m_pQuickConnectPasswordStaticText->setProperty("FrameEnabled", "false");
	m_pQuickConnectPasswordStaticText->setProperty("BackgroundEnabled", "false");
	//m_pQuickConnectPasswordStaticText->setFont(m_pGUI->GetFont("tahoma-bold"));

	m_pQuickConnectPasswordEditBox = m_pGUI->CreateGUIEditBox(m_pQuickConnectWindow);
	m_pQuickConnectPasswordEditBox->setText("");
	m_pQuickConnectPasswordEditBox->setSize(CEGUI::UVector2(CEGUI::UDim(0, 260), CEGUI::UDim(0, 30)));
	m_pQuickConnectPasswordEditBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 20), CEGUI::UDim(0, 120)));
	m_pQuickConnectPasswordEditBox->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&CMainMenu::OnQuickConnectIPEditBoxKeyUp, this));
	m_pQuickConnectPasswordEditBox->setProperty("MaskText", "true");

	m_pQuickConnectConnectButton = m_pGUI->CreateGUIButton(m_pQuickConnectWindow);
	m_pQuickConnectConnectButton->setText("Connect");
	m_pQuickConnectConnectButton->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 40)));
	m_pQuickConnectConnectButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 50), CEGUI::UDim(0, 160)));
	m_pQuickConnectConnectButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CMainMenu::OnQuickConnectConnectButtonClick, this));
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

void CMainMenu::OnExitButtonMouseClickConfirm(eGUIMessageBoxResponse type)
{
	if (type == GUI_MESSAGEBOX_YES)
	{
		// Are we connected to the network?
		if (g_pCore->GetNetworkManager()->IsConnected())
		{
			// Disconnect and shutdown RakNet
			g_pCore->GetNetworkManager()->Shutdown(500, true);
		}

		// Close IV:Network
		ExitProcess(0);
	}
}

bool CMainMenu::OnExitButtonMouseClick(const CEGUI::EventArgs &eventArgs)
{
	m_pGUI->ShowMessageBox("Are you sure you want to leave IV:Network?", "Leaving IV:Network", GUI_MESSAGEBOXTYPE_YESNO, OnExitButtonMouseClickConfirm);
	return true;
}

bool CMainMenu::OnQuickConnectCloseClick(const CEGUI::EventArgs &eventArgs)
{
	// Hide the whole Quick Connect Box
	SetQuickConnectVisible(false);

	// Set the password to nothing for security purposes
	m_pQuickConnectPasswordEditBox->setText("");

	return true;
}

bool CMainMenu::OnQuickConnectIPEditBoxKeyUp(const CEGUI::EventArgs &eventArgs)
{
	const CEGUI::KeyEventArgs& key_args = static_cast<const CEGUI::KeyEventArgs&>(eventArgs);
	if (key_args.scancode == CEGUI::Key::Return)
	{
		OnQuickConnectSubmit();
		return true;
	}
	return true;
}

void CMainMenu::OnQuickConnectSubmit()
{
	CString strHost;
	unsigned short usPort = 9999;

	// Get the password
	CString strPassword(m_pQuickConnectPasswordEditBox->getText().c_str());

	// Set the ip, port and password
	CVAR_SET_STRING("ip", strHost);
	CVAR_SET_INTEGER("port", usPort);
	CVAR_SET_STRING("pass", strPassword);

	// Hide the quick connect window
	SetVisible(false);

	CIVScript::DoScreenFadeIn(1000); //TODO: do this after connected to the sever

	// Enable the chat
	g_pCore->GetChat()->SetVisible(true);

	// Set nickname
	g_pCore->SetNick("Player"); // TODO: Make it so you can change your name

	// Conneting the player to the server
	g_pCore->ConnectToServer(strHost, usPort);

	// Hide the main menu elements
	SetVisible(false);
	SetQuickConnectVisible(false);
}

bool CMainMenu::OnQuickConnectConnectButtonClick(const CEGUI::EventArgs &eventArgs)
{
	OnQuickConnectSubmit();
	return true;
}