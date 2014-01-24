#include "CPlayRandomAmbientsInfo.h"

#include <CCore.h>

extern CCore * g_pCore;

_GAME_BEGIN

#define IVPlayRandomAmbientsInfo__IVPlayRandomAmbientsInfo (*(IPlayRandomAmbientsInfo* (__thiscall *)(IPlayRandomAmbientsInfo*, BYTE state)) (g_pCore->GetBase() + 0xA1EB30))


CPlayRandomAmbientsInfo::CPlayRandomAmbientsInfo() : CTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (IPlayRandomAmbientsInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	IVPlayRandomAmbientsInfo__IVPlayRandomAmbientsInfo((IPlayRandomAmbientsInfo *)m_pTaskInfo, 0);
}

CPlayRandomAmbientsInfo::CPlayRandomAmbientsInfo(IPlayRandomAmbientsInfo* taskInfo) : CTaskInfoWithCloneTask()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CPlayRandomAmbientsInfo::~CPlayRandomAmbientsInfo()
{

}

bool CPlayRandomAmbientsInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((IPlayRandomAmbientsInfo *)m_pTaskInfo)->state);

	return true;
}

bool CPlayRandomAmbientsInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CTaskInfoWithCloneTask::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((IPlayRandomAmbientsInfo *)m_pTaskInfo)->state);

	return true;
}

_GAME_END