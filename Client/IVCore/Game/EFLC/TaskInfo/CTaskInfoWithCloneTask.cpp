#include "CTaskInfoWithCloneTask.h"

#include <CCore.h>

extern CCore* g_pCore;

_GAME_BEGIN

CTaskInfoWithCloneTask::CTaskInfoWithCloneTask() : CTaskInfo()
{
	//TODO...
}

CTaskInfoWithCloneTask::~CTaskInfoWithCloneTask()
{

}

bool CTaskInfoWithCloneTask::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfo::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((ITaskInfoWithCloneTask *)m_pTaskInfo)->field_14);

	return true;
}

bool CTaskInfoWithCloneTask::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfo::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((ITaskInfoWithCloneTask *)m_pTaskInfo)->field_14);

	return true;
}

_GAME_END