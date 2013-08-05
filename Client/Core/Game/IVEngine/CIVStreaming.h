//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CIVStreaming.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVStreaming_h
#define CIVStreaming_h

#include <IV/IVCommon.h>

// unsigned int var addresses
enum eResourceType
{
	RESOURCE_TYPE_WDR, // Model information file
	RESOURCE_TYPE_WAD, // Animation file
	RESOURCE_TYPE_SCO, // Script file
	RESOURCE_TYPE_WTD, // Texture file
	RESOURCE_TYPE_CUT, // Cutscene file
	RESOURCE_TYPE_WDD, // Drawable dictionary store
	RESOURCE_TYPE_WNV, // Navigation mesh file
	RESOURCE_TYPE_RRR, // Car recording file
	RESOURCE_TYPE_WBD, // Collision file
	RESOURCE_TYPE_IPL, // Item placement file
	RESOURCE_TYPE_WBN, // Static boundaries file
	RESOURCE_TYPE_WBS  // Blend shape file
};

class CIVStreaming
{
public:
	unsigned	 GetResourceTypeIndex(eResourceType resourceType);
	void         RequestResource(eResourceType resourceType, int iResourceIndex, DWORD dwFlags = 0x1A);
	void         LoadAllResources(bool bUnknown = true);
	bool         HasResourceLoaded(eResourceType resourceType, int iResourceIndex);
	void         ReleaseResource(eResourceType resourceType, int iResourceIndex);
	int          GetModelIndexFromHash(DWORD dwModelHash);
	void         LoadWorldAtPosition(CVector3 vecPosition);

	int          GetAnimIndexFromName(const char * szName);
	int          GetAnimIndexFromHash(unsigned int uiHash);
};

#endif // CIVStreaming_h