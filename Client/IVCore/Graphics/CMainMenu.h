
#ifndef CMainMenu_h
#define CMainMenu_h

#include <Common.h>
#include "CGUI.h"

class CMainMenu
{
private:
	CGUI * m_pGUI;
	CEGUI::Window	* m_pWindow;
	bool			  m_bVisible;

	// Main Menu Stuff
	CGUIStaticImage	* m_pBackground;
	CGUIStaticText	* m_pQuickConnectButton;
	CGUIStaticText  * m_pServerBrowserButton;
	CGUIStaticText  * m_pSettingsButton;
	CGUIStaticText  * m_pCreditsButton;
	CGUIStaticText  * m_pExitButton;
	CGUIStaticText	* CreateButton(char * szText, CEGUI::UVector2 vecSize, CEGUI::UVector2 vecPosition);

	bool			OnQuickConnectButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool			OnQuickConnectButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool			OnServerBrowserButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool			OnServerBrowserButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool			OnSettingsButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool			OnSettingsButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool			OnCreditsButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool			OnCreditsButtonMouseExit(const CEGUI::EventArgs &eventArgs);
	bool			OnExitButtonMouseEnter(const CEGUI::EventArgs &eventArgs);
	bool			OnExitButtonMouseExit(const CEGUI::EventArgs &eventArgs);

public:
	CMainMenu(CGUI * pGUI);
	~CMainMenu();

	bool Initialize();

	bool OnQuickConnectButtonMouseClick(const CEGUI::EventArgs &eventArgs);
	bool OnExitButtonMouseClick(const CEGUI::EventArgs &eventArgs);

	void SetVisible(bool bVisible);
	bool IsMainMenuVisible() { return m_bVisible; }
};

#endif