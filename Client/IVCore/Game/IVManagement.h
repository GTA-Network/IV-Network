//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: IVManagement.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef IVManagement_h
#define IVManagement_h

#include <Game/IVEngine/CIVTrain.h>
#include <Game/Entity/CVehicleEntity.h>

struct InternalThread
{
	HANDLE			hThreadHandle;
	HANDLE			hThreadId;
	DWORD			dwStartAddress;
	const char		* szThreadTitle;
	const char		* szComment;
	bool			bInitialised;
};

struct InternalTrainHandle
{
	unsigned int	m_uiScriptingHandle;
	CVehicleEntity	*pVehicle;
	IVTrain			*pTrain;
	CIVTrain		*pCIVTrain;
	bool			m_bInitialised;

};

class IVManagement {
private:
	InternalTrainHandle	m_pTrains[MAX_TRAINS];

public:
						IVManagement();
						~IVManagement() { };

	void				CreateTrain(CVector3 vecPosition, BYTE iWagons, float fSpeed, bool bDirection);
	static void			ProcessTrain(LPVOID lpParameter);
	BYTE				GetFreeTrainSlot();
	BYTE				GetTrainCount();
	void				Pulse();
};
#endif // IVManagement_h