#ifndef CComplexSlideIntoCoverInfo_h
#define CComplexSlideIntoCoverInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IComplexSlideIntoCoverInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IComplexSlideIntoCoverInfo();	
};

class CComplexSlideIntoCoverInfo : public CTaskInfoWithCloneTask
{
public:
	CComplexSlideIntoCoverInfo();
	~CComplexSlideIntoCoverInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexSlideIntoCoverInfo_h
