#ifndef CIVSimpleMeleeActionResultTaskInfo_h
#define CIVSimpleMeleeActionResultTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleMeleeActionResultTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleMeleeActionResultTaskInfo();
	BYTE field_20;
};

#define IVSimpleMeleeActionResultTaskInfo__IVSimpleMeleeActionResultTaskInfo (*(IVSimpleMeleeActionResultTaskInfo* (__thiscall *)(IVSimpleMeleeActionResultTaskInfo*)) (g_pCore->GetBase() + 0xA1E570))

class CIVSimpleMeleeActionResultTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleMeleeActionResultTaskInfo();
	CIVSimpleMeleeActionResultTaskInfo(IVSimpleMeleeActionResultTaskInfo* taskInfo);
	~CIVSimpleMeleeActionResultTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

#endif // CIVSimpleMeleeActionResultTaskInfo_h