/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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