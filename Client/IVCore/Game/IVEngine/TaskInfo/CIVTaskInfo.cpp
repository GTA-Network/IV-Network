#include "CIVTaskInfo.h"

#include <CCore.h>

extern CCore* g_pCore;

CIVTaskInfo::CIVTaskInfo()
{
	m_pTaskInfo = (IVTaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	CTaskInfo__CTaskInfo(m_pTaskInfo);
}

CIVTaskInfo::CIVTaskInfo(IVTaskInfo * pTaskInfo)
{
	m_pTaskInfo = pTaskInfo;
}

CIVTaskInfo::~CIVTaskInfo() { }

bool CIVTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(m_pTaskInfo->m_dwTaskId);

	return true;
}

bool CIVTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(m_pTaskInfo->m_dwTaskId);

	return true;
}