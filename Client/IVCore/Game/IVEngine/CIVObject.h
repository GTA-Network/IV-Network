//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVObject.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVObject_h
#define CIVObject_h

#include <Common.h>
#include "CIVPhysical.h"
#include "CIVWeapon.h"

class IVObject : public IVPhysical {
public:
	                           // 000-210
	PAD(IVObject, pad0, 0x4C); // 210-25C
	IVWeapon * m_pWeapon;      // 25C-260
	PAD(IVObject, pad1, 0xC0); // 210-320

	virtual ~IVObject();
};

class CIVObject : public CIVPhysical {
private:
	IVObject  * m_pObject;
	CIVWeapon * m_pWeapon;

public:
	CIVObject(IVObject * pObject);
	~CIVObject();

	void        SetObject(IVObject * pObject) { m_pObject = pObject; }
	IVObject  * GetObject() { return m_pObject; }
	CIVWeapon * GetWeapon();
};

#endif // CIVObject_h