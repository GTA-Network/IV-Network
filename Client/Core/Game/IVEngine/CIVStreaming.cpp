//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CIVStreaming.cpp
// Project: Client.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVStreaming.h"
#include "../COffsets.h"
#include <SharedUtility.h>
#include <CLogFile.h>

unsigned int CIVStreaming::GetResourceTypeIndex(eResourceType resourceType)
{
#ifdef EXT_LOG
	CLogFile::Printf(__FUNCSIG__);
#endif
	switch(resourceType)
	{
	case RESOURCE_TYPE_WDR: return *(unsigned int *)COffsets::VAR_ResourceTypeWdrIndex;
	case RESOURCE_TYPE_WAD: return *(unsigned int *)COffsets::VAR_ResourceTypeWadIndex;
	case RESOURCE_TYPE_SCO: return *(unsigned int *)COffsets::VAR_ResourceTypeScoIndex;
	case RESOURCE_TYPE_WTD: return *(unsigned int *)COffsets::VAR_ResourceTypeWtdIndex;
	case RESOURCE_TYPE_CUT: return *(unsigned int *)COffsets::VAR_ResourceTypeCutIndex;
	case RESOURCE_TYPE_WDD: return *(unsigned int *)COffsets::VAR_ResourceTypeWddIndex;
	case RESOURCE_TYPE_WNV: return *(unsigned int *)COffsets::VAR_ResourceTypeWnvIndex;
	case RESOURCE_TYPE_RRR: return *(unsigned int *)COffsets::VAR_ResourceTypeRrrIndex;
	case RESOURCE_TYPE_WBD: return *(unsigned int *)COffsets::VAR_ResourceTypeWbdIndex;
	case RESOURCE_TYPE_IPL: return *(unsigned int *)COffsets::VAR_ResourceTypeIplIndex;
	case RESOURCE_TYPE_WBN: return *(unsigned int *)COffsets::VAR_ResourceTypeWbnIndex;
	case RESOURCE_TYPE_WBS: return *(unsigned int *)COffsets::VAR_ResourceTypeWbsIndex;
	}

	// Invalid resource type
	return 0;
}

void CIVStreaming::RequestResource(eResourceType resourceType, int iResourceIndex, DWORD dwFlags)
{
#ifdef EXT_LOG
	CLogFile::Printf(__FUNCSIG__);
#endif
	unsigned int uiResourceTypeIndex = GetResourceTypeIndex(resourceType);
	_asm
	{
		push dwFlags
		push uiResourceTypeIndex
		push iResourceIndex
		call COffsets::FUNC_RequestResource
		add esp, 0Ch
	}
}

void CIVStreaming::LoadAllResources(bool bUnknown)
{
#ifdef EXT_LOG
	CLogFile::Printf(__FUNCSIG__);
#endif
	_asm
	{
		push bUnknown
		call COffsets::FUNC_LoadAllResources
		add esp, 4
	}
}

bool CIVStreaming::HasResourceLoaded(eResourceType resourceType, int iResourceIndex)
{
#ifdef EXT_LOG
	CLogFile::Printf(__FUNCSIG__);
#endif
	unsigned int uiResourceTypeIndex = GetResourceTypeIndex(resourceType);
	bool bLoaded = false;
	_asm
	{
		push uiResourceTypeIndex
		push iResourceIndex
		call COffsets::FUNC_HasResourceLoaded
		add esp, 8
		mov bLoaded, al
	}
	return bLoaded;
}

void CIVStreaming::ReleaseResource(eResourceType resourceType, int iResourceIndex)
{
#ifdef EXT_LOG
	CLogFile::Printf(__FUNCSIG__);
#endif
	unsigned int uiResourceTypeIndex = GetResourceTypeIndex(resourceType);
	_asm
	{
		push uiResourceTypeIndex
		push iResourceIndex
		call COffsets::FUNC_ReleaseResource
		add esp, 8
	}
}

int CIVStreaming::GetModelIndexFromHash(DWORD dwModelHash)
{
#ifdef EXT_LOG
	CLogFile::Printf(__FUNCSIG__);
#endif
	int iModelIndex = -1;
	int * pModelIndex = &iModelIndex;
	_asm
	{
		push pModelIndex
		push dwModelHash
		call COffsets::FUNC_GetModelIndexFromHash
		add esp, 8
	}
	return iModelIndex;
}

void CIVStreaming::LoadWorldAtPosition(CVector3 vecPosition)
{
#ifdef EXT_LOG
	CLogFile::Printf(__FUNCSIG__);
#endif
	BYTE * pByteUnknown = &(*(BYTE *)(CGame::GetBase() + 0x11DC444));
	CVector3 * pVecPosition = &vecPosition;
	_asm
	{
		push pVecPosition
		mov ecx, pByteUnknown
		call COffsets::FUNC_LoadWorldAtPosition
	}
}

int CIVStreaming::GetAnimIndexFromName(const char * szName)
{
#ifdef EXT_LOG
	CLogFile::Printf(__FUNCSIG__);
#endif
	return GetAnimIndexFromHash(SharedUtility::IVHash(szName));
}

int CIVStreaming::GetAnimIndexFromHash(unsigned int uiHash)
{
#ifdef EXT_LOG
	CLogFile::Printf(__FUNCSIG__);
#endif
	int iAnimIndex = -1;
	_asm
	{
		push uiHash
		call COffsets::FUNC_CAnimStore__GetIndexFromHash
		mov iAnimIndex, eax
		add esp, 4
	}
	return iAnimIndex;
}