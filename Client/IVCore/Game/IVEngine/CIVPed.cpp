//================ IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ================
//
// File: CIVPed.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVPed.h"
#include <CCore.h>
#include "CIVPedTaskManager.h"
extern CCore * g_pCore;

CIVPed::CIVPed() : CIVPhysical()
{

}

CIVPed::CIVPed(IVPed * pPed) : CIVPhysical(pPed)
{
	// Reset the task manager
	m_pPedTaskManager = NULL;

	// Set the ped
	SetPed(pPed);
}

CIVPed::~CIVPed()
{
	// Set the ped
	SetPed(NULL);
}

void CIVPed::SetPed(IVPed * pPed)
{
	SetPhysical(pPed);

	// Do we have a valid task manager?
	if(m_pPedTaskManager)
	{
		// Delete the ped task manager
		SAFE_DELETE(m_pPedTaskManager);
	}

	// Do we have a valid ped pointer?
	if(pPed)
	{
		// Create the ped task manager
		m_pPedTaskManager = new CIVPedTaskManager(&pPed->m_pPedIntelligence->m_pedTaskManager, this);
	}
}

IVPed * CIVPed::GetPed()
{
	return (IVPed *)GetPhysical();
}

void CIVPed::SetPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	// Get the ped
	IVPed * pPed = GetPed();

	// Set the player info
	if(pPed)
		pPed->m_pPlayerInfo = pPlayerInfo;
}

IVPlayerInfo * CIVPed::GetPlayerInfo()
{
	// Get the ped
	IVPed * pPed = GetPed();

	// Get the player info
	if(pPed)
		return pPed->m_pPlayerInfo;

	return NULL;
}

void CIVPed::SetCurrentHeading(float fCurrentHeading)
{
	// Get the ped
	IVPed * pPed = GetPed();

	// Set the current heading
	if(pPed)
		pPed->m_fCurrentHeading = fCurrentHeading;
}

float CIVPed::GetCurrentHeading()
{
	// Get the ped
	IVPed * pPed = GetPed();

	// Get the current heading
	if(pPed)
		return pPed->m_fCurrentHeading;

	return 0.0f;
}

void CIVPed::SetDucking(bool bDucking)
{
	// Get the ped
	IVPed * pPed = GetPed();

	if(pPed)
	{
		int iDuck = (int)bDucking;

		_asm	push -1;
		_asm	push iDuck;
		_asm	mov ecx, pPed;
		_asm	call COffsets::FUNC_CPed__SetDucking;
	}
}

bool CIVPed::IsDucking()
{
	// Get the ped
	IVPed * pPed = GetPed();

	if(pPed)
	{
		bool bDucking = false;

		_asm	mov ecx, pPed;
		_asm	call COffsets::FUNC_CPed__IsDucking;
		_asm	mov bDucking, al;

		return bDucking;
	}

	return false;
}

bool CIVPed::IsInVehicle()
{
	// Get the ped pointer
	IVPed * pPed = GetPed();

	// Is the ped pointer valid?
	if(pPed)
		return ((pPed->m_byteUnknown & 4) != 0);

	return false;
}

void CIVPed::SetCurrentVehicle(IVVehicle * pVehicle)
{
	// Get the ped pointer
	IVPed * pPed = GetPed();

	// Is the ped pointer valid?
	if(pPed)
		pPed->m_pCurrentVehicle = pVehicle;
}

IVVehicle * CIVPed::GetCurrentVehicle()	
{
	// Get the ped pointer
	IVPed * pPed = GetPed();

	// Is the ped pointer valid?
	if(pPed)
		return pPed->m_pCurrentVehicle;

	return NULL;
}

unsigned int CIVPed::GetNumberOfCharDrawableVariations(unsigned int ucBodyLocation)
{
	// Get the ped pointer
	IVPed * pPed = GetPed();

	// Is the ped pointer valid?
	if(pPed)
	{
		unsigned int uiDrawableVariations;

		DWORD DWORD_157D310 = (g_pCore->GetBase() + 0x157D310);
		DWORD SUB_9440E0 = (g_pCore->GetBase() + 0x9440E0);

		_asm	mov ecx, pPed;
		_asm	mov edx, DWORD_157D310[ecx*4];
		_asm	mov eax, ucBodyLocation;
		_asm	mov ecx, [edx+128h];
		_asm	push eax;
		_asm	call SUB_9440E0;
		_asm	movzx eax, al;
		_asm	mov uiDrawableVariations, eax;
		_asm	retn;

		return uiDrawableVariations;
	}
	else
		return 0;
}

unsigned int CIVPed::GetNumberOfCharTextureVariations(unsigned int ucBodyLocation, unsigned int uiPart)
{
	// Get the ped pointer
	IVPed * pPed = GetPed();

	// Is the ped pointer valid?
	if(pPed)
	{
		unsigned int uiTextureVariations;

		DWORD DWORD_157D310 = (g_pCore->GetBase() + 0x157D310);
		DWORD SUB_944080 = (g_pCore->GetBase() + 0x944080);

		_asm mov ecx, pPed;
		_asm mov edx, DWORD_157D310[ecx*4];
		_asm mov eax, uiPart;
		_asm mov ecx, [edx+128h];
		_asm mov edx, ucBodyLocation;
		_asm push eax;
		_asm push edx;
		_asm call SUB_944080;
		_asm movzx eax, al;
		_asm mov uiTextureVariations, eax;
		_asm retn;

		return uiTextureVariations;
	}
	else
		return 0;
}

void CIVPed::SetClothes(unsigned int ucBodyLocation, unsigned int uiVariation, unsigned int uiTexture)
{
	// Get the ped pointer
	IVPed * pPed = GetPed();

	// Is the ped pointer valid?
	if(pPed)
	{
		DWORD SUB_944900 = (g_pCore->GetBase() + 0x944900);

		// Move ped to ecx->eax register
		_asm mov ecx, pPed;
		_asm mov eax, [ecx];

		// Move third parameter into edxy and push it to the stack
		_asm mov edx, uiTexture;
		_asm mov ecx, [eax+21Ch];
		_asm push edx;
		
		// Move second parameter into edx and push it to the stack
		_asm mov edx, [uiVariation];
		_asm push edx;

		// Move first parameter into edx and push it to the stack
		_asm mov edx, [ucBodyLocation];
		_asm push edx;

		// Move *(BYTE *)(pPed + 537) and push it to the stack
		_asm movzx edx, byte ptr [eax+219h];
		_asm push edx;

		// Push *(DWORD *)(pPed + 540) to the stack [added mov ecx, [eax+21Ch(540)] before]
		_asm push ecx;

		// Push *(DWORD *)(pPed + 540) + 128 to the stack
		_asm add ecx, 80h;
		_asm push ecx;

		// Push the pPed to the stack
		_asm push eax;

		// Call our SetClothes function
		_asm call SUB_944900;

		// Cleanup stack and exit
		_asm add esp, 1Ch;
		_asm retn;
	}
}