#ifndef CIVComplexCombatRetreatInfo_h
#define CIVComplexCombatRetreatInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVComplexCombatRetreatInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVComplexCombatRetreatInfo();
};

class CIVComplexCombatRetreatInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVComplexCombatRetreatInfo();
	~CIVComplexCombatRetreatInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexCombatRetreatInfo_h