#include "CIVMeleeTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

CIVMeleeTaskInfo::CIVMeleeTaskInfo() : CIVTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (IVMeleeTaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	CIVMeleeTaskInfo__CIVMeleeTaskInfo((IVMeleeTaskInfo *)m_pTaskInfo);
}

CIVMeleeTaskInfo::CIVMeleeTaskInfo(IVMeleeTaskInfo* taskInfo) : CIVTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CIVMeleeTaskInfo::~CIVMeleeTaskInfo()
{

}

bool CIVMeleeTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	return true;
}

bool CIVMeleeTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	return true;
}