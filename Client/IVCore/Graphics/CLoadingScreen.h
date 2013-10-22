#ifndef CLoadingScreen_h
#define CLoadingScreen_h

#include <Common.h>
#include "CGUI.h"

class CLoadingScreen
{
private:
	CGUI * m_pGUI;

	CGUIStaticImage	* m_pBackground;

public:
	CLoadingScreen(CGUI * pGUI);
	~CLoadingScreen();

	bool Initialize();
	void SetVisible(bool bVisible);
};

#endif