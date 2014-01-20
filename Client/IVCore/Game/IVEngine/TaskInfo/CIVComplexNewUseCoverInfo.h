#ifndef CIVComplexNewUseCoverInfo_h
#define CIVComplexNewUseCoverInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVComplexNewUseCoverInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVComplexNewUseCoverInfo();
};

class CIVComplexNewUseCoverInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVComplexNewUseCoverInfo();
	~CIVComplexNewUseCoverInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexNewUseCoverInfo_h