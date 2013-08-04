//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CContextData.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CContextData_h
#define CContextData_h

#include <Common.h>
#include <Game/IVEngine/CIVPlayerInfo.h>
#include <Game/IVEngine/CIVPlayerPed.h>
#include <Game/IVEngine/CIVPad.h>

class CContextData {
private:
	CIVPlayerInfo			* m_pPlayerInfo;
	CIVPlayerPed			* m_pPlayerPed;
	CIVPad					* m_pPad;

public:

	CContextData(CIVPlayerInfo * pPlayerInfo)
	{
		// Set the player info
		SetPlayerInfo(pPlayerInfo);

		// Set the player ped
		SetPlayerPed(NULL);

		// Create the pad
		m_pPad = new CIVPad();
	}

	~CContextData()
	{
		// Delete the pad
		SAFE_DELETE(m_pPad);
	}

	void              SetPlayerPed(CIVPlayerPed * pPlayerPed) { m_pPlayerPed = pPlayerPed; }
	CIVPlayerPed    * GetPlayerPed() { return m_pPlayerPed; }

	void              SetPlayerInfo(CIVPlayerInfo * pPlayerInfo) { m_pPlayerInfo = pPlayerInfo; }
	CIVPlayerInfo   * GetPlayerInfo() { return m_pPlayerInfo; }

	CIVPad			* GetPad() { return m_pPad; }

};

class CContextDataManager {
private:
	static std::list< CContextData *>	m_contextDataList;

public:

	CContextDataManager() { };
	~CContextDataManager();

	static	CContextData			* CreateContextData(CIVPlayerInfo * pPlayerInfo);
	static	void					DestroyContextData(CContextData * pContextData);

	static CContextData				* GetContextData(BYTE bytePlayerNumber);
	static CContextData				* GetContextData(CIVPlayerInfo * pPlayerInfo);
	static CContextData				* GetContextData(IVPlayerInfo * pPlayerInfo);
	static CContextData				* GetContextData(CIVPlayerPed * pPlayerPed);
	static CContextData				* GetContextData(IVPlayerPed * pPlayerPed);

};


#endif // CContextData_h