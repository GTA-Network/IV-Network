
#ifndef CMainMenu_h
#define CMainMenu_h

#include <Common.h>
#include "CGUI.h"

class CMainMenu
{
private:
	CGUI * m_pGUI;
	CEGUI::Window * m_pWindow;
	bool			m_bVisible;

public:
	CMainMenu(CGUI * pGUI);
	~CMainMenu();

	bool Initialize();

	bool OnQuickConnectButtonMouseClick(const CEGUI::EventArgs &eventArgs);

	void SetVisible(bool bVisible);
};

#endif