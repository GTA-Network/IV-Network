//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVTrain.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVTrain_h
#define CIVTrain_h

#include <Common.h>
#include <CLogFile.h>
#include <Game/Entity/CVehicleEntity.h>

class IVTrain { // size 44
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

enum eTrainType {
	TYPE_MAIN = 0,
	TYPE_WAGON = 1
};

class CIVTrain : public CVehicleEntity {
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