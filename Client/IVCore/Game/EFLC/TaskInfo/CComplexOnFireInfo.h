#ifndef CComplexOnFireInfo_h
#define CComplexOnFireInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IComplexOnFireInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IComplexOnFireInfo();
};

class CComplexOnFireInfo : public CTaskInfoWithCloneTask
{
public:
	CComplexOnFireInfo();
	~CComplexOnFireInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexOnFireInfo_h
