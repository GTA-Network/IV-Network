//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CPlayerEntity.h
// Project: Server.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CPlayerEntity_h
#define CPlayerEntity_h

#include "CNetworkEntity.h"

#include <Common.h>

class CPlayerEntity : public CNetworkEntity {
private:
	CString		m_strName;
public:
	CPlayerEntity();
	~CPlayerEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}

	void		SetName(const CString& strName) { m_strName = strName; }
	CString		GetName() { return m_strName; }
};

#endif // CPlayerEntity_h