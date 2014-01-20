#include "CIVSimpleCarDriveTaskInfo.h"

#include <CCore.h>

extern CCore * g_pCore;

CIVSimpleCarDriveTaskInfo::CIVSimpleCarDriveTaskInfo() : CIVStatusTaskInfo()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = (IVSimpleCarDriveTaskInfo *)CPool__Allocate_0(g_pTaskInfoPool);
	if (!m_pTaskInfo)
		return;

	IVSimpleCarDriveTaskInfo__IVSimpleCarDriveTaskInfo((IVSimpleCarDriveTaskInfo *)m_pTaskInfo);
}

CIVSimpleCarDriveTaskInfo::CIVSimpleCarDriveTaskInfo(IVSimpleCarDriveTaskInfo* taskInfo) : CIVStatusTaskInfo()
{
	if (m_pTaskInfo)
		delete[] m_pTaskInfo;

	m_pTaskInfo = taskInfo;
}

CIVSimpleCarDriveTaskInfo::~CIVSimpleCarDriveTaskInfo()
{

}

bool CIVSimpleCarDriveTaskInfo::Serialize(RakNet::BitStream * pBitStream)
{
	if (!CIVStatusTaskInfo::Serialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Write(((IVSimpleCarDriveTaskInfo *)m_pTaskInfo)->m_dwFlags);

	return true;
}

bool CIVSimpleCarDriveTaskInfo::Deserialize(RakNet::BitStream * pBitStream)
{
	if (!CIVStatusTaskInfo::Deserialize(pBitStream))
		return false;

	if (!m_pTaskInfo)
		return false;

	pBitStream->Read(((IVSimpleCarDriveTaskInfo *)m_pTaskInfo)->m_dwFlags);

	return true;
}