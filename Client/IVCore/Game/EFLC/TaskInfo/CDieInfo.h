#ifndef CDieInfo_h
#define CDieInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IDieInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IDieInfo();
};

class CDieInfo : public CTaskInfoWithCloneTask
{
public:
	CDieInfo();
	~CDieInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CDieInfo_h
