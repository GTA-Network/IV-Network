#ifndef CComplexGunTaskInfo_h
#define CComplexGunTaskInfo_h

#include "CStatusAndTargetTaskInfo.h"

_GAME_BEGIN

class IComplexGunTaskInfo : public IStatusAndTargetTaskInfo
{
public:
	virtual ~IComplexGunTaskInfo();
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

class CComplexGunTaskInfo : public CStatusAndTargetTaskInfo
{
public:
	CComplexGunTaskInfo();
	~CComplexGunTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexGunTaskInfo_h
