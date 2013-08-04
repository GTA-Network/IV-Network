//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CIVModelInfo.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVModelInfo_h
#define CIVModelInfo_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>

#define	ARRAY_ModelInfos			0x15F73B0
#define	NUM_ModelInfos				65535

class IVBaseModelInfoVFTable
{
public:
	DWORD ScalarDeletingDestructor;
	DWORD m4;
	DWORD m8;
	DWORD GetType;
	DWORD m10;
	DWORD m14;
	DWORD m18;
	DWORD m1C;
	DWORD m20;
	DWORD m24;
	DWORD m28;
	DWORD m2C;
	DWORD m30;
	DWORD m34;
	DWORD m38;
};

class IVBaseModelInfo
{
public:
	IVBaseModelInfoVFTable * m_VFTable;
	PAD(IVBaseModelInfo, pad0, 0x38);
	DWORD dwHash;
	PAD(IVBaseModelInfo, pad1, 0x4);
	DWORD dwRefCount;
	PAD(IVBaseModelInfo, pad2, 0xE);
	WORD wAnimIndex;
	PAD(IVBaseModelInfo, pad3, 0x14);
	DWORD dwVehicleType;
	PAD(IVBaseModelInfo, pad4, 0x52);
	BYTE byteTextureVariationCount;
};

class CIVModelInfo
{

private:

	int			m_iModelIndex;
	DWORD		m_dwReferenceCount;

public:

	CIVModelInfo( );
	CIVModelInfo( int iModelIndex );
	~CIVModelInfo( );

	IVBaseModelInfo		* GetModelInfo( );

	void				SetIndex( int iModelIndex ) { m_iModelIndex = iModelIndex; }
	int					GetIndex( ) { return m_iModelIndex; }

	BYTE				GetType( );

	bool				IsBase( ) { return (GetType() == MODEL_TYPE_BASE); }
	bool				IsInstance() { return (GetType() == MODEL_TYPE_BASE); }
	bool				IsMlo() { return (GetType() == MODEL_TYPE_MLO); }
	bool				IsTime() { return (GetType() == MODEL_TYPE_TIME); }
	bool				IsWeapon() { return (GetType() == MODEL_TYPE_WEAPON); }
	bool				IsVehicle() { return (GetType() == MODEL_TYPE_VEHICLE); }
	bool				IsPed() { return (GetType() == MODEL_TYPE_PED); }
	bool				IsValid( ) { return (GetModelInfo() != NULL); }
	
	void				Load( bool bWaitForLoad = true );
	bool				IsLoaded( );

	DWORD				GetHash();
	DWORD				GetReferenceCount();
	WORD				GetAnimIndex();

	void				AddReference( bool bWaitForLoad );
	void				RemoveReference( );

};

#endif // CIVModelInfo_h