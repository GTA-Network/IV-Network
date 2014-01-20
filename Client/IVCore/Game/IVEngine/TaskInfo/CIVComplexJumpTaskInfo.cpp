#include "CIVComplexJumpTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

CIVComplexJumpTaskInfo::CIVComplexJumpTaskInfo() : CIVTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (IVComplexJumpTaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	CComplexJumpTaskInfo__CComplexJumpTaskInfo((IVComplexJumpTaskInfo *)m_pTaskInfo, false, false, false);
}

CIVComplexJumpTaskInfo::CIVComplexJumpTaskInfo(IVComplexJumpTaskInfo* taskInfo) : CIVTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CIVComplexJumpTaskInfo::~CIVComplexJumpTaskInfo()
{

}

bool CIVComplexJumpTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((IVComplexJumpTaskInfo *)m_pTaskInfo)->m_bHasPedJumped);
	pBitStream->Write(((IVComplexJumpTaskInfo *)m_pTaskInfo)->m_bJumpOnSpot);
	pBitStream->Write(((IVComplexJumpTaskInfo *)m_pTaskInfo)->m_bForceInAir);

	return true;
}

bool CIVComplexJumpTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((IVComplexJumpTaskInfo *)m_pTaskInfo)->m_bHasPedJumped);
	pBitStream->Read(((IVComplexJumpTaskInfo *)m_pTaskInfo)->m_bJumpOnSpot);
	pBitStream->Read(((IVComplexJumpTaskInfo *)m_pTaskInfo)->m_bForceInAir);

	return true;
}