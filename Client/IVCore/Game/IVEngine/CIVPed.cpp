/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
	m_pPedTaskManager = nullptr;

	m_pPedWeapons = nullptr;

	// Set the ped
	SetPed(pPed);
}

CIVPed::~CIVPed()
{
	// Set the ped
	SetPed(nullptr);
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

		m_pPedWeapons = new CIVPedWeapons(&pPed->m_weapons, this);
	}
}

IVPed * CIVPed::GetPed()
{
	return (IVPed *)GetPhysical();
}

void CIVPed::SetPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	if (GetPed())
		GetPed()->m_pPlayerInfo = pPlayerInfo;
}

IVPlayerInfo * CIVPed::GetPlayerInfo()
{
	if (GetPed())
		return GetPed()->m_pPlayerInfo;

	return nullptr;
}

void CIVPed::SetCurrentHeading(float fCurrentHeading)
{
	if (GetPed())
		GetPed()->m_fCurrentHeading = fCurrentHeading;
}

float CIVPed::GetCurrentHeading()
{
	if (GetPed())
		return GetPed()->m_fCurrentHeading;

	return 0.0f;
}

void CIVPed::SetDucking(bool bDucking)
{
	if (GetPed())
		((void(__thiscall *) (IVPed *, bool, int))(COffsets::FUNC_CPed__SetDucking))(GetPed(), bDucking, -1);
}

bool CIVPed::IsDucking()
{
	if (GetPed())
		return ((bool(__thiscall *) (IVPed *))(COffsets::FUNC_CPed__IsDucking))(GetPed());

	return false;
}

bool CIVPed::IsInVehicle()
{
	if (GetPed())
		return ((GetPed()->m_byteUnknown & 4) != 0);

	return false;
}

void CIVPed::SetCurrentVehicle(IVVehicle * pVehicle)
{
	if (GetPed())
		GetPed()->m_pCurrentVehicle = pVehicle;
}

IVVehicle * CIVPed::GetCurrentVehicle()	
{
	if (GetPed())
		return GetPed()->m_pCurrentVehicle;

	return nullptr;
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