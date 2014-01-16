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

#ifndef CIVTrain_h
#define CIVTrain_h

#include <Common.h>
#include <CLogFile.h>
#include <Game/Entity/CVehicleEntity.h>

class IVTrain 
{ // size 44
public:
  BYTE f0[4];
  DWORD dword4;
  DWORD dword8;
  DWORD dwordC;
  DWORD dword10;
  BYTE f14[4];
  DWORD dword18;
  DWORD dword1C;
  WORD word20;
  WORD word22;
  WORD word24;
  BYTE byte26;
  BYTE Speed;
  BYTE byte28;
  BYTE byte29;
  BYTE byte2A;
  BYTE byte2B;
};

enum eTrainType 
{
	TYPE_MAIN = 0,
	TYPE_WAGON = 1
};

class CIVTrain : public CVehicleEntity
{
public:
	IVTrain				*	m_pTrain;
	CVehicleEntity		*	m_pVehicle;

	IVTrain				*	m_pWagon[8];
	CIVTrain			*	m_pWagonEntity[8];
	eTrainType				m_eTrainType;

						CIVTrain();
						~CIVTrain() { };

	void				CreateTrain();
	void				CreateWagons(BYTE iWagons);
	bool				IsTrain();
	void				SetTrainDirection(int iDirection);
	void				SetTrainCuriseSpeed(float fSpeed, unsigned int uiHandle = 1);

	CVehicleEntity		*GetVehicleEntity() { return m_pVehicle; }
	IVTrain				*GetTrain() { return m_pTrain; }
	BYTE				GetMaxWagonCount() { return ARRAY_LENGTH(m_pWagonEntity); }
	CIVTrain			*GetVehicleWagon(BYTE iWagon) { return m_pWagonEntity[iWagon] ? m_pWagonEntity[iWagon] : NULL; }
	IVTrain				*GetIVTrain();
};

#endif // CIVTrain_h