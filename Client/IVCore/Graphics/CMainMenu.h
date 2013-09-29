
#ifndef CMainMenu_h
#define CMainMenu_h

#include <Common.h>
#include "CGUI.h"

class CMainMenu
{
private:
	CGUI * m_pGUI;
	CEGUI::Window * m_pWindow;
public:
	CMainMenu(CGUI * pGUI);
	~CMainMenu();

	bool Initialize();

	bool OnQuickConnectButtonMouseClick(const CEGUI::EventArgs &eventArgs);
};

#endif