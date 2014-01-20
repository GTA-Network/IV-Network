#include "CIVTaskInfoWithCloneTask.h"

#include <CCore.h>

extern CCore* g_pCore;

CIVTaskInfoWithCloneTask::CIVTaskInfoWithCloneTask() : CIVTaskInfo()
{
	//TODO...
}

CIVTaskInfoWithCloneTask::~CIVTaskInfoWithCloneTask()
{

}

bool CIVTaskInfoWithCloneTask::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfo::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((IVTaskInfoWithCloneTask *)m_pTaskInfo)->field_14);

	return true;
}

bool CIVTaskInfoWithCloneTask::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfo::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((IVTaskInfoWithCloneTask *)m_pTaskInfo)->field_14);

	return true;
}
