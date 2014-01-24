#ifndef CDeadInfo_h
#define CDeadInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IDeadInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IDeadInfo();
};

class CDeadInfo : public CTaskInfoWithCloneTask
{
public:
	CDeadInfo();
	~CDeadInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CDeadInfo_h
