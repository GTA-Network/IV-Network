#ifndef CSimpleClimbTaskInfo_h
#define CSimpleClimbTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

#pragma pack(push, 1)
class ISimpleClimbTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleClimbTaskInfo();
	BYTE m_bClimbType;		
	BYTE m_bShimmyingLeft;
	BYTE m_bShimmyingRight;
	BYTE m_bPullingUp;
	DWORD unk; //padding by the compiler?
	CVector3 m_vecGrabPosition;
};
#pragma pack(pop)

#define CSimpleClimbTaskInfo__CSimpleClimbTaskInfo (*(ISimpleClimbTaskInfo* (__thiscall *)(ISimpleClimbTaskInfo*, char bClimbType, char bShimmyingLeft, char bShimmyingRight, char bPullingUp, CVector3* a6)) (g_pCore->GetBase() + 0xA1EAA0))

class CSimpleClimbTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleClimbTaskInfo();

	CSimpleClimbTaskInfo(ISimpleClimbTaskInfo * taskInfo);
	
	~CSimpleClimbTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

_GAME_END

#endif // CSimpleClimbTaskInfo_h
