#ifndef CTaskInfo_h
#define CTaskInfo_h

#include <Common.h>
#include "../../GameCommon.h"
#include <RakNet/Bitstream.h>

_GAME_BEGIN

#define CPool__Allocate_0 (*(void* (__thiscall *)(void*)) (g_pCore->GetBase() + 0x4AAF70))
#define g_pTaskInfoPool *(void**) (g_pCore->GetBase() + 0x15C33C4)


#define CTaskInfo__CTaskInfo (*(ITaskInfo* (__thiscall *)(ITaskInfo*)) (g_pCore->GetBase() + 0xA19030))
#define CComplexJumpTaskInfo__CComplexJumpTaskInfo (*(IComplexJumpTaskInfo* (__thiscall *)(IComplexJumpTaskInfo*, bool bHasPedJumped, bool bJumpOnSpot, bool bForceInAir)) (g_pCore->GetBase() + 0xA1E600))
#define CMeleeTaskInfo__CMeleeTaskInfo (*(IMeleeTaskInfo* (__thiscall *)(IMeleeTaskInfo*)) (g_pCore->GetBase() + 0xA19DA0))

class ITaskInfo
{
public:
	DWORD 		m_dwTaskId;
	DWORD		unknownFlag0;
	ITaskInfo 	*subTaskInfo;
	DWORD		field10;
	
	virtual ~ITaskInfo();
	virtual int GetType(); // returns the id
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void DebugText(); // does nothing because debug log function is a nullsub
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
};

class CTaskInfo
{
protected:
	ITaskInfo* m_pTaskInfo = nullptr;

public:
	CTaskInfo();
	CTaskInfo(ITaskInfo * pTaskInfo);
	~CTaskInfo();

	ITaskInfo * GetTaskInfo() { return m_pTaskInfo; }
	
	virtual bool Serialize(RakNet::BitStream * pBitStream);
	virtual bool Deserialize(RakNet::BitStream * pBitStream);
};

_GAME_END

#endif // CTaskInfo_h
