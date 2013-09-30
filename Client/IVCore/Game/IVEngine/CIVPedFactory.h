//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPedFactory.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPedFactory_h
#define CIVPedFactory_h

#include "CIVPed.h"
#include <Game/CGame.h>
#include <Game/COffsets.h>
#include <CLogFile.h>

class IVPedFactory
{
public:
	virtual 			~IVPedFactory();
	virtual void 		Function1(); // pure virtual
	virtual IVPed* 		CreateDummyPed(int iModelIndex, Matrix34* pMatrix, bool createNetwork);
	virtual int 		RemovePed(IVPed*);
	virtual IVPed* 		CreatePed(int a1, int unk = 0);
	virtual IVPed* 		CreatePedIntelligent(WORD* wPlayerData, int iModelIndex, Matrix34* pMatrix, int remotePed, char couldNetworkPed);
	virtual int 		RemoveIntelligentPed(IVPed*);
	virtual IVPed* 		CreatePlayerPed(WORD* playerNumber, int iModelIndex, int playerNum, Matrix34 *pMatrix, bool createNetworkPlayer);
	virtual void		RemovePlayer(IVPed*);
	virtual void 		AssignDefaultTask(IVPed *a1, int a2, int a3, char a4);
};

class IVPedFactoryNY : public IVPedFactory
{

};

#endif // CIVPedFactory_h