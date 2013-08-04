//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CIVCam.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVCam.h"

CIVCam::CIVCam( )
{
	// Set the cam
	SetCam( NULL );
}

CIVCam::CIVCam( IVCam * pCam )
{
	// Set the cam
	SetCam( pCam );
}

CIVCam::~CIVCam( )
{

}