//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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

CIVPed::CIVPed() :
	CIVPhysical()
{

}

CIVPed::CIVPed(IVPed * pPed) :
	CIVPhysical(pPed)
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
		unsigned int uiPedHandle = g_pCore->GetGame()->GetPools()->GetPedPool()->HandleOf(pPed);
		DWORD GetNumberOfCharDrawableVariations = (g_pCore->GetBase() + 0xC0B9D0);

		_asm	mov esi, esp  
		_asm	mov	eax, dword ptr [ucBodyLocation]  
		_asm	push eax  
		_asm	mov ecx, dword ptr [uiPedHandle]  
		_asm	push ecx  
		_asm	call dword ptr [GetNumberOfCharDrawableVariations]  
		_asm	add esp,8 
		_asm	mov dword ptr [uiDrawableVariations], eax  

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
		unsigned int uiPedHandle = g_pCore->GetGame()->GetPools()->GetPedPool()->HandleOf(pPed);
		DWORD GetNumberOfCharTextureVariations = (g_pCore->GetBase() + 0xC0BA30);

		_asm	mov esi, esp;
		_asm	mov eax, dword ptr [uiPart]; 
		_asm	push eax;
		_asm	mov ecx, dword ptr [ucBodyLocation];
		_asm	push ecx;
		_asm	mov edx, dword ptr [uiPedHandle];
		_asm	push edx;
		_asm	call dword ptr [GetNumberOfCharTextureVariations];
		_asm	add esp, 0Ch;
		_asm	mov dword ptr [uiTextureVariations], eax; 

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
		unsigned int uiPedHandle = g_pCore->GetGame()->GetPools()->GetPedPool()->HandleOf(pPed);
		DWORD SetClothes = (g_pCore->GetBase() + 0xC0BA70);
		
		_asm	mov esi,esp  
		_asm	mov	eax,dword ptr [uiTexture]  
		_asm	push eax  
		_asm	mov ecx,dword ptr [uiVariation]  
		_asm	push ecx  
		_asm	mov edx,dword ptr [ucBodyLocation]  
		_asm	push edx  
		_asm	mov eax,dword ptr [uiPedHandle]  
		_asm	push eax  
		_asm	call dword ptr [SetClothes]  
		_asm	add esp,10h;
	}
}