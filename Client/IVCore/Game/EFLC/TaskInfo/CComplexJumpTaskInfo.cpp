#include "CComplexJumpTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

_GAME_BEGIN

CComplexJumpTaskInfo::CComplexJumpTaskInfo() : CTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (IComplexJumpTaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	CComplexJumpTaskInfo__CComplexJumpTaskInfo((IComplexJumpTaskInfo *)m_pTaskInfo, false, false, false);
}

CComplexJumpTaskInfo::CComplexJumpTaskInfo(IComplexJumpTaskInfo* taskInfo) : CTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CComplexJumpTaskInfo::~CComplexJumpTaskInfo()
{

}

bool CComplexJumpTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((IComplexJumpTaskInfo *)m_pTaskInfo)->m_bHasPedJumped);
	pBitStream->Write(((IComplexJumpTaskInfo *)m_pTaskInfo)->m_bJumpOnSpot);
	pBitStream->Write(((IComplexJumpTaskInfo *)m_pTaskInfo)->m_bForceInAir);

	return true;
}

bool CComplexJumpTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((IComplexJumpTaskInfo *)m_pTaskInfo)->m_bHasPedJumped);
	pBitStream->Read(((IComplexJumpTaskInfo *)m_pTaskInfo)->m_bJumpOnSpot);
	pBitStream->Read(((IComplexJumpTaskInfo *)m_pTaskInfo)->m_bForceInAir);

	return true;
}

_GAME_END