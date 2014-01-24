//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CWeaponInfo.cpp
// Project: Client.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CWeaponInfo.h"
#include <CLogFile.h>

_GAME_BEGIN

CWeaponInfo::CWeaponInfo() :
	m_pWeaponInfo(nullptr)
{
}

CWeaponInfo::CWeaponInfo(eWeaponType weaponType, IWeaponInfo * pWeaponInfo) :
	m_weaponType(weaponType), 
	m_pWeaponInfo(pWeaponInfo)
{
}

CWeaponInfo::~CWeaponInfo()
{
}

_GAME_END