//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CIncludedResource.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CIncludedResource_h
#define CIncludedResource_h

#include "CResource.h"

class CIncludedResource {

private:
	class CResource *		m_resource; // the resource this links to
	class CResource *		m_owner; // the resource this is inside
public:
	CIncludedResource();
	~CIncludedResource();

	inline CResource *          GetResource() { return m_resource; }
};

#endif // CIncludedResource_h