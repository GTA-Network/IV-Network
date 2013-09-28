//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CMainMenu.cpp
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CCore.h"
extern CCore *g_pCore;

CMainMenu::CMainMenu(Gwen::Controls::Canvas* pCanvas) : Gwen::Controls::Base(pCanvas)
{
	// Set the default information of the Main Menu
	SetPadding(Gwen::Padding(0, 0));	
	SetPos(10, 300);
	SetSize(1920, 1200);

	// Quick Connect Button
	Gwen::Controls::Button* pQuickConnect = new Gwen::Controls::Button(this);
	pQuickConnect->SetText("Quick Connect");
	pQuickConnect->SetSize(150, 30);
	pQuickConnect->SetPos(350, 250);
	pQuickConnect->onPress.Add(this, &CMainMenu::Connect);
	
	// Connect Button
	Gwen::Controls::Button* pConnect =  new Gwen::Controls::Button(this);
	pConnect->SetText("Connect");
	pConnect->SetSize(150, 30);
	pConnect->SetPos(505, 250);

	// About Button
	Gwen::Controls::Button* pAbout = new Gwen::Controls::Button(this);
	pAbout->SetText("About");
	pAbout->SetSize(150, 30);
	pAbout->SetPos(660, 250);
	pAbout->IsHovered();
	pAbout->onPress.Add(this, &CMainMenu::ShowAbout);

	// Exit Button
	Gwen::Controls::Button* pExit = new Gwen::Controls::Button(this);
	pExit->SetText("Exit");
	pExit->SetSize(150, 30);
	pExit->SetPos(815, 250);
	pExit->onPress.Add(this, &CMainMenu::Exit);
}

void CMainMenu::Connect(Gwen::Controls::Base* pControl)
{
	g_pCore->ConnectToServer();
}

void CMainMenu::ShowAbout(Gwen::Controls::Base* pControl)
{
	Gwen::Controls::WindowControl* pAboutWindow = new Gwen::Controls::WindowControl(GetCanvas());
	pAboutWindow->SetTitle("About IV:Network");
	pAboutWindow->SetSize(200 + rand() % 100, 200 + rand() % 100);
	pAboutWindow->MakeModal(true);
	pAboutWindow->SetDeleteOnClose(true);
}

void CMainMenu::Exit(Gwen::Controls::Base* pControl)
{
	TerminateProcess(GetCurrentProcess(), 0);
}
	
	
	
	