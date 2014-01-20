#ifndef CIVDeadInfo_h
#define CIVDeadInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVDeadInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVDeadInfo();
};

class CIVDeadInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVDeadInfo();
	~CIVDeadInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVDeadInfo_h