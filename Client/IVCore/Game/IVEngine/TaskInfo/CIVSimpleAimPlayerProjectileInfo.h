#ifndef CIVSimpleAimPlayerProjectileInfo_h
#define CIVSimpleAimPlayerProjectileInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleAimPlayerProjectileInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleAimPlayerProjectileInfo();
};

class CIVSimpleAimPlayerProjectileInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleAimPlayerProjectileInfo();
	~CIVSimpleAimPlayerProjectileInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSimpleAimPlayerProjectileInfo_h