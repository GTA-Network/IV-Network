#ifndef CIVComplexSlideIntoCoverInfo_h
#define CIVComplexSlideIntoCoverInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVComplexSlideIntoCoverInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVComplexSlideIntoCoverInfo();	
};

class CIVComplexSlideIntoCoverInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVComplexSlideIntoCoverInfo();
	~CIVComplexSlideIntoCoverInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexSlideIntoCoverInfo_h