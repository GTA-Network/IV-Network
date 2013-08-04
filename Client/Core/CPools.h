//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CPools.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CPools_h
#define CPools_h

#include <Common.h>
#include <Game\IVEngine\CIVCam.h>
#include <Game\IVEngine\CIVPed.h>
#include <Game\IVEngine\CIVVehicle.h>
#include <Game\IVEngine\CIVPlayerPed.h>
#include <Game\IVEngine\CIVTask.h>

#define				PLAYER_INFO_ARRAY_SIZE			32

template <class T>
class CIVPool;

class CPools
{

private:

	CIVPool< IVPed >				* m_pPedPool;
	CIVPool< IVVehicle >			* m_pVehiclePool;
	CIVPool< IVTask >				* m_pTaskPool;
	CIVPool< IVCam >				* m_pCamPool;

public:

	CPools( );
	~CPools( );

	void							Initialise( );

	static	IVPlayerInfo			* GetPlayerInfoFromIndex( unsigned int uiIndex );
	static	IVPlayerInfo			* GetPlayerInfoFromPlayerPed( IVPlayerPed * pPlayerPed );

	static	unsigned int			GetIndexFromPlayerInfo( IVPlayerInfo * pPlayerInfo );
	static	void					SetPlayerInfoAtIndex( unsigned int uiIndex, IVPlayerInfo * pPlayerInfo );
	
	static	unsigned int			FindFreePlayerInfoIndex( );

	static	unsigned int			GetLocalPlayerIndex( );
	static	void					SetLocalPlayerIndex( unsigned int uiIndex );
	
	CIVPool< IVPed >				* GetPedPool( ) { return m_pPedPool; }
	CIVPool< IVVehicle >			* GetVehiclePool( ) { return m_pVehiclePool; }
	CIVPool< IVTask >				* GetTaskPool( ) { return m_pTaskPool; }
	CIVPool< IVCam >				* GetCamPool( ) { return m_pCamPool; }

};

#endif // CPools_h