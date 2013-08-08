//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CSquirrelEventHandler.cpp
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSquirrelEventHandler.h"
#include "CSquirrel.h"

bool CSquirrelEventHandler::equals(const CEventHandler* other) const
{
	return other->GetScript() && other->GetScript() == GetScript() && other->GetFunction()._unVal.pClosure == GetFunction()._unVal.pClosure;
}

void CSquirrelEventHandler::Call(CSquirrelArguments* pArguments, CSquirrelArgument* pReturn)
{
	// Get the stack top
	int iTop = sq_gettop(m_pVM);

	// Process the parameters if needed
	int iParams = 1;

	if(pArguments)
	{
		pArguments->push_to_vm(m_pVM);
		iParams += pArguments->GetArguments()->size();
	}

	// Call the function
	SQObjectPtr res;

	if(m_pVM->Call(m_pFunction, iParams, m_pVM->_top-iParams, res, true))
	{
		// Set the return value if needed
		if(pReturn)
			*pReturn = res;
	}

	// Restore the stack top
	sq_settop(m_pVM, iTop);
}