//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPhysical.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPhysical_h
#define CIVPhysical_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include "CIVDynamicEntity.h"
#include <IV/CIVScriptEnums.h>
#include "CIVWeaponInfo.h"

class IVPhysical : public IVDynamicEntity {
public:
        // 000-10C
        // 13C - In Water (BYTE)?
        PAD(IVPhysical, pad0, 0xD8);    // 10C-1E4
        // 0x1BC - IVEntity * m_pAttachedToEntity;
        // 0x140 - BYTE m_byteAttachedToEntity;
        // 0x150 - IVEntity * m_pCollidedEntity;
        // 0x1AA - BYTE m_byteHasDamageEntity;
        // 0x1C0 - CVector3 vecAttachedOffset;
        // 0x1D0 - Quaternion quatAttachedOffset;
        IVEntity * m_pLastDamageEntity; // 1E4-1E8
        PAD(IVPhysical, pad1, 0x4);     // 1E8-1EC
        eWeaponType m_lastDamageWeapon; // 1EC-1F0 // -1: None, eWeaponType: Weapon
        float m_fHealth;                // 1F0-1F4
        PAD(IVPhysical, pad3, 0x1C);    // 1F4-210

        virtual					~IVPhysical();
        virtual bool			Function55(); 
        virtual void			Function56(); // seems get flag
        virtual void			Function57(); // something with bound or so
        virtual void			Function58(); // nullsub
        virtual CVector3*		GetVelocity(CVector3*);
        virtual void			SetHealth(float);
        virtual void			SetHealth(float, int);
        virtual void			AddHealth(float);
        virtual float			GetHealth();
		virtual void			Function64(); // something with network object
		virtual void			Function65(); // return 1;
		virtual void			Function66(); // return 1;
        virtual CVector3*		Function67(CVector3*); // sets something
		virtual void			Function68(); // unregister reference
		virtual void			Function69(); // physics calculation
		virtual void			Function70();
		virtual void			Function71();
};

class CIVPhysical : public CIVDynamicEntity {
public:
        CIVPhysical();
        CIVPhysical(IVPhysical * pPhysical);
        ~CIVPhysical();

        void         SetPhysical(IVPhysical * pPhysical);
        IVPhysical * GetPhysical();

        void         SetMoveSpeed(const CVector3& vecMoveSpeed);
        void         GetMoveSpeed(CVector3& vecMoveSpeed);
        void         SetTurnSpeed(const CVector3& vecTurnSpeed);
        void         GetTurnSpeed(CVector3& vecTurnSpeed);
        void         SetLastDamageEntity(IVEntity * pLastDamageEntity);
        IVEntity *   GetLastDamageEntity();
        void         SetHealth(float fHealth);
        float        GetHealth();
};

#endif // CIVPhysical_h