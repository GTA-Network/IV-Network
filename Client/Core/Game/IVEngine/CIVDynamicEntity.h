//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CIVDynamicEntity.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVDynamicEntity_h
#define CIVDynamicEntity_h

#include <Common.h>
#include <Math\CMaths.h>
#include <IV\IVCommon.h>
#include "CIVEntity.h"

class IVDynamicEntityVFTable : public IVEntityVFTable {
public:
	DWORD mCC;
	DWORD mD0;
	DWORD mD4;
	DWORD mD8;
};

class IVDynamicEntity : public IVEntity {
	PAD(IVDynamicEntity, pad0, 0x4);
	DWORD m_pAnim;
	PAD(IVDynamicEntity, pad1, 0x90);
};

class CIVDynamicEntity : public CIVEntity {
public:
	CIVDynamicEntity();
	CIVDynamicEntity(IVDynamicEntity * pDynamicEntity);
	~CIVDynamicEntity();

	void				SetDynamicEntity(IVDynamicEntity * pDynamicEntity);
	IVDynamicEntity		* GetDynamicEntity();
};

#endif // CIVDynamicEntity_h