//========== IV:Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CPauseMenu.cpp
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CPauseMenu.h"
#include <CCore.h>
#include <IV/CIVScript.h>

extern CCore* g_pCore;

CPauseMenu::CPauseMenu(CGUI* pGUI) :
m_pGUI(pGUI)
{

}

CPauseMenu::~CPauseMenu()
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

bool CPauseMenu::Initialize()
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
	m_pBackground->setVisible(false);

#define fY 0.5f

	// Create the Quick Connect Button
	m_pQuickConnectButton = CreateButton("Quick Connect", CEGUI::UVector2(CEGUI::UDim(0.20f, 0), CEGUI::UDim(0.030f, 0)), CEGUI::UVector2(CEGUI::UDim(0.025f, 0), CEGUI::UDim(fY, 0)));
	m_pQuickConnectButton->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CPauseMenu::OnQuickConnectButtonMouseEnter, this));
	m_pQuickConnectButton->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CPauseMenu::OnQuickConnectButtonMouseExit, this));
	m_pQuickConnectButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&CPauseMenu::OnQuickConnectButtonMouseClick, this));
	m_pBackground->addChildWindow(m_pQuickConnectButton);

	// Create the Server Browser Button
	m_pServerBrowserButton = CreateButton("Server Browser", CEGUI::UVector2(CEGUI::UDim(0.20f, 0), CEGUI::UDim(0.030f, 0)), CEGUI::UVector2(CEGUI::UDim(0.275f, 0), CEGUI::UDim(fY, 0)));
	m_pServerBrowserButton->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CPauseMenu::OnServerBrowserButtonMouseEnter, this));
	m_pServerBrowserButton->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CPauseMenu::OnServerBrowserButtonMouseExit, this));
	m_pServerBrowserButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&CPauseMenu::OnServerBrowserButtonMouseClick, this));
	m_pBackground->addChildWindow(m_pServerBrowserButton);

	// Create the Settings Button
	m_pSettingsButton = CreateButton("Settings", CEGUI::UVector2(CEGUI::UDim(0.162f, 0), CEGUI::UDim(0.030f, 0)), CEGUI::UVector2(CEGUI::UDim(0.525f, 0), CEGUI::UDim(fY, 0)));
	m_pSettingsButton->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CPauseMenu::OnSettingsButtonMouseEnter, this));
	m_pSettingsButton->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CPauseMenu::OnSettingsButtonMouseExit, this));
	m_pSettingsButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&CPauseMenu::OnSettingsButtonMouseClick, this));
	m_pBackground->addChildWindow(m_pSettingsButton);

	// Create the Credits Button
	m_pCreditsButton = CreateButton("Credits", CEGUI::UVector2(CEGUI::UDim(0.08f, 0), CEGUI::UDim(0.030f, 0)), CEGUI::UVector2(CEGUI::UDim(0.75f, 0), CEGUI::UDim(fY, 0)));
	m_pCreditsButton->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CPauseMenu::OnCreditsButtonMouseEnter, this));
	m_pCreditsButton->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CPauseMenu::OnCreditsButtonMouseExit, this));
	m_pCreditsButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&CPauseMenu::OnCreditsButtonMouseClick, this));
	m_pBackground->addChildWindow(m_pCreditsButton);

	// Create the Exit Button
	m_pExitButton = CreateButton("Exit", CEGUI::UVector2(CEGUI::UDim(0.08f, 0), CEGUI::UDim(0.030f, 0)), CEGUI::UVector2(CEGUI::UDim(0.925f, 0), CEGUI::UDim(fY, 0)));
	m_pExitButton->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CPauseMenu::OnExitButtonMouseEnter, this));
	m_pExitButton->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CPauseMenu::OnExitButtonMouseExit, this));
	m_pExitButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&CPauseMenu::OnExitButtonMouseClick, this));
	m_pBackground->addChildWindow(m_pExitButton);

#undef fY

	return true;
}

void CPauseMenu::SetVisible(bool bVisible)
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

void CPauseMenu::SetQuickConnectVisible(bool bVisible)
{
	m_pQuickConnectWindow->setVisible(bVisible);
	m_pQuickConnectWindow->setProperty("AlwaysOnTop", "true");
	m_pQuickConnectWindow->activate();

	m_bQuickConnectVisible = bVisible;
}

void CPauseMenu::SetSettingsVisible(bool bVisible)
{
	m_pSettingsWindow->setVisible(bVisible);
	m_pSettingsWindow->setProperty("AlwaysOnTop", "true");
	m_pSettingsWindow->activate();

	m_bSettingsVisible = bVisible;
}

CGUIStaticText * CPauseMenu::CreateButton(char * szText, CEGUI::UVector2 vecSize, CEGUI::UVector2 vecPosition)
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

bool CPauseMenu::OnQuickConnectButtonMouseClick(const CEGUI::EventArgs &eventArgs)
{
	float fWidth = (float) m_pGUI->GetDisplayWidth();
	float fHeight = (float) m_pGUI->GetDisplayHeight();

	m_pQuickConnectWindow = m_pGUI->CreateGUIFrameWindow();
	m_pQuickConnectWindow->setText("IV:Network Quick Connect");
	m_pQuickConnectWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0, 300), CEGUI::UDim(0, 250)));
	m_pQuickConnectWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, fWidth / 2 - 150.0f), CEGUI::UDim(0, fHeight / 2 - 120.0f)));
	m_pQuickConnectWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&CPauseMenu::OnQuickConnectCloseClick, this));
	m_pQuickConnectWindow->setProperty("FrameEnabled", "false");
	m_pQuickConnectWindow->setVisible(true);

	m_pQuickConnectIPStaticText = m_pGUI->CreateGUIStaticText(m_pQuickConnectWindow);
	m_pQuickConnectIPStaticText->setText("Hostname / IP Address:");
	m_pQuickConnectIPStaticText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 260), CEGUI::UDim(0, 20)));
	m_pQuickConnectIPStaticText->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 20), CEGUI::UDim(0, 20)));
	m_pQuickConnectIPStaticText->setProperty("FrameEnabled", "false");
	m_pQuickConnectIPStaticText->setProperty("BackgroundEnabled", "false");

	m_pQuickConnectIPEditBox = m_pGUI->CreateGUIEditBox(m_pQuickConnectWindow);
	m_pQuickConnectIPEditBox->setText(CString("%s:%i", CVAR_GET_STRING("ip"), CVAR_GET_INTEGER("port")).Get());
	m_pQuickConnectIPEditBox->setSize(CEGUI::UVector2(CEGUI::UDim(0, 260), CEGUI::UDim(0, 30)));
	m_pQuickConnectIPEditBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 20), CEGUI::UDim(0, 50)));
	m_pQuickConnectIPEditBox->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&CPauseMenu::OnQuickConnectIPEditBoxKeyUp, this));

	m_pQuickConnectPasswordStaticText = m_pGUI->CreateGUIStaticText(m_pQuickConnectWindow);
	m_pQuickConnectPasswordStaticText->setText("Password:");
	m_pQuickConnectPasswordStaticText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 260), CEGUI::UDim(0, 20)));
	m_pQuickConnectPasswordStaticText->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 20), CEGUI::UDim(0, 90)));
	m_pQuickConnectPasswordStaticText->setProperty("FrameEnabled", "false");
	m_pQuickConnectPasswordStaticText->setProperty("BackgroundEnabled", "false");

	m_pQuickConnectPasswordEditBox = m_pGUI->CreateGUIEditBox(m_pQuickConnectWindow);
	m_pQuickConnectPasswordEditBox->setText(CVAR_GET_STRING("pass").Get());
	m_pQuickConnectPasswordEditBox->setSize(CEGUI::UVector2(CEGUI::UDim(0, 260), CEGUI::UDim(0, 30)));
	m_pQuickConnectPasswordEditBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 20), CEGUI::UDim(0, 120)));
	m_pQuickConnectPasswordEditBox->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&CPauseMenu::OnQuickConnectIPEditBoxKeyUp, this));
	m_pQuickConnectPasswordEditBox->setProperty("MaskText", "true");

	m_pQuickConnectConnectButton = m_pGUI->CreateGUIButton(m_pQuickConnectWindow);
	m_pQuickConnectConnectButton->setText("Connect");
	m_pQuickConnectConnectButton->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 40)));
	m_pQuickConnectConnectButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 50), CEGUI::UDim(0, 160)));
	m_pQuickConnectConnectButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CPauseMenu::OnQuickConnectConnectButtonClick, this));
	return true;
}

bool CPauseMenu::OnSettingsButtonMouseClick(const CEGUI::EventArgs &eventArgs)
{
	// Does the Settings GUI already exists? If yes, delete it
	if (m_pSettingsWindow)
		m_pGUI->RemoveGUIWindow(m_pSettingsWindow);

	float fWidth = (float) m_pGUI->GetDisplayWidth();
	float fHeight = (float) m_pGUI->GetDisplayHeight();

	m_pSettingsWindow = m_pGUI->CreateGUIFrameWindow();
	m_pSettingsWindow->setText("IV:Network Settings");
	m_pSettingsWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0, 300), CEGUI::UDim(0, 220)));
	m_pSettingsWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, fWidth / 2 - 150.0f), CEGUI::UDim(0, fHeight / 2 - 120.0f)));
	m_pSettingsWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&CPauseMenu::OnSettingsCloseClick, this));
	m_pSettingsWindow->setProperty("FrameEnabled", "false");
	m_pSettingsWindow->setVisible(true);

	m_pSettingsStaticText = m_pGUI->CreateGUIStaticText(m_pSettingsWindow);
	m_pSettingsStaticText->setText("Username:");
	m_pSettingsStaticText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 260), CEGUI::UDim(0, 20)));
	m_pSettingsStaticText->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 20), CEGUI::UDim(0, 20)));
	m_pSettingsStaticText->setProperty("FrameEnabled", "false");
	m_pSettingsStaticText->setProperty("BackgroundEnabled", "false");

	m_pSettingsEditBox = m_pGUI->CreateGUIEditBox(m_pSettingsWindow);
	m_pSettingsEditBox->setText("");
	m_pSettingsEditBox->setSize(CEGUI::UVector2(CEGUI::UDim(0, 260), CEGUI::UDim(0, 30)));
	m_pSettingsEditBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 20), CEGUI::UDim(0, 50)));
	m_pSettingsEditBox->subscribeEvent(CEGUI::Editbox::EventKeyUp, CEGUI::Event::Subscriber(&CPauseMenu::OnSettingsEditBoxKeyUp, this));

	m_pSettingsButtonEx = m_pGUI->CreateGUIButton(m_pSettingsWindow);
	m_pSettingsButtonEx->setText("Apply");
	m_pSettingsButtonEx->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 40)));
	m_pSettingsButtonEx->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 50), CEGUI::UDim(0, 100)));
	m_pSettingsButtonEx->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CPauseMenu::OnSettingsMouseClick, this));
	return true;
}

bool CPauseMenu::OnQuickConnectButtonMouseEnter(const CEGUI::EventArgs &eventArgs)
{
	m_pQuickConnectButton->setAlpha(0.5f);
	return true;
}

bool CPauseMenu::OnQuickConnectButtonMouseExit(const CEGUI::EventArgs &eventArgs)
{
	m_pQuickConnectButton->setAlpha(1);
	return true;
}

bool CPauseMenu::OnServerBrowserButtonMouseEnter(const CEGUI::EventArgs &eventArgs)
{
	m_pServerBrowserButton->setAlpha(0.5f);
	return true;
}

bool CPauseMenu::OnServerBrowserButtonMouseExit(const CEGUI::EventArgs &eventArgs)
{
	m_pServerBrowserButton->setAlpha(1);
	return true;
}

bool CPauseMenu::OnServerBrowserButtonMouseClick(const CEGUI::EventArgs &eventArgs)
{
	m_pGUI->ShowMessageBox("This feature is temporary disabled.", "Server Browser", GUI_MESSAGEBOXTYPE_OK);
	return true;
}

bool CPauseMenu::OnSettingsButtonMouseEnter(const CEGUI::EventArgs &eventArgs)
{
	m_pSettingsButton->setAlpha(0.5f);
	return true;
}

bool CPauseMenu::OnSettingsButtonMouseExit(const CEGUI::EventArgs &eventArgs)
{
	m_pSettingsButton->setAlpha(1);
	return true;
}

bool CPauseMenu::OnCreditsButtonMouseEnter(const CEGUI::EventArgs &eventArgs)
{
	m_pCreditsButton->setAlpha(0.5f);
	return true;
}

bool CPauseMenu::OnCreditsButtonMouseExit(const CEGUI::EventArgs &eventArgs)
{
	m_pCreditsButton->setAlpha(1);
	return true;
}

bool CPauseMenu::OnCreditsButtonMouseClick(const CEGUI::EventArgs &eventArgs)
{
	m_pGUI->ShowMessageBox("This feature is temporary disabled.", "IV:Network Credits", GUI_MESSAGEBOXTYPE_OK);
	return true;
}

bool CPauseMenu::OnExitButtonMouseEnter(const CEGUI::EventArgs &eventArgs)
{
	m_pExitButton->setAlpha(0.5f);
	return true;
}

bool CPauseMenu::OnExitButtonMouseExit(const CEGUI::EventArgs &eventArgs)
{
	m_pExitButton->setAlpha(1);
	return true;
}

void CPauseMenu::OnExitButtonMouseClickConfirm(eGUIMessageBoxResponse type)
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

bool CPauseMenu::OnExitButtonMouseClick(const CEGUI::EventArgs &eventArgs)
{
	m_pGUI->ShowMessageBox("Are you sure you want to leave IV:Network?", "Leaving IV:Network", GUI_MESSAGEBOXTYPE_YESNO, OnExitButtonMouseClickConfirm);
	return true;
}

bool CPauseMenu::OnQuickConnectCloseClick(const CEGUI::EventArgs &eventArgs)
{
	// Hide the whole Quick Connect Box
	SetQuickConnectVisible(false);

	// Set the password to nothing for security purposes
	m_pQuickConnectPasswordEditBox->setText("");

	return true;
}

bool CPauseMenu::OnSettingsCloseClick(const CEGUI::EventArgs &eventArgs)
{
	// Hide the whole Quick Connect Box
	SetSettingsVisible(false);

	// Set the password to nothing for security purposes
	m_pSettingsEditBox->setText("");

	return true;
}

bool CPauseMenu::OnQuickConnectIPEditBoxKeyUp(const CEGUI::EventArgs &eventArgs)
{
	const CEGUI::KeyEventArgs& key_args = static_cast<const CEGUI::KeyEventArgs&>(eventArgs);
	if (key_args.scancode == CEGUI::Key::Return)
	{
		OnQuickConnectSubmit();
		return true;
	}
	return true;
}

bool CPauseMenu::OnSettingsEditBoxKeyUp(const CEGUI::EventArgs &eventArgs)
{
	const CEGUI::KeyEventArgs& key_args = static_cast<const CEGUI::KeyEventArgs&>(eventArgs);
	if (key_args.scancode == CEGUI::Key::Return)
	{
		OnSettingsApply();
		return true;
	}
	return true;
}

void CPauseMenu::OnSettingsApply()
{
	g_pCore->SetNick(CString(m_pSettingsEditBox->getText()).Get());

	m_pGUI->ShowMessageBox(CString("You have changed your name to %s.", m_pSettingsEditBox->getText()).Get(), "Applying Settings", GUI_MESSAGEBOXTYPE_OK);
}

void CPauseMenu::OnQuickConnectSubmit()
{
	char* cpHost;
	unsigned short usPort = 9999;

	if (strlen(m_pQuickConnectIPEditBox->getText()) == 0)
	{
		m_pQuickConnectIPEditBox->setText("127.0.0.1:9999");
	}

	int colon = -1;
	for (int i = 0; i < strlen(m_pQuickConnectIPEditBox->getText()); ++i)
	{
		if (m_pQuickConnectIPEditBox->getText()[i] == ':')
		{
			colon = i;
			break;
		}
	}

	if (colon == -1)
	{
		cpHost = m_pQuickConnectIPEditBox->getText();
		m_pQuickConnectIPEditBox->setText(CString("%s:9999", m_pQuickConnectIPEditBox->getText()).Get());
	}
	else
	{
		cpHost = m_pQuickConnectIPEditBox->getText();
		cpHost[colon] = '\0';
		usPort = atoi(m_pQuickConnectIPEditBox->getText() + colon + 1);
	}

	// Set the ip, port and password
	CVAR_SET_STRING("ip", cpHost);
	CVAR_SET_INTEGER("port", usPort);
	CVAR_SET_STRING("pass", m_pQuickConnectPasswordEditBox->getText());

	// Hide the quick connect window
	SetVisible(false);

	CIVScript::DoScreenFadeIn(1000); //TODO: do this after connected to the sever

	// Enable the chat
	g_pCore->GetChat()->SetVisible(true);

	// Conneting the player to the server
	g_pCore->ConnectToServer(cpHost, usPort, m_pQuickConnectPasswordEditBox->getText());

	// Hide the main menu elements
	SetVisible(false);
	SetQuickConnectVisible(false);
}

bool CPauseMenu::OnQuickConnectConnectButtonClick(const CEGUI::EventArgs &eventArgs)
{
	OnQuickConnectSubmit();
	return true;
}

bool CPauseMenu::OnSettingsMouseClick(const CEGUI::EventArgs &eventArgs)
{
	OnSettingsApply();
	return true;
}
