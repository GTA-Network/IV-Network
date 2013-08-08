//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CDevelopment.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CDevelopment.h"
#include <CCore.h>
extern CCore * g_pCore;

CDevelopment::CDevelopment()
{

}

CDevelopment::~CDevelopment()
{

}

void CDevelopment::Process()
{
	if(bDebugView && g_pCore->GetGame()->GetLocalPlayer() && g_pCore->GetGraphics())
	{
		float fCurrentLine = 325;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("LocalPlayer Debug:").Get());
	
		fCurrentLine += 15;

		CVector3 vecPosition;
		g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetPosition(vecPosition);
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Current Position: %.2f, %.2f ,%.2f,", vecPosition.fX, vecPosition.fY, vecPosition.fZ).Get());
	}
}