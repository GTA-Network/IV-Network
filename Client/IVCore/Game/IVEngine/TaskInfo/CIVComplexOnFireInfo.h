#ifndef CIVComplexOnFireInfo_h
#define CIVComplexOnFireInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVComplexOnFireInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVComplexOnFireInfo();
};

class CIVComplexOnFireInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVComplexOnFireInfo();
	~CIVComplexOnFireInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexOnFireInfo_h