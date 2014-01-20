#include "CIVSimpleMeleeActionResultTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

CIVSimpleMeleeActionResultTaskInfo::CIVSimpleMeleeActionResultTaskInfo() : CIVTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (IVSimpleMeleeActionResultTaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	IVSimpleMeleeActionResultTaskInfo__IVSimpleMeleeActionResultTaskInfo((IVSimpleMeleeActionResultTaskInfo *)m_pTaskInfo);
}

CIVSimpleMeleeActionResultTaskInfo::CIVSimpleMeleeActionResultTaskInfo(IVSimpleMeleeActionResultTaskInfo* taskInfo) : CIVTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CIVSimpleMeleeActionResultTaskInfo::~CIVSimpleMeleeActionResultTaskInfo()
{

}

bool CIVSimpleMeleeActionResultTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((IVSimpleMeleeActionResultTaskInfo *)m_pTaskInfo)->field_20);

	return true;
}

bool CIVSimpleMeleeActionResultTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((IVSimpleMeleeActionResultTaskInfo *)m_pTaskInfo)->field_20);

	return true;
}