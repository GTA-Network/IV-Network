//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CIVEntity.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVEntity_h
#define CIVEntity_h

#include <Common.h>
#include <Math\CMaths.h>
#include <IV\IVCommon.h>

class CIVWorld;
class IVEntityVFTable {
public:
	DWORD ScalarDeletingDestructor;
	DWORD SetMatrix;
	DWORD SetPosition;
	DWORD SetHeading;
	DWORD m10;
	DWORD m14;
	DWORD m18;
	DWORD AddToInterior;
	DWORD RemoveFromInterior;
	DWORD m24;
	DWORD m28;
	DWORD m2C;
	DWORD m30;
	DWORD m34;
	DWORD SetModelIndex;
	DWORD SetModelByName;
	DWORD m40;
	DWORD m44;
	DWORD m48;
	DWORD m4C;
	DWORD m50;
	DWORD m54;
	DWORD m58;
	DWORD m5C;
	DWORD m60;
	DWORD m64;
	DWORD m68;
	DWORD m6C;
	DWORD m70;
	DWORD m74;
	DWORD m78;
	DWORD m7C;
	DWORD m80;
	DWORD m84;
	DWORD m88;
	DWORD m8C;
	DWORD m90;
	DWORD m94;
	DWORD m98;
	DWORD GetPosition;
	DWORD mA0;
	DWORD mA4;
	DWORD mA8;
	DWORD Add;
	DWORD Remove;
	DWORD mB4;
	DWORD mB8;
	DWORD mBC;
	DWORD mC0;
	DWORD mC4;
	DWORD mC8;
};

class IVEntity {
public:
	IVEntityVFTable * m_VFTable;
	PAD(IVEntity, pad0, 0xC);
	CVector3 m_vecPosition;
	float m_fHeading;
	Matrix34 * m_pMatrix;
	DWORD m_dwFlags1;
	DWORD m_dwFlags2;
	WORD m_w2C;
	WORD m_wModelIndex;
	IVEntity * m_pReferences;
	DWORD m_pLivery;
	DWORD m_pPhysics;
	PAD(IVEntity, pad1, 0xC);
	DWORD m_hInterior;
	PAD(IVEntity, pad2, 0x17);
	BYTE m_byteAlpha;
	PAD(IVEntity, pad3, 0x8);
	DWORD m_dwNetObject;
	PAD(IVEntity, pad4, 0x4);
};

class CIVEntity {
private:
	IVEntity			* m_pEntity;

public:
	CIVEntity();
	CIVEntity(IVEntity * pEntity);
	~CIVEntity();

	void				SetEntity(IVEntity * pEntity) { m_pEntity = pEntity; }
	IVEntity			* GetEntity() { return m_pEntity; }

	void				SetMatrix(Matrix matMatrix);
	void				GetMatrix(Matrix * matMatrix);

	void				SetPosition(CVector3 vecPosition);
	void				GetPosition(CVector3 * vecPosition);

	void				SetRoll(CVector3 vecRoll);
	void				GetRoll(CVector3 * vecRoll);

	void				SetDirection(CVector3 vecDirection);
	void				GetDirection(CVector3 * vecDirection);

	void				SetModelIndex(WORD wModelIndex);
	WORD				GetModelIndex();

	void				SetAlpha(BYTE byteAlpha);
	BYTE				GetAlpha();

	bool				IsTouchingEntity(CIVEntity * pTouchingEntity);

	void				AddToWorld();
	void				RemoveFromWorld();
};

#endif // CIVEntity_h