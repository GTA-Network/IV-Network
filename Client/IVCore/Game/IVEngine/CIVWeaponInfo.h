//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVWeaponInfo.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVWeaponInfo_h
#define CIVWeaponInfo_h

#include <IV/IVData.h>

enum eWeaponType
{
	WEAPON_TYPE_UNARMED,
	WEAPON_TYPE_BASEBALLBAT,
	WEAPON_TYPE_POOLCUE,
	WEAPON_TYPE_KNIFE,
	WEAPON_TYPE_GRENADE,
	WEAPON_TYPE_MOLOTOV,
	WEAPON_TYPE_ROCKET,
	WEAPON_TYPE_PISTOL,
	WEAPON_TYPE_UNUSED0,
	WEAPON_TYPE_DEAGLE,
	WEAPON_TYPE_SHOTGUN,
	WEAPON_TYPE_BARETTA,
	WEAPON_TYPE_MICRO_UZI,
	WEAPON_TYPE_MP5,
	WEAPON_TYPE_AK47,
	WEAPON_TYPE_M4,
	WEAPON_TYPE_SNIPERRIFLE,
	WEAPON_TYPE_M40A1,
	WEAPON_TYPE_RLAUNCHER,
	WEAPON_TYPE_FTHROWER,
	WEAPON_TYPE_MINIGUN,
	WEAPON_TYPE_EPISODIC_1,
	WEAPON_TYPE_EPISODIC_2,
	WEAPON_TYPE_EPISODIC_3,
	WEAPON_TYPE_EPISODIC_4,
	WEAPON_TYPE_EPISODIC_5,
	WEAPON_TYPE_EPISODIC_6,
	WEAPON_TYPE_EPISODIC_7,
	WEAPON_TYPE_EPISODIC_8,
	WEAPON_TYPE_EPISODIC_9,
	WEAPON_TYPE_EPISODIC_10,
	WEAPON_TYPE_EPISODIC_11,
	WEAPON_TYPE_EPISODIC_12,
	WEAPON_TYPE_EPISODIC_13,
	WEAPON_TYPE_EPISODIC_14,
	WEAPON_TYPE_EPISODIC_15,
	WEAPON_TYPE_EPISODIC_16,
	WEAPON_TYPE_EPISODIC_17,
	WEAPON_TYPE_EPISODIC_18,
	WEAPON_TYPE_EPISODIC_19,
	WEAPON_TYPE_EPISODIC_20,
	WEAPON_TYPE_EPISODIC_21,
	WEAPON_TYPE_EPISODIC_22,
	WEAPON_TYPE_EPISODIC_23,
	WEAPON_TYPE_EPISODIC_24,
	WEAPON_TYPE_CAMERA,
	WEAPON_TYPE_OBJECT,
	WEAPON_TYPE_LAST_WEAPONTYPE,
	WEAPON_TYPE_ARMOUR,
	WEAPON_TYPE_RAMMEDBYCAR,
	WEAPON_TYPE_RUNOVERBYCAR,
	WEAPON_TYPE_EXPLOSION,
	WEAPON_TYPE_UZI_DRIVEBY,
	WEAPON_TYPE_DROWNING,
	WEAPON_TYPE_FALL,
	WEAPON_TYPE_UNIDENTIFIED,
	WEAPON_TYPE_ANYMELEE,
	WEAPON_TYPE_ANYWEAPON,
	WEAPON_TYPE_MAX
};

enum eWeaponSlot
{
	WEAPON_SLOT_UNARMED,
	WEAPON_SLOT_MELEE,
	WEAPON_SLOT_HANDGUN,
	WEAPON_SLOT_SHOTGUN,
	WEAPON_SLOT_SMG,
	WEAPON_SLOT_RIFLE,
	WEAPON_SLOT_SNIPER,
	WEAPON_SLOT_HEAVY,
	WEAPON_SLOT_THROWN,
	WEAPON_SLOT_SPECIAL,
	WEAPON_SLOT_PARACHUTE,
	WEAPON_SLOT_MAX
};

enum eWeaponFireType
{
	WEAPON_FIRE_TYPE_MELEE,
	WEAPON_FIRE_TYPE_INSTANT_HIT,
	WEAPON_FIRE_TYPE_DELAYED_HIT,
	WEAPON_FIRE_TYPE_PROJECTILE,
	WEAPON_FIRE_TYPE_AREA_EFFECT,
	WEAPON_FIRE_TYPE_CAMERA,
	WEAPON_FIRE_TYPE_USE,
	WEAPON_FIRE_TYPE_UNKNOWN,
	WEAPON_FIRE_TYPE_MAX
};

enum eWeaponProjectileType
{
	WEAPON_PROJECTILE_TYPE_NONE,
	WEAPON_PROJECTILE_TYPE_FUSE,
	WEAPON_PROJECTILE_TYPE_IMPACT,
	WEAPON_PROJECTILE_TYPE_ROCKET,
	WEAPON_PROJECTILE_TYPE_STICKY,
	WEAPON_PROJECTILE_TYPE_UNKNOWN,
	WEAPON_PROJECTILE_TYPE_MAX
};

enum eWeaponDamageType
{
	WEAPON_DAMAGE_TYPE_NONE,
	WEAPON_DAMAGE_TYPE_MELEE,
	WEAPON_DAMAGE_TYPE_BULLET,
	WEAPON_DAMAGE_TYPE_EXPLOSIVE,
	WEAPON_DAMAGE_TYPE_FIRE,
	WEAPON_DAMAGE_TYPE_COLLISION,
	WEAPON_DAMAGE_TYPE_FALL,
	WEAPON_DAMAGE_TYPE_DROWN,
	WEAPON_DAMAGE_TYPE_UNKNOWN,
	WEAPON_DAMAGE_TYPE_MAX
};

enum eWeaponGroup
{
	WEAPON_GROUP_PUNCH_KICK,
	WEAPON_GROUP_MELEE_WOOD,
	WEAPON_GROUP_MELEE_METAL,
	WEAPON_GROUP_MELEE_SHARP,
	WEAPON_GROUP_MELEE_GENERIC,
	WEAPON_GROUP_PISTOL_SMALL,
	WEAPON_GROUP_PISTOL_LARGE,
	WEAPON_GROUP_PISTOL_SILENCED,
	WEAPON_GROUP_SMG,
	WEAPON_GROUP_SHOTGUN,
	WEAPON_GROUP_RIFLE_ASSAULT,
	WEAPON_GROUP_RIFLE_SNIPER,
	WEAPON_GROUP_ROCKET,
	WEAPON_GROUP_GRENADE,
	WEAPON_GROUP_MOLOTOV,
	WEAPON_GROUP_FIRE,
	WEAPON_GROUP_EXPLOSION,
	WEAPON_GROUP_UNKNOWN,
	WEAPON_GROUP_MAX
};

enum eWeaponFlag
{
	WEAPON_FLAG_CAN_AIM = 0x00000001,
	WEAPON_FLAG_CAN_AIM_WITH_ARM = 0x00000002,
	WEAPON_FLAG_CAN_FREE_AIM = 0x00000004,
	WEAPON_FLAG_FIRST_PERSON = 0x00000008,
	WEAPON_FLAG_KEEP_CAMERA_BEHIND = 0x00000010,
	WEAPON_FLAG_GUN = 0x00000020,
	WEAPON_FLAG_THROWN = 0x00000040,
	WEAPON_FLAG_HEAVY = 0x00000080,
	WEAPON_FLAG_SILENCED = 0x00000100,
	WEAPON_FLAG_MELEE_CLUB = 0x00000200,
	WEAPON_FLAG_MELEE_BLADE = 0x00000400,
	WEAPON_FLAG_ARMOUR_PENETRATING = 0x00000800,
	WEAPON_FLAG_2HANDED = 0x00001000,
	WEAPON_FLAG_TREAT_AS_2HANDED_IN_COVER = 0x00002000,
	WEAPON_FLAG_ANIM_RELOAD = 0x00004000,
	WEAPON_FLAG_ANIM_CROUCH_FIRE = 0x00008000,
	WEAPON_FLAG_CREATE_VISIBLE_ORDNANCE = 0x00010000,
	WEAPON_FLAG_EXPLOSION_BASED_ON_IMPACT = 0x00020000,
	WEAPON_FLAG_ADD_SMOKE_ON_EXPLOSION = 0x00040000,
	WEAPON_FLAG_INSTANT_KILL_IN_MP = 0x00080000,
	WEAPON_FLAG_HIGHER_BREAK_FORCE = 0x00100000,
	WEAPON_FLAG_CAN_BE_USED_AS_DRIVEBY = 0x00200000,
	WEAPON_FLAG_HEAVY_WEAPON_USES_RIFLE_ANIMS = 0x00400000,
	WEAPON_FLAG_MISSION_CAN_FORCE_DRIVEBY_USE = 0x00800000,
	WEAPON_FLAG_DONT_RUMBLE_WHEN_DOING_DRIVE_BY = 0x01000000,
	WEAPON_FLAG_MAX
};

enum eExplosionType
{
	EXPLOSION_TYPE_GRENADE,
	EXPLOSION_TYPE_MOLOTOV,
	EXPLOSION_TYPE_ROCKET,
	EXPLOSION_TYPE_HI_OCTANE,
	EXPLOSION_TYPE_CAR,
	EXPLOSION_TYPE_PLANE,
	EXPLOSION_TYPE_PETROL_PUMP,
	EXPLOSION_TYPE_BIKE,
	EXPLOSION_TYPE_DIR_STEAM,
	EXPLOSION_TYPE_DIR_FLAME,
	EXPLOSION_TYPE_DIR_WATER_HYDRANT,
	EXPLOSION_TYPE_DIR_GAS_CANISTER,
	EXPLOSION_TYPE_BOAT,
	EXPLOSION_TYPE_SHIP_DESTROY,
	EXPLOSION_TYPE_TRUCK,
	EXPLOSION_TYPE_EPISODIC_1,
	EXPLOSION_TYPE_EPISODIC_2,
	EXPLOSION_TYPE_EPISODIC_3,
	EXPLOSION_TYPE_EPISODIC_4,
	EXPLOSION_TYPE_EPISODIC_5,
	EXPLOSION_TYPE_EPISODIC_6,
	EXPLOSION_TYPE_EPISODIC_7,
	EXPLOSION_TYPE_EPISODIC_8,
	EXPLOSION_TYPE_EPISODIC_9,
	EXPLOSION_TYPE_EPISODIC_10,
	EXPLOSION_TYPE_UNKNOWN,
	EXPLOSION_TYPE_MAX
};

class IVWeaponInfo
{
public:
	eWeaponType m_weaponType;                                    // 000-004
	eWeaponSlot m_slot;                                          // 004-008
	eWeaponFireType m_fireType;                                  // 008-00C
	eWeaponDamageType m_damageType;                              // 00C-010
	eWeaponGroup m_group;                                        // 010-014
	float m_fTargetRange;                                        // 014-018
	float m_fWeaponRange;                                        // 018-01C (dwProjectilePhysicsForce)
	DWORD m_dwStatType;                                          // 01C-020
	DWORD m_dwFlags;                                             // 020-024 (See eWeaponFlag)
	DWORD m_dwModelHash;                                         // 024-028
	DWORD m_dwAnimGroup;                                         // 028-02C
	float m_fFireRate;                                           // 02C-030
	float m_fBlindFireRate;                                      // 030-034
	float m_fAimingAccuracy;                                     // 034-038
	float m_fAimingAccuracyFPS;                                  // 038-03C
	PAD(IVWeaponInfo, pad1, 0x4);                                // 03C-040
	CVector3 m_vecAimingOffset;                                  // 040-04C
	PAD(IVWeaponInfo, pad2, 0x4);                                // 04C-050
	CVector3 m_vecAimingCrouchedOffset;                          // 050-05C
	PAD(IVWeaponInfo, pad3, 0x4);                                // 05C-060
	float m_fAimingPitch;                                        // 060-064
	float m_fAimingReticuleStanding;                             // 064-068
	float m_fAimingReticuleDucked;                               // 068-06C
	float m_fAimingReticuleScale;                                // 06C-070
	DWORD m_dwRumbleDuration;                                    // 070-074
	float m_fRumbleIntensity;                                    // 074-078
	DWORD m_dwPickupRegenTime;                                   // 078-07C
	PAD(IVWeaponInfo, pad4, 0x4);                                // 07C-080
	WORD m_wPickupAmmoOnStreet;                                  // 080-082
	WORD m_wDamageBase;                                          // 082-084
	WORD m_wDamageFPS;                                           // 084-086
	WORD m_wClipSize;                                            // 086-088
	WORD m_wAmmoMax;                                             // 088-08A
	PAD(IVWeaponInfo, pad5, 0x2);                                // 08A-08C
	DWORD m_dwTimeBetweenShots;                                  // 08C-090
	float m_fPhysicsForce;                                       // 090-094
	DWORD m_dwReloadTime;                                        // 094-098
	DWORD m_dwFastReloadTime;                                    // 098-09C
	DWORD m_dwCrouchReloadTime;                                  // 09C-0A0
	DWORD m_dwProjectileType;                                    // 0A0-0A4
	DWORD m_dwProjectileFuseTime;                                // 0A4-0A8
	DWORD m_dwProjectileTypeToCreate;                            // 0A8-0AC
	eExplosionType m_explosionType;                              // 0AC-0B0
	CVector3 m_vecProjectileOffset;                              // 0B0-0BC
	PAD(IVWeaponInfo, pad6, 0x4);                                // 0BC-0C0
	CVector3 m_vecProjectileRotOffset;                           // 0C0-0CC
	PAD(IVWeaponInfo, pad7, 0x4);                                // 0CC-0D0
	float m_fProjectilePhysicsExplodeImpactThreshold;            // 0D0-0D4
	float m_fProjectilePhysicsExplodeImpactWithVehicleThreshold; // 0D4-0D8
	float m_fProjectilePhysicsVehicleVelocity;                   // 0D8-0DC
	DWORD m_dwAnimMeleeGroup1;                                   // 0DC-0E0
	DWORD m_dwAnimMeleeGroup2;                                   // 0E0-0E4
	DWORD m_dwMuzzleFxHash;                                      // 0E4-0E8
	DWORD m_dwShellFxHash;                                       // 0E8-0EC
	DWORD m_dwTrailFxHash;                                       // 0EC-0F0
	float m_fDamageNetworkPlayerMod;                             // 0F0-0F4
	float m_fDamageNetworkPedMod;                                // 0F4-0F8
	float m_fAimingAccuracyTime;                                 // 0F8-0FC
	DWORD m_dwAimingPellets;                                     // 0FC-100
	PAD(IVWeaponInfo, pad8, 0x10);                               // 100-110
};

class CIVWeaponInfo
{
private:
	eWeaponType    m_weaponType;
	IVWeaponInfo * m_pWeaponInfo;

public:
	CIVWeaponInfo();
	CIVWeaponInfo(eWeaponType weaponType, IVWeaponInfo * pWeaponInfo);
	~CIVWeaponInfo();

	void           SetType(eWeaponType weaponType) { m_weaponType = weaponType; }
	eWeaponType    GetType() { return m_weaponType; }
	void           SetWeaponInfo(IVWeaponInfo * pWeaponInfo) { m_pWeaponInfo = pWeaponInfo; }
	IVWeaponInfo * GetWeaponInfo() { return m_pWeaponInfo; }
};

#endif // CIVWeaponInfo_h