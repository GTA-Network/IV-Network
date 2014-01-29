#ifndef CComplexNewUseCoverInfo_h
#define CComplexNewUseCoverInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IComplexNewUseCoverInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IComplexNewUseCoverInfo();
};

class CComplexNewUseCoverInfo : public CTaskInfoWithCloneTask
{
public:
	CComplexNewUseCoverInfo();
	~CComplexNewUseCoverInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexNewUseCoverInfo_h
