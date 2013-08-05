//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CSquirrelEventHandler.h
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CSquirrelEventHandler_h
#define CSquirrelEventHandler_h

#include <Common.h>
#include <assert.h>
#include <Scripting/CSquirrelArgument.h>
#include <Squirrel/sqobject.h>
#include "CEventHandler.h"

class CSquirrelEventHandler
{
private:
	SQVM * m_pVM;
	SQObjectPtr m_pFunction;
public:
	CSquirrelEventHandler();
	~CSquirrelEventHandler();

	SQVM*		GetScript() const { return m_pVM; }
	SQObjectPtr GetFunction() const { return m_pFunction; }

	bool equals(const CEventHandler* other) const;
	void Call(CSquirrelArguments* pArguments, CSquirrelArgument* pReturn);
};

#endif // CSquirrelEventHandler_h