#include "CSimpleMeleeActionResultTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

_GAME_BEGIN

CSimpleMeleeActionResultTaskInfo::CSimpleMeleeActionResultTaskInfo() : CTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (ISimpleMeleeActionResultTaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	IVSimpleMeleeActionResultTaskInfo__IVSimpleMeleeActionResultTaskInfo((ISimpleMeleeActionResultTaskInfo *)m_pTaskInfo);
}

CSimpleMeleeActionResultTaskInfo::CSimpleMeleeActionResultTaskInfo(ISimpleMeleeActionResultTaskInfo* taskInfo) : CTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CSimpleMeleeActionResultTaskInfo::~CSimpleMeleeActionResultTaskInfo()
{

}

bool CSimpleMeleeActionResultTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((ISimpleMeleeActionResultTaskInfo *)m_pTaskInfo)->field_20);

	return true;
}

bool CSimpleMeleeActionResultTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((ISimpleMeleeActionResultTaskInfo *)m_pTaskInfo)->field_20);

	return true;
}

_GAME_END