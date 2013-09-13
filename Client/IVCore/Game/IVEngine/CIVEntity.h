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
#include <Game/IVEngine/CIVPhysics.h>

class CIVWorld;
class IVEntity {
public:
	DWORD field_4;               // 04-08
	DWORD field_8;               // 08-0C
	DWORD field_C;               // 0C-10
	CVector3 m_vecPosition;      // 10-1C
	float m_fHeading;            // 1C-20
	Matrix34 * m_pMatrix;        // 20-24
	// Flag 1 - Has collision model (Set to enable col, unset to disable col)
	// Flag 8 - Fixed waiting for world collision (Don't load collision)
	// flags 0 - has col model, 3 - don't load cols, 5 - visible, 12 - draw last
	DWORD m_dwFlags1;            // 24-28 - Bits 0: has collision model, 1: use collision, 3: don't load collisions, 4: fixed, 5: is visible, 8: fixed waiting for collision, 12: draw last, 32: visible
	DWORD m_dwFlags2;            // 28-2C - Bits 2: lights, 21: on fire
	WORD field_2C;               // 2C-2E
	WORD m_wModelIndex;          // 2E-30
	IVEntity * m_pReferences;    // 30-34
	DWORD m_pLivery;             // 34-38 - Not sure about this, all i know is ((ent + 0x34) + 0xD8) = vehicle livery
	DWORD m_pPhysics;            // 38-3C
	DWORD field_3C;              // 3C-40
	BYTE field_40;               // 40-41
	BYTE field_41;               // 41-42
	WORD field_42;               // 42-44
	WORD field_44;               // 48-46
	BYTE field_46;               // 46-47
	BYTE field_47;               // 47-48
	DWORD m_dwInteriorHandle;    // 48-4C - Handle to current interior instance in the interior instance pool
	DWORD field_4C;              // 4C-50
	DWORD field_50;              // 50-54
	DWORD field_54;              // 54-58
	DWORD field_58;              // 58-5C
	WORD field_5C;               // 5C-5E
	WORD field_5E;               // 5E-60
	BYTE field_60;               // 60-61
	BYTE field_61;               // 61-62
	BYTE field_62;               // 62-63
	BYTE m_byteAlpha;            // 63-64
	DWORD field_64;              // 64-68
	DWORD field_68;              // 68-6C
	DWORD m_pNetworkObject;      // 6C-70
	DWORD m_pEntryInfoNode;      // 70-74

	virtual					~IVEntity();
	virtual Matrix34*       SetMatrix(Matrix34* pMatrix, int a2, int a3);
	virtual Matrix34*       SetCoordinates(Vector4* pCoordinates, bool b2, int a4); 
	virtual void            SetHeading(float fHeading); // not sure
	virtual void            Function4(); // 0x10
	virtual void            Function5(); // 0x14
	virtual void            Function6(); // 0x18
	virtual int				AddToInterior(); // 7
	virtual void            RemoveFromInterior();
	virtual void            Function9(); // return 0;
	virtual void            Function10(); // return 0;
	virtual void            Function11(); // return 0;
	virtual int				SetUnknownFlag0(unsigned char flag);
	virtual void            GetModelType(); // return 1;
	virtual int             SetModelIndex(int modelIndex);
	virtual int             SetModelByName(const char* modelName);
	virtual bool            Function16(); // checks something something with model and doing something with ped base
	virtual int             ReleaseModel(); // return mabye modelInfo
	virtual int             Function18(int a1); // something with livery
	virtual int             Function19(int a1); // something with physics
	virtual void            Function20(); // gets a position relative to model and entity position
	virtual void            Function21(); // gets a position relative to model and entity position
	virtual CVector3*       GetModelForwardMatrix(); // gets field 1c of model info
	virtual void            Function23(); // gets a position relative to model and entity position and return field 1c of model
	virtual void            Function24(); // get vec1 of model
	virtual void            Function25(); // get vec2 of model
	virtual void            Function26(); // something with model and entity position
	virtual void            Function27(); // something with model and entity position
	virtual void            ProcessInput(); // ProcessInput
	virtual char            Function29(int a1, int a2, int a3); // return 0;
	virtual void            Function30(Vector4*, float, bool); // return 0;
	virtual void            Function31(); // something with ped intelligence
	virtual void            Function32();
	virtual void            Function33(); // something with model
	virtual void            Function34();
	virtual void            Function35(); // something with livery and model
	virtual void            Function36(); // return 0;
	virtual void            Function37(); // nullsub
	virtual void            Function38();
	virtual Vector4*        GetCoordinates(Vector4* pCoordinates);
	virtual IVPhysics*      GetPhysics();
	virtual void            Function41(); // return 0;
	virtual int             GetModelIndex(); // something with model and physics
	virtual int             Add();
	virtual int             Remove();
	virtual Matrix34*       UpdatePhysicsMatrix(bool); // updates physics matrix
	virtual void            Function46(int a1, int a2, int a3, int a4); 
	virtual int             CreateNetworkObject(int a2, char a3, int a4, int a5, int a6); /* returns networkobject of entity */
	virtual void            Function48(); // return 10;
	virtual void            Function49(); // nullsub
	virtual void            Function50(); // nullsub
};


class CIVEntity {
private:
        IVEntity * m_pEntity;

public:
        CIVEntity();
        CIVEntity(IVEntity * pEntity);
        ~CIVEntity();

        void       SetEntity(IVEntity * pEntity);
        IVEntity * GetEntity();

        void       SetMatrix(const Matrix& matMatrix);
        void       GetMatrix(Matrix& matMatrix);
        void       SetPosition(const CVector3& vecPosition);
        void       GetPosition(CVector3& vecPosition);
        void       SetRoll(const CVector3& vecRoll);
        void       GetRoll(CVector3& vecRoll);
        void       SetDirection(const CVector3& vecDirection);
        void       GetDirection(CVector3& vecDirection);
        void       SetHeading(float fHeading);
        void       SetModelIndex(WORD wModelIndex);
        WORD       GetModelIndex();
        void       SetAlpha(BYTE byteAlpha);
        BYTE       GetAlpha();
        bool       IsTouchingEntity(CIVEntity * pTouchingEntity);
        void       AddToWorld();
        void       RemoveFromWorld();
};


#endif // CIVEntity_h