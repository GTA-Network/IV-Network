#include "CSimpleCarDriveTaskInfo.h"

#include <CCore.h>

extern CCore * g_pCore;

_GAME_BEGIN

CSimpleCarDriveTaskInfo::CSimpleCarDriveTaskInfo() : CStatusTaskInfo()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (ISimpleCarDriveTaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	IVSimpleCarDriveTaskInfo__IVSimpleCarDriveTaskInfo((ISimpleCarDriveTaskInfo *)m_pTaskInfo);
}

CSimpleCarDriveTaskInfo::CSimpleCarDriveTaskInfo(ISimpleCarDriveTaskInfo* taskInfo) : CStatusTaskInfo()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CSimpleCarDriveTaskInfo::~CSimpleCarDriveTaskInfo()
{

}

bool CSimpleCarDriveTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CStatusTaskInfo::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((ISimpleCarDriveTaskInfo *)m_pTaskInfo)->m_dwFlags);

	return true;
}

bool CSimpleCarDriveTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CStatusTaskInfo::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((ISimpleCarDriveTaskInfo *)m_pTaskInfo)->m_dwFlags);

	return true;
}

_GAME_END