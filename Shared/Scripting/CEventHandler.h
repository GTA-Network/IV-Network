//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CEventHandler.h
// Project: Shared
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CEventHandler_h
#define CEventHandler_h

#include <Common.h>
#include <assert.h>
#include <Squirrel/squirrel.h>
#include <Squirrel/sqobject.h>
#include <Scripting/CSquirrelArgument.h>

class CEventHandler
{
public:
	virtual SQVM*			GetScript()   const { return 0; };
	virtual SQObjectPtr		GetFunction() const { return (SQInteger)0; };
	virtual void*			GetChunk()    const { return 0; };
	virtual bool			equals(const CEventHandler* other) const = 0;
	virtual void			Call(CSquirrelArguments* pArguments, CSquirrelArgument* pReturn) = 0;
};

#endif // CEventHandler_h