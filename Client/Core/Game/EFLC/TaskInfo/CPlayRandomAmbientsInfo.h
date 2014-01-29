#ifndef CPlayRandomAmbientsInfo_h
#define CPlayRandomAmbientsInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IPlayRandomAmbientsInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IPlayRandomAmbientsInfo();
	BYTE state;
};

class CPlayRandomAmbientsInfo : public CTaskInfoWithCloneTask
{
public:
	CPlayRandomAmbientsInfo();
	CPlayRandomAmbientsInfo(IPlayRandomAmbientsInfo* taskInfo);

	~CPlayRandomAmbientsInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

_GAME_END

#endif // CPlayRandomAmbientsInfo_h
