#include "CStatusTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

_GAME_BEGIN

CStatusTaskInfo::CStatusTaskInfo() : CTaskInfoWithCloneTask()
{
	//TODO...
}

CStatusTaskInfo::~CStatusTaskInfo()
{

}

bool CStatusTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((IStatusTaskInfo *)m_pTaskInfo)->m_dwStatus);

	return true;
}

bool CStatusTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((IStatusTaskInfo *)m_pTaskInfo)->m_dwStatus);

	return true;
}

_GAME_END