#include "CSimpleClimbTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

_GAME_BEGIN

CSimpleClimbTaskInfo::CSimpleClimbTaskInfo() : CTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (ISimpleClimbTaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	CSimpleClimbTaskInfo__CSimpleClimbTaskInfo((ISimpleClimbTaskInfo *)m_pTaskInfo, false, false, false, false, new CVector3(0.0f, 0.0f, 0.0f));
}

CSimpleClimbTaskInfo::CSimpleClimbTaskInfo(ISimpleClimbTaskInfo * taskInfo) : CTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CSimpleClimbTaskInfo::~CSimpleClimbTaskInfo()
{

}

bool CSimpleClimbTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((ISimpleClimbTaskInfo *)m_pTaskInfo)->m_bClimbType);
	pBitStream->Write(((ISimpleClimbTaskInfo *)m_pTaskInfo)->m_bShimmyingLeft);
	pBitStream->Write(((ISimpleClimbTaskInfo *)m_pTaskInfo)->m_bShimmyingRight);
	pBitStream->Write(((ISimpleClimbTaskInfo *)m_pTaskInfo)->m_bPullingUp);
	pBitStream->Write(((ISimpleClimbTaskInfo *)m_pTaskInfo)->m_vecGrabPosition);

	return true;
}

bool CSimpleClimbTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((ISimpleClimbTaskInfo *)m_pTaskInfo)->m_bClimbType);
	pBitStream->Read(((ISimpleClimbTaskInfo *)m_pTaskInfo)->m_bShimmyingLeft);
	pBitStream->Read(((ISimpleClimbTaskInfo *)m_pTaskInfo)->m_bShimmyingRight);
	pBitStream->Read(((ISimpleClimbTaskInfo *)m_pTaskInfo)->m_bPullingUp);
	pBitStream->Read(((ISimpleClimbTaskInfo *)m_pTaskInfo)->m_vecGrabPosition);

	return true;
}

_GAME_END