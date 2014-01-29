#include "CMeleeTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

_GAME_BEGIN

CMeleeTaskInfo::CMeleeTaskInfo() : CTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (IMeleeTaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	CMeleeTaskInfo__CMeleeTaskInfo((IMeleeTaskInfo *)m_pTaskInfo);
}

CMeleeTaskInfo::CMeleeTaskInfo(IMeleeTaskInfo* taskInfo) : CTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CMeleeTaskInfo::~CMeleeTaskInfo()
{

}

bool CMeleeTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	return true;
}

bool CMeleeTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	return true;
}

_GAME_END