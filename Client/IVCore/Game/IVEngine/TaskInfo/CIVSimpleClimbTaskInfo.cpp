#include "CIVSimpleClimbTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

CIVSimpleClimbTaskInfo::CIVSimpleClimbTaskInfo() : CIVTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (IVSimpleClimbTaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	CSimpleClimbTaskInfo__CSimpleClimbTaskInfo((IVSimpleClimbTaskInfo *)m_pTaskInfo, false, false, false, false, new CVector3(0.0f, 0.0f, 0.0f));
}

CIVSimpleClimbTaskInfo::CIVSimpleClimbTaskInfo(IVSimpleClimbTaskInfo * taskInfo) : CIVTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CIVSimpleClimbTaskInfo::~CIVSimpleClimbTaskInfo()
{

}

bool CIVSimpleClimbTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((IVSimpleClimbTaskInfo *)m_pTaskInfo)->m_bClimbType);
	pBitStream->Write(((IVSimpleClimbTaskInfo *)m_pTaskInfo)->m_bShimmyingLeft);
	pBitStream->Write(((IVSimpleClimbTaskInfo *)m_pTaskInfo)->m_bShimmyingRight);
	pBitStream->Write(((IVSimpleClimbTaskInfo *)m_pTaskInfo)->m_bPullingUp);
	pBitStream->Write(((IVSimpleClimbTaskInfo *)m_pTaskInfo)->m_vecGrabPosition);

	return true;
}

bool CIVSimpleClimbTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((IVSimpleClimbTaskInfo *)m_pTaskInfo)->m_bClimbType);
	pBitStream->Read(((IVSimpleClimbTaskInfo *)m_pTaskInfo)->m_bShimmyingLeft);
	pBitStream->Read(((IVSimpleClimbTaskInfo *)m_pTaskInfo)->m_bShimmyingRight);
	pBitStream->Read(((IVSimpleClimbTaskInfo *)m_pTaskInfo)->m_bPullingUp);
	pBitStream->Read(((IVSimpleClimbTaskInfo *)m_pTaskInfo)->m_vecGrabPosition);

	return true;
}