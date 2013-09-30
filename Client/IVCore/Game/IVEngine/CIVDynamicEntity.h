//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include "CIVEntity.h"

class IVDynamicEntity : public IVEntity {
public:
	DWORD m_pPtrNodeDouble;                   // PtrNodeDouble
	DWORD m_pAnim;                    // 078-07C
	// 0x80 - 0xCC = CPortalTracker m_portalTracker; (+0x30 = CDynamicEntity * m_pDynamicEntity)
	PAD(IVDynamicEntity, pad1, 0x90); // 07C-10C

	virtual ~IVDynamicEntity();
	virtual void            Function51(); // idk
	virtual void            Function52(); // return 0;
	virtual void            Function53(); // return 0;
	virtual void            Function54(); // CPortalTracker
};

class CIVDynamicEntity : public CIVEntity {
public:
	CIVDynamicEntity();
	CIVDynamicEntity(IVDynamicEntity * pDynamicEntity);
	~CIVDynamicEntity();

	void	 SetDynamicEntity(IVDynamicEntity * pDynamicEntity);
	IVDynamicEntity	 * GetDynamicEntity();
};

#endif // CIVDynamicEntity_h