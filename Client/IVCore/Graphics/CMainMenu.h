//========== IV:Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CMainMenu.h
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CMainMenu_h
#define CMainMenu_h

#include <Common.h>
#include "CGUI.h"

class CMainMenu
{
private:
	CGUI * m_pGUI;
	bool			  m_bVisible;
	bool			  m_bVisibleEx;

	// Main Menu Stuff
	CGUIStaticImage	* m_pBackground;
	CGUIStaticText	* m_pQuickConnectButton;
	CGUIStaticText  * m_pServerBrowserButton;
	CGUIStaticText  * m_pSettingsButton;
	CGUIStaticText  * m_pCreditsButton;
	CGUIStaticText  * m_pExitButton;
	CGUIStaticText	* CreateButton(char * szText, CEGUI::UVector2 vecSize, CEGUI::UVector2 vecPosition);

	// Quick Connect Stuff
	CGUIFrameWindow	* m_pQuickConnectWindow;
	CGUIStaticText	* m_pQuickConnectNicknameText;
	CGUIEditBox		* m_pQuickConnectNamenameEditBox;
	CGUIStaticText	* m_pQuickConnectIPStaticText;
	CGUIEditBox		* m_pQuickConnectIPEditBox;
	CGUIStaticText	* m_pQuickConnectPasswordStaticText;
	CGUIEditBox		* m_pQuickConnectPasswordEditBox;
	CGUIButton		* m_pQuickConnectConnectButton;

	bool OnQuickConnectButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool OnQuickConnectButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool OnQuickConnectButtonMouseClick(const CEGUI::EventArgs &eventArgs);
	bool OnServerBrowserButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool OnServerBrowserButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool OnSettingsButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool OnSettingsButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool OnCreditsButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool OnCreditsButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool OnExitButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool OnExitButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool OnExitButtonMouseClick(const CEGUI::EventArgs &eventArgs);
	bool OnQuickConnectCloseClick(const CEGUI::EventArgs &eventArgs);
	bool OnQuickConnectIPEditBoxKeyUp(const CEGUI::EventArgs &eventArgs);
	bool OnQuickConnectConnectButtonClick(const CEGUI::EventArgs &eventArgs);
	void OnQuickConnectSubmit();

public:
	CMainMenu(CGUI * pGUI);
	~CMainMenu();

	bool Initialize();

	void SetVisible(bool bVisible);
	void SetQuickConnectVisible(bool bVisible);
	bool IsMainMenuVisible() { return m_bVisible; }

	static void OnExitButtonMouseClickConfirm(eGUIMessageBoxResponse type);
};

#endif