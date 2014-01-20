#include "CIVPlayRandomAmbientsInfo.h"

#include <CCore.h>

extern CCore * g_pCore;

#define IVPlayRandomAmbientsInfo__IVPlayRandomAmbientsInfo (*(IVPlayRandomAmbientsInfo* (__thiscall *)(IVPlayRandomAmbientsInfo*, BYTE state)) (g_pCore->GetBase() + 0xA1EB30))


CIVPlayRandomAmbientsInfo::CIVPlayRandomAmbientsInfo() : CIVTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (IVPlayRandomAmbientsInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	IVPlayRandomAmbientsInfo__IVPlayRandomAmbientsInfo((IVPlayRandomAmbientsInfo *)m_pTaskInfo, 0);
}

CIVPlayRandomAmbientsInfo::CIVPlayRandomAmbientsInfo(IVPlayRandomAmbientsInfo* taskInfo) : CIVTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CIVPlayRandomAmbientsInfo::~CIVPlayRandomAmbientsInfo()
{

}

bool CIVPlayRandomAmbientsInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((IVPlayRandomAmbientsInfo *)m_pTaskInfo)->state);

	return true;
}

bool CIVPlayRandomAmbientsInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CIVTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((IVPlayRandomAmbientsInfo *)m_pTaskInfo)->state);

	return true;
}