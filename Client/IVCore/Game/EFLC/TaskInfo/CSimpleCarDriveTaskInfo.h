#ifndef CSimpleCarDriveTaskInfo_h
#define CSimpleCarDriveTaskInfo_h

#include "CStatusTaskInfo.h"

_GAME_BEGIN

class ISimpleCarDriveTaskInfo : public IStatusTaskInfo
{
public:
	virtual ~ISimpleCarDriveTaskInfo();
	DWORD m_dwFlags;
};

#define IVSimpleCarDriveTaskInfo__IVSimpleCarDriveTaskInfo

class CSimpleCarDriveTaskInfo : public CStatusTaskInfo
{
public:
	CSimpleCarDriveTaskInfo();
	CSimpleCarDriveTaskInfo(ISimpleCarDriveTaskInfo* taskInfo);

	~CSimpleCarDriveTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

_GAME_END

#endif // CSimpleCarDriveTaskInfo_h
