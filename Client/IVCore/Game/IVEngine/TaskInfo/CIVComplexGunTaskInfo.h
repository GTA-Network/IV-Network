#ifndef CIVComplexGunTaskInfo_h
#define CIVComplexGunTaskInfo_h

#include "CIVStatusAndTargetTaskInfo.h"

class IVComplexGunTaskInfo : public IVStatusAndTargetTaskInfo
{
public:
	virtual ~IVComplexGunTaskInfo();
	DWORD	m_pTarget;				// 1C-20
	WORD	m_wTargetId;			// 20-22
	Vector4 m_vecTarget;			// 30-40
	DWORD	m_dwFlags;				// 40-44
	BYTE	m_bOverridingAnims;		// 44-45
	BYTE	m_bCoverLeftFlag;		// 45-46
	BYTE	m_bCoverOverFlag;		// 46-47
	BYTE	m_bUnk;					// 47-48
	DWORD	m_dwCoverHeight;		// 48-

};

class CIVComplexGunTaskInfo : public CIVStatusAndTargetTaskInfo
{
public:
	CIVComplexGunTaskInfo();
	~CIVComplexGunTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexGunTaskInfo_h