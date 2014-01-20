#include <RakNet/Bitstream.h>
#include <Math/CMaths.h>

#ifndef CIVTaskInfo_h
#define CIVTaskInfo_h

#define CPool__Allocate_0 (*(void* (__thiscall *)(void*)) (g_pCore->GetBase() + 0x4AAF70))
#define g_pTaskInfoPool *(void**) (g_pCore->GetBase() + 0x15C33C4)


#define CTaskInfo__CTaskInfo (*(IVTaskInfo* (__thiscall *)(IVTaskInfo*)) (g_pCore->GetBase() + 0xA19030))
#define CComplexJumpTaskInfo__CComplexJumpTaskInfo (*(IVComplexJumpTaskInfo* (__thiscall *)(IVComplexJumpTaskInfo*, bool bHasPedJumped, bool bJumpOnSpot, bool bForceInAir)) (g_pCore->GetBase() + 0xA1E600))
#define CIVMeleeTaskInfo__CIVMeleeTaskInfo (*(IVMeleeTaskInfo* (__thiscall *)(IVMeleeTaskInfo*)) (g_pCore->GetBase() + 0xA19DA0))

class IVTaskInfo
{
public:
	DWORD 		m_dwTaskId;
	DWORD		unknownFlag0;
	IVTaskInfo 	*subTaskInfo;
	DWORD		field10;
	
	virtual ~IVTaskInfo();
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

class CIVTaskInfo
{
protected:
	IVTaskInfo* m_pTaskInfo = nullptr;

public:
	CIVTaskInfo();
	CIVTaskInfo(IVTaskInfo * pTaskInfo);
	~CIVTaskInfo();

	IVTaskInfo * GetTaskInfo() { return m_pTaskInfo; }
	
	virtual bool Serialize(RakNet::BitStream * pBitStream);
	virtual bool Deserialize(RakNet::BitStream * pBitStream);
};

#endif // CIVTaskInfo_h