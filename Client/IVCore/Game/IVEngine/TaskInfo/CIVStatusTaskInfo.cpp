#include "CIVStatusTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

CIVStatusTaskInfo::CIVStatusTaskInfo() : CIVTaskInfoWithCloneTask()
{
	//TODO...
}

CIVStatusTaskInfo::~CIVStatusTaskInfo()
{

}

bool CIVStatusTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((IVStatusTaskInfo *)m_pTaskInfo)->m_dwStatus);

	return true;
}

bool CIVStatusTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((IVStatusTaskInfo *)m_pTaskInfo)->m_dwStatus);

	return true;
}