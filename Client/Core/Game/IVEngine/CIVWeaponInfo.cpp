//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CIVWeaponInfo.cpp
// Project: Client.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVWeaponInfo.h"
#include <CLogFile.h>

CIVWeaponInfo::CIVWeaponInfo()
	: m_pWeaponInfo(NULL)
{
	m_pWeaponInfo = NULL;
}

CIVWeaponInfo::CIVWeaponInfo(eWeaponType weaponType, IVWeaponInfo * pWeaponInfo)
	: m_weaponType(weaponType),
	m_pWeaponInfo(pWeaponInfo)
{
}

CIVWeaponInfo::~CIVWeaponInfo()
{
}