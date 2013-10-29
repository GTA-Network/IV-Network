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
	CGUI			* m_pGUI;
	bool			  m_bVisible;
	bool			  m_bQuickConnectVisible;
	bool			  m_bSettingsVisible;
	bool			  m_bServerBrowserVisible;

	// Main Menu Stuff
	CGUIStaticImage	* m_pBackground;
	CGUIStaticText	* m_pDisconnectButton;
	CGUIStaticText	* m_pQuickConnectButton;
	CGUIStaticText  * m_pServerBrowserButton;
	CGUIStaticText  * m_pSettingsButton;
	CGUIStaticText  * m_pCreditsButton;
	CGUIStaticText  * m_pExitButton;

	// Quick Connect Stuff
	CGUIFrameWindow	* m_pQuickConnectWindow;
	CGUIStaticText	* m_pQuickConnectNicknameText;
	CGUIEditBox		* m_pQuickConnectNamenameEditBox;
	CGUIStaticText	* m_pQuickConnectIPStaticText;
	CGUIEditBox		* m_pQuickConnectIPEditBox;
	CGUIStaticText	* m_pQuickConnectPasswordStaticText;
	CGUIEditBox		* m_pQuickConnectPasswordEditBox;
	CGUIButton		* m_pQuickConnectConnectButton;

	// Settings Stuff
	CGUIFrameWindow * m_pSettingsWindow;
	CGUIStaticText  * m_pSettingsStaticText;
	CGUIEditBox     * m_pSettingsEditBox;
	CGUIButton      * m_pSettingsButtonEx;

	// Server Browser Stuff
	CGUIFrameWindow		* m_pBrowserWindow;
	CGUIMultiColumnList * m_pBrowserList;
	CGUIButton			* m_pBrowserConnect;

	bool OnDisconnectButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool OnDisconnectButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool OnDisconnectButtonMouseClick(const CEGUI::EventArgs &eventArgs);
	bool OnQuickConnectButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool OnQuickConnectButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool OnQuickConnectButtonMouseClick(const CEGUI::EventArgs &eventArgs);
	bool OnServerBrowserButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool OnServerBrowserButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool OnServerBrowserButtonMouseClick(const CEGUI::EventArgs &eventArgs);
	bool OnServerBrowserExit(const CEGUI::EventArgs &eventArgs);
	bool OnServerClicked(const CEGUI::EventArgs &eventArgs);
	bool OnSettingsButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool OnSettingsButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool OnCreditsButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool OnCreditsButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool OnCreditsButtonMouseClick(const CEGUI::EventArgs &eventArgs);
	bool OnExitButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool OnExitButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool OnExitButtonMouseClick(const CEGUI::EventArgs &eventArgs);
	bool OnQuickConnectCloseClick(const CEGUI::EventArgs &eventArgs);
	bool OnQuickConnectIPEditBoxKeyUp(const CEGUI::EventArgs &eventArgs);
	bool OnQuickConnectConnectButtonClick(const CEGUI::EventArgs &eventArgs);
	void OnQuickConnectSubmit();
	bool OnSettingsButtonMouseClick(const CEGUI::EventArgs &eventArgs);
	bool OnSettingsCloseClick(const CEGUI::EventArgs &eventArgs);
	bool OnSettingsEditBoxKeyUp(const CEGUI::EventArgs &eventArgs);
	void OnSettingsApply();
	bool OnSettingsMouseClick(const CEGUI::EventArgs &eventArgs);


public:
	CMainMenu(CGUI * pGUI);
	~CMainMenu();

	bool Initialize();

	void SetVisible(bool bVisible);
	void SetQuickConnectVisible(bool bVisible);
	void SetSettingsVisible(bool bVisible);
	void SetBrowserVisible(bool bVisible);
	bool IsMainMenuVisible() { return m_bVisible; }

	static void OnExitButtonMouseClickConfirm(eGUIMessageBoxResponse type);
};

#endif