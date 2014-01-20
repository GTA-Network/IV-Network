#ifndef CIVSimpleCarDriveTaskInfo_h
#define CIVSimpleCarDriveTaskInfo_h

#include "CIVStatusTaskInfo.h"

class IVSimpleCarDriveTaskInfo : public IVStatusTaskInfo
{
public:
	virtual ~IVSimpleCarDriveTaskInfo();
	DWORD m_dwFlags;
};

#define IVSimpleCarDriveTaskInfo__IVSimpleCarDriveTaskInfo

class CIVSimpleCarDriveTaskInfo : public CIVStatusTaskInfo
{
public:
	CIVSimpleCarDriveTaskInfo();
	CIVSimpleCarDriveTaskInfo(IVSimpleCarDriveTaskInfo* taskInfo);

	~CIVSimpleCarDriveTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

#endif // CIVSimpleCarDriveTaskInfo_h