#ifndef CComplexCombatRetreatInfo_h
#define CComplexCombatRetreatInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IComplexCombatRetreatInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IComplexCombatRetreatInfo();
};

class CComplexCombatRetreatInfo : public CTaskInfoWithCloneTask
{
public:
	CComplexCombatRetreatInfo();
	~CComplexCombatRetreatInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexCombatRetreatInfo_h
