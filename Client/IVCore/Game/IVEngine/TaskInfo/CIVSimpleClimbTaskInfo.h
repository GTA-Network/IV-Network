#ifndef CIVSimpleClimbTaskInfo_h
#define CIVSimpleClimbTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

#pragma pack(push, 1)
class IVSimpleClimbTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleClimbTaskInfo();
	BYTE m_bClimbType;		
	BYTE m_bShimmyingLeft;
	BYTE m_bShimmyingRight;
	BYTE m_bPullingUp;
	DWORD unk; //padding by the compiler?
	CVector3 m_vecGrabPosition;
};
#pragma pack(pop)

#define CSimpleClimbTaskInfo__CSimpleClimbTaskInfo (*(IVSimpleClimbTaskInfo* (__thiscall *)(IVSimpleClimbTaskInfo*, char bClimbType, char bShimmyingLeft, char bShimmyingRight, char bPullingUp, CVector3* a6)) (g_pCore->GetBase() + 0xA1EAA0))

class CIVSimpleClimbTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleClimbTaskInfo();

	CIVSimpleClimbTaskInfo(IVSimpleClimbTaskInfo * taskInfo);
	
	~CIVSimpleClimbTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

#endif // CIVSimpleClimbTaskInfo_h