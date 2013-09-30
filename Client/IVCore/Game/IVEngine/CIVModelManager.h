//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVModelManager.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVModelManager_h
#define CIVModelManager_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>

class CIVModelManager{
public:

	static	int			GetModelIndexFromHash(DWORD dwModelHash);
	static	void		RequestModel(int iModelIndex, DWORD dwFlags = 0x1A);
	static	void		LoadRequestedModels();
	static	bool		HasModelLoaded(int iModelIndex);
	static	void		ReleaseModel(int iModelIndex);

	static	DWORD	VehicleIdToModelHash(int iModelId);
	static	int		ModelHashToVehicleId(DWORD dwModelHash);
};

#endif // CIVModelManager_h