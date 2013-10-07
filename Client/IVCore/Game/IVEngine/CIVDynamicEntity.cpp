//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVDynamicEntity.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVDynamicEntity.h"

CIVDynamicEntity::CIVDynamicEntity( ) :
	CIVEntity( )
{

}

CIVDynamicEntity::CIVDynamicEntity( IVDynamicEntity * pDynamicEntity ) :
	CIVEntity( pDynamicEntity )
{

}

CIVDynamicEntity::~CIVDynamicEntity( )
{

}

void CIVDynamicEntity::SetDynamicEntity( IVDynamicEntity * pDynamicEntity )
{
	SetEntity( (IVEntity *)pDynamicEntity );
}

IVDynamicEntity * CIVDynamicEntity::GetDynamicEntity( )
{
	return (IVDynamicEntity *)GetEntity( );
}