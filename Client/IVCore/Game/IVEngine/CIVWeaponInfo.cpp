//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CIVWeaponInfo.cpp
// Project: Client.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVWeaponInfo.h"
#include <CLogFile.h>

CIVWeaponInfo::CIVWeaponInfo() :
	m_pWeaponInfo(NULL)
{
}

CIVWeaponInfo::CIVWeaponInfo(eWeaponType weaponType, IVWeaponInfo * pWeaponInfo) :
	m_weaponType(weaponType), m_pWeaponInfo(pWeaponInfo)
{
}

CIVWeaponInfo::~CIVWeaponInfo()
{
}