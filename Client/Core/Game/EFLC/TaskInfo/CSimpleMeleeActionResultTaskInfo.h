#ifndef CSimpleMeleeActionResultTaskInfo_h
#define CSimpleMeleeActionResultTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleMeleeActionResultTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleMeleeActionResultTaskInfo();
	BYTE field_20;
};

#define IVSimpleMeleeActionResultTaskInfo__IVSimpleMeleeActionResultTaskInfo (*(ISimpleMeleeActionResultTaskInfo* (__thiscall *)(ISimpleMeleeActionResultTaskInfo*)) (g_pCore->GetBase() + 0xA1E570))

class CSimpleMeleeActionResultTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleMeleeActionResultTaskInfo();
	CSimpleMeleeActionResultTaskInfo(ISimpleMeleeActionResultTaskInfo* taskInfo);
	~CSimpleMeleeActionResultTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

_GAME_END

#endif // CSimpleMeleeActionResultTaskInfo_h
