//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrelScript.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSquirrelScript.h"
#include <CLogFile.h>
#include <assert.h>
#include <Squirrel/sqstdio.h>
#include <Squirrel/sqstdaux.h>
#include <Squirrel/sqstdblob.h>
#include <Squirrel/sqstdio.h>
#include <Squirrel/sqstdsystem.h>
#include <Squirrel/sqstdmath.h>
#include <Squirrel/sqstdstring.h>
#include <Squirrel/sqstate.h>

CSquirrelScript::CSquirrelScript()
	: CScript()
{
	
}

CSquirrelScript::~CSquirrelScript()
{

}


bool CSquirrelScript::Load(CString strName, CString strPath)
{
	m_pVM = sq_open(1024);

	// Register the default error handlers
	sqstd_seterrorhandlers(m_pVM);

	// Set the print function and error function
	sq_setprintfunc(m_pVM, PrintFunction, PrintFunction);

	// Set the compiler error function
	sq_setcompilererrorhandler(m_pVM, CompilerErrorFunction);

	// Set our error handler
	sq_newclosure(m_pVM, PrintErrorFunction, 0);
	sq_seterrorhandler(m_pVM);
	sq_seterrorhandler(m_pVM);

	// Push the root table onto the stack
	sq_pushroottable(m_pVM);

	// Register the blob library
	sqstd_register_bloblib(m_pVM);

	// Register the math library
	sqstd_register_mathlib(m_pVM);

	// Register the string library
	sqstd_register_stringlib(m_pVM);

	return true;
}

void CSquirrelScript::Unload()
{
	// Pop the root table from the stack
	sq_pop(m_pVM, 1);

	// Close the squirrel VM
	sq_close(m_pVM);

	m_pVM = NULL;
}

bool CSquirrelScript::Execute()
{	
	// Add the script name constant
	RegisterConstant("SCRIPT_NAME", GetName());

	// Add the script path constant
	RegisterConstant("SCRIPT_PATH", GetName());

	// Load and compile the script
	if(SQ_FAILED(sqstd_dofile(m_pVM, GetName().Get(), SQFalse, SQTrue)))
		return false;

	return true;
}

void CSquirrelScript::RegisterConstant(CString strConstantName, CSquirrelScriptArgument value)
{
	// Push the constant name onto the stack
	sq_pushstring(m_pVM, strConstantName.Get(), -1);

	// Push the constant value onto the stack
	value.push(m_pVM);

	// Create a new slot
	sq_createslot(m_pVM, -3);
}

void CSquirrelScript::RegisterFunction(CString strFunctionName, SQFUNCTION pfnFunction, int iParameterCount, CString strFunctionTemplate)
{
	// Push the function name onto the stack
	sq_pushstring(m_pVM, strFunctionName.Get(), -1);

	// Create a new function
	sq_newclosure(m_pVM, pfnFunction, 0);

	// Set the function parameter template and count
	if(iParameterCount != -1)
	{
		CString strTypeMask;

		if(strFunctionTemplate.IsNotEmpty())
			strTypeMask.Format(".%s", strFunctionTemplate.Get());

		sq_setparamscheck(m_pVM, (iParameterCount + 1), strTypeMask.Get());
	}

	// Create a new slot
	sq_createslot(m_pVM, -3);
}

void CSquirrelScript::PrintFunction(SQVM * pVM, const char * szFormat, ...)
{
	va_list args;
	char szBuffer[512];
	va_start(args, szFormat);
	vsnprintf(szBuffer, sizeof(szBuffer), szFormat, args);
	va_end(args);
	CLogFile::Print(szBuffer);
}

void CSquirrelScript::CompilerErrorFunction(SQVM * pVM, const char * szError, const char * szSource, int iLine, int iColumn)
{
	//// Find the script
	//CSquirrelScript * pScript = CScriptingManager::GetInstance()->Get(pVM);

	//if(pScript)
	//{
	//	// Call the 'compilerError' event
	//	CSquirrelScriptArguments arguments;
	//	arguments.push(szError);
	//	arguments.push(szSource);
	//	arguments.push(iLine);
	//	arguments.push(iColumn);

	//	/*if(CEvents::GetInstance()->Call("compilerError", &arguments, pScript).GetInteger() == 1)
	//		CLogFile::Printf("Error: Failed to compile script %s (Error: %s (Line %d, Column %d)).", pScript->GetName().Get(), szError, iLine, iColumn);*/
	//}
}

#include <list>

typedef std::pair<CString, int> ErrorSourcePair;
typedef std::pair<CString, ErrorSourcePair> ErrorCallstackPair;
typedef std::list<ErrorCallstackPair> ErrorCallstackList;

typedef std::pair<CString, CSquirrelScriptArgument> ErrorLocalPair;
typedef std::list<ErrorLocalPair> ErrorLocalsList;

struct ErrorInfo
{
	CString strError;
	ErrorCallstackList callstack;
	ErrorLocalsList locals;
};


SQInteger CSquirrelScript::PrintErrorFunction(SQVM * pVM)
{
	if(sq_gettop(pVM) >= 1)
	{
		//const SQChar * szError = NULL;
		//sq_getstring(pVM, 2, &szError);
		//		
		//ErrorInfo info;
		//info.strError = szError;

		//SQStackInfos si;
		//SQInteger level = 1; // 1 is to skip this function that is level 0
		//const SQChar *name = 0; 
		//SQInteger seq = 0;

		//while(SQ_SUCCEEDED(sq_stackinfos(pVM, level, &si)))
		//{
		//	const SQChar * fn = _SC("unknown");
		//	const SQChar * src = _SC("unknown");
		//	if(si.funcname) fn = si.funcname;
		//	if(si.source) src = si.source;
		//	info.callstack.push_back(ErrorCallstackPair(fn, ErrorSourcePair(src, si.line)));
		//	level++;
		//}

		//for(level = 0; level < 10; level++)
		//{
		//	seq = 0;

		//	while((name = sq_getlocal(pVM, level, seq)))
		//	{
		//		seq++;
		//		CSquirrelScriptArgument arg;
		//		arg.pushFromStack(pVM, -1);
		//		info.locals.push_back(ErrorLocalPair(name, arg));
		//		sq_pop(pVM, 1);
		//	}
		//}

		//CSquirrel * pScript = CScriptingManager::GetInstance()->Get(pVM);

		//if(pScript)
		//{
		//	CSquirrelArguments arguments;
		//	CSquirrelArguments tempArray;
		//	CSquirrelArguments callstackTable;
		//	CSquirrelArguments localsTable;
		//	arguments.push(info.strError);

		//	for(ErrorCallstackList::iterator iter = info.callstack.begin(); iter != info.callstack.end(); iter++)
		//	{
		//		String strFunction = iter->first;
		//		String strSource = iter->second.first;
		//		int iLine = iter->second.second;
		//		callstackTable.push(strFunction);
		//		tempArray.reset();
		//		tempArray.push(strSource);
		//		tempArray.push(iLine);
		//		callstackTable.push(tempArray, true);
		//	}

		//	arguments.push(callstackTable, false);

		//	for(ErrorLocalsList::iterator iter = info.locals.begin(); iter != info.locals.end(); iter++)
		//	{
		//		String strName = iter->first;
		//		CSquirrelArgument arg = iter->second;
		//		localsTable.push(strName);
		//		localsTable.push(arg);
		//	}

		//	arguments.push(localsTable, false);

		//	if(CEvents::GetInstance()->Call("scriptError", &arguments, pScript).GetInteger() == 1)
		//	{
		//		CLogFile::Printf("<Error (%s)>", info.strError.Get());

		//		CLogFile::Printf("<Callstack>");
		//		for(ErrorCallstackList::iterator iter = info.callstack.begin(); iter != info.callstack.end(); iter++)
		//		{
		//			String strFunction = iter->first;
		//			String strSource = iter->second.first;
		//			int iLine = iter->second.second;
		//			CLogFile::Printf("<%s (%s, %d)>", strFunction.Get(), strSource.Get(), iLine);
		//		}
		//		CLogFile::Printf("</Callstack>");

		//		CLogFile::Printf("<Locals>");
		//		for(ErrorLocalsList::iterator iter = info.locals.begin(); iter != info.locals.end(); iter++)
		//		{
		//			String strName = iter->first;
		//			CSquirrelArgument arg = iter->second;
		//			CLogFile::Printf("<%s (%s)>", strName.Get(), arg.GetTypeString().Get());
		//		}
		//		CLogFile::Printf("</Locals>");

		//		CLogFile::Printf("</Error>");
		//	}
		//}
	}

	return 0;
}

// TODO: add register class