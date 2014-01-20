#ifndef CIVPlayRandomAmbientsInfo_h
#define CIVPlayRandomAmbientsInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVPlayRandomAmbientsInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVPlayRandomAmbientsInfo();
	BYTE state;
};

class CIVPlayRandomAmbientsInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVPlayRandomAmbientsInfo();
	CIVPlayRandomAmbientsInfo(IVPlayRandomAmbientsInfo* taskInfo);

	~CIVPlayRandomAmbientsInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

#endif // CIVPlayRandomAmbientsInfo_h