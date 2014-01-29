#include "CTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

_GAME_BEGIN

CTaskInfo::CTaskInfo()
{
	m_pTaskInfo = (ITaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	CTaskInfo__CTaskInfo(m_pTaskInfo);
}

CTaskInfo::CTaskInfo(ITaskInfo * pTaskInfo)
{
	m_pTaskInfo = pTaskInfo;
}

CTaskInfo::~CTaskInfo() { }

bool CTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(m_pTaskInfo->m_dwTaskId);

	return true;
}

bool CTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(m_pTaskInfo->m_dwTaskId);

	return true;
}

_GAME_END