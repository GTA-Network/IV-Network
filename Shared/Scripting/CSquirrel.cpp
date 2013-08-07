//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CSquirrel.cpp
// Project: (Shared)
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSquirrel.h"
#include "CSquirrelArgument.h"
#include <CLogFile.h>
#include <Squirrel/sqstdaux.h>
#include <Squirrel/sqstdblob.h>
#include <Squirrel/sqstdio.h>
#include <Squirrel/sqstdmath.h>
#include <Squirrel/sqstdstring.h>
#include <Squirrel/sqstdsystem.h>

#ifdef _SERVER
#include <Scripting/Natives/Natives.h>
#else

#endif

#ifdef _LINUX
#define stricmp strcasecmp
#define vsprintf_s vsprintf
#define vsnprintf_s vsnprintf
#define sprintf_s sprintf
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#endif


#define DEFAULT_STACK_SIZE 1024

/************************************/
/* Some old shit from the other mod */
/************************************/
void printfunc(HSQUIRRELVM vm, const char *s,...)
{
	va_list vl;
	char tmp[256];
	va_start(vl, s);
	vsprintf(tmp, s, vl);
	va_end(vl);
	CLogFile::Printf("%s",tmp);
}

void errorfunc(HSQUIRRELVM vm, const char *s, ...)
{
	va_list args;
	char tmps[256];
	va_start(args, s);
	vsprintf(tmps, s, args);
	va_end(args);

	char *tmp = (char *)tmps;

	size_t offstart = 0, offend = 0;

	size_t len = strlen(tmp);
	for (size_t i = 0; i < len; ++i)
	{
		switch (tmp[i])
		{
		case ' ':
		case '\r':
		case '\n':
		case '\t':
			++offstart;
			break;
		default:
			i = len - 1;
			break;
		}
	}

	tmp += offstart;
	len -= offstart;

	for (size_t i = len - 1; i > 0; --i)
	{
		switch (tmp[i])
		{
		case ' ':
		case '\r':
		case '\n':
		case '\t':
			++offend;
			break;
		default:
			i = 1;
			break;
		}
	}

	tmp[len - offend] = '\0';

	CLogFile::Printf("%s", tmp);
}
/************************************/

CSquirrel::CSquirrel(CResource* pResource)
{
	m_pResource = pResource;

	// Create the VM
	m_pVM = sq_open(DEFAULT_STACK_SIZE);

	// Was the VM created successfully?
	if( m_pVM )
	{
		// Push the root table onto the stack
		sq_pushroottable(m_pVM);

		// Register the default error handles
		sqstd_seterrorhandlers(m_pVM);

		// Set the print and error functions
		sq_setprintfunc(m_pVM, printfunc, errorfunc);
		
		// Register the blob library
		sqstd_register_bloblib(m_pVM);

		// Register the input/out library
		sqstd_register_iolib(m_pVM);

		// Register the math library
		sqstd_register_mathlib(m_pVM);

		// Register the string library
		sqstd_register_stringlib(m_pVM);

		// Register the system library
		sqstd_register_systemlib(m_pVM);

		// Register our shared functions

		// Register our own functions
#ifdef _SERVER
		CPlayerNatives::Register(this);
		CVehicleNatives::Register(this);
		C3DLabelNatives::Register(this);
		CActorNatives::Register(this);
		CCheckpointNatives::Register(this);
		CObjectNatives::Register(this);
		CServerNatives::Register(this);
		CBlipNatives::Register(this);
#endif
	}
}

CSquirrel::~CSquirrel()
{
	if(m_pVM)
	{
		// Pop the root table from the stack
		sq_pop(m_pVM, 1);

		// Close the squirrel VM
		sq_close(m_pVM);
	}
}

bool CSquirrel::LoadScript(CString script)
{
	CString scriptPath( "%s/%s", m_pResource->GetPath().Get(), script.Get());
	if(SQ_FAILED(sqstd_dofile( m_pVM, scriptPath.Get(), SQFalse, SQTrue )))
	{
		CLogFile::Printf("[%s] Failed to load file %s.", m_pResource->GetName().Get(), script.Get());
		return false;
	}
	CLogFile::Printf("\t[%s] Loaded file %s.", m_pResource->GetName().Get(), script.Get());
	return true;
}

bool CSquirrel::LoadScripts(std::list<CScript> scripts)
{
	for(auto strScript : scripts)
		if(strScript.GetType() != CLIENT_SCRIPT)
			if(!LoadScript(strScript.GetScriptFileName()))
				return false;

	return true;
}

bool CSquirrel::RegisterClassStart(const char * szClassName, const char * szBaseClassName)
{
	// Get the stack top
	int oldtop = sq_gettop(m_pVM);

	// Push the root table onto the stack
	sq_pushroottable(m_pVM);

	// Push the class name onto the stack
	sq_pushstring(m_pVM, szClassName, -1);

	// Do we have a base class name?
	if(szBaseClassName)
	{
		// Push the base class name onto the stack
		sq_pushstring(m_pVM, szBaseClassName, -1);

		// Attempt to get the base class
		if(SQ_FAILED(sq_get(m_pVM, -3)))
		{
			// Failed to get the base class, Restore the stack top
			sq_settop(m_pVM, oldtop);
			return false;
		}
	}

	// Create the class
	if(SQ_FAILED(sq_newclass(m_pVM, (szBaseClassName == NULL) ? 0 : 1)))
	{
		// Failed to create the class, Restore the stack top
		sq_settop(m_pVM, oldtop);
		return false;
	}

	// Set the class type tag
	//sq_settypetag(m_pVM, -1, NULL);
	return true;
}

void CSquirrel::RegisterClassFinish()
{
	// Create a new slot
	sq_createslot(m_pVM, -3);

	// Pop the root table from the stack
	sq_pop(m_pVM, 1);
}

void CSquirrel::RegisterFunction(const char * szFunctionName, SQFUNCTION pfnFunction, int iParameterCount, const char * szFunctionTemplate, bool bPushRootTable)
{
	// Push the root table onto the stack if needed
	if(bPushRootTable)
		sq_pushroottable(m_pVM);

	// Push the function name onto the stack
	sq_pushstring(m_pVM, szFunctionName, -1);

	// Create a new function
	sq_newclosure(m_pVM, pfnFunction, 0);

	// Set the function parameter template and count
	if(iParameterCount != -1)
	{
		char szTemp[128];

		if(szFunctionTemplate)
			sprintf(szTemp, ".%s", szFunctionTemplate);

		sq_setparamscheck(m_pVM, (iParameterCount + 1), (szFunctionTemplate) ? szTemp : NULL);
	}

	// Create a new slot
	sq_createslot(m_pVM, -3);

	// Pop the root table from the stack if needed
	if(bPushRootTable)
		sq_pop(m_pVM, 1);
}

bool CSquirrel::Call(SQObjectPtr& pFunction, CSquirrelArguments* pArguments)
{
	// Get the stack top
	int iTop = sq_gettop(m_pVM);

	// push the root table onto the stack
	sq_pushroottable(m_pVM);

	// push all arguments
	if(pArguments)
		pArguments->push_to_vm(m_pVM);

	// Call the function
	SQObjectPtr res;
	bool success = m_pVM->Call(pFunction, (pArguments ? pArguments->GetArguments()->size() : 0) + 1, m_pVM->_top - (pArguments ? pArguments->GetArguments()->size() : 0) - 1, res, true);

	// Restore the stack top
	sq_settop(m_pVM, iTop);

	// delete the 'source' variable
	//sq_pushroottable(m_pVM);
	//sq_pushstring(m_pVM, "source", -1);
	//sq_deleteslot(m_pVM, -2, false);

	// return value dependant on the function's return (if it's a boolean false, then this will return false - otherwise true)
	if( success )
		return res._type != OT_BOOL || ( res._unVal.nInteger == 0 ? false : true );
	else
		return false;
}

void CSquirrel::Call(SQObjectPtr pFunction, CSquirrelArguments * pArguments, CSquirrelArgument * pReturn)
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

	if(m_pVM->Call(pFunction, iParams, m_pVM->_top-iParams, res, true))
	{
		// Set the return value if needed
		if(pReturn)
			*pReturn = res;
	}

	// Restore the stack top
	sq_settop(m_pVM, iTop);
}