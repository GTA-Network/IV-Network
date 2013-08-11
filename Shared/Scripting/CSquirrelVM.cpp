//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CSquirrelVM.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSquirrelVM.h"
#include <CLogFile.h>
#include <Squirrel/sqstdio.h>
#include <Squirrel/sqstdaux.h>

#include "../../Server/Scripting/Natives/CPlayerNatives.h"

CSquirrelVM::CSquirrelVM(CResource * pResource)
	: CScriptVM(pResource)
{
	m_pVM = sq_open(1024);

	// Register the default error handlers
	sqstd_seterrorhandlers(m_pVM);

	// Push the root table onto the stack
	sq_pushroottable(m_pVM);

	CPlayerNatives::Register(this);

}


CSquirrelVM::~CSquirrelVM()
{
	// Pop the root table from the stack
	sq_pop(m_pVM, 1);

	// Close the squirrel VM
	sq_close(m_pVM);
	m_pVM = NULL;
}

#include <SharedUtility.h>

bool CSquirrelVM::LoadScript(CString script)
{
	CString scriptPath( "%s/%s", GetResource()->GetResourceDirectoryPath().Get(), script.Get());
	
	if(!SharedUtility::Exists(script.Get()) && SQ_FAILED(sqstd_dofile( m_pVM, scriptPath.Get(), SQFalse, SQTrue )))
	{
		CLogFile::Printf("[%s] Failed to load file %s.", GetResource()->GetName().Get(), script.Get());
		return false;
	}
	CLogFile::Printf("\t[%s] Loaded file %s.", GetResource()->GetName().Get(), script.Get());
	return true;
}

bool CSquirrelVM::LoadScripts(std::list<CScript> scripts)
{
	for(auto Script : scripts)
		if (Script.GetType() != CLIENT_SCRIPT)
			if (!LoadScript(Script.GetScriptFileName()))
				return false;
	
	return true;
}

void CSquirrelVM::RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount, const char* szFunctionTemplate, bool bPushRootTable)
{
	// Push the function name onto the stack
	sq_pushstring(m_pVM, szFunctionName, -1);

	// Create a new function
	sq_newclosure(m_pVM, (SQFUNCTION)pfnFunction, 0);

	// Set the function parameter template and count
	if(iParameterCount != -1)
	{
		CString strTypeMask;

		// TODO: Change parameter
		CString strFunctionTemplate = szFunctionTemplate;
		if(strFunctionTemplate.IsNotEmpty())
			strTypeMask.Format(".%s", strFunctionTemplate.Get());

		sq_setparamscheck(m_pVM, (iParameterCount + 1), strTypeMask.Get());
	}

	// Create a new slot
	sq_createslot(m_pVM, -3);
}

void CSquirrelVM::PopBool(bool& b)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_BOOL)
	{
		SQBool sqB;
		sq_getbool(m_pVM, m_iStackIndex++, &sqB);
		b = sqB ? true : false;
		return;
	}

	b = false;
	m_iStackIndex++;
}

void CSquirrelVM::PopBool(bool& b, bool bDefaultValue)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_BOOL)
	{
		SQBool sqB;
		sq_getbool(m_pVM, m_iStackIndex++, &sqB);
		b = sqB ? true : false;
		return;
	} else {
		if(argType == OT_NULL)
		{
			b = bDefaultValue;
			m_iStackIndex++;
			return;
		}
	}
	b = false;
	m_iStackIndex++;
}

void CSquirrelVM::PopInteger(int& i)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_INTEGER)
	{
		sq_getinteger(m_pVM, m_iStackIndex++, &i);
		return;
	}

	i = 0;
	m_iStackIndex++;
}

void CSquirrelVM::PopInteger(int& i, int iDefaultValue)
{
		SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_INTEGER)
	{
		sq_getinteger(m_pVM, m_iStackIndex++, &i);
		return;
	}else {
		if(argType == OT_NULL)
		{
			i = iDefaultValue;
			m_iStackIndex++;
			return;
		}
	}

	i = 0;
	m_iStackIndex++;
}

void CSquirrelVM::PopFloat(float& f)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_FLOAT)
	{
		sq_getfloat(m_pVM, m_iStackIndex++, &f);
		return;
	}

	f = 0;
	m_iStackIndex++;
}

void CSquirrelVM::PopFloat(float& f, float fDefaultValue)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_FLOAT)
	{
		sq_getfloat(m_pVM, m_iStackIndex++, &f);
		return;
	} else {
		if(argType == OT_NULL) {
			f = fDefaultValue;
			m_iStackIndex++;
			return;
		}
	}

	f = 0;
	m_iStackIndex++;
}

void CSquirrelVM::PopString(CString& str)
{
	const char* c = NULL;
	sq_getstring(m_pVM, m_iStackIndex++, &c);
	str = c;

		SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_STRING)
	{
		const char* c = NULL;
		sq_getstring(m_pVM, m_iStackIndex++, &c);
		str = c;
		return;
	}

	str = "";
	m_iStackIndex++;
}

void CSquirrelVM::PopString(CString& str, CString strDefaultValue)
{
	const char* c = NULL;
	sq_getstring(m_pVM, m_iStackIndex++, &c);
	str = c;

	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_STRING)
	{
		const char* c = NULL;
		sq_getstring(m_pVM, m_iStackIndex++, &c);
		str = c;
		return;
	} else {
		if(argType == OT_NULL) {
			str = strDefaultValue;
		}
	}

	str = "";
	m_iStackIndex++;
}

void CSquirrelVM::PopVector(CVector3& vec)
{
	PopFloat(vec.fX);
	PopFloat(vec.fY);
	PopFloat(vec.fZ);
}


void CSquirrelVM::PopVector(CVector3& vec, CVector3 vecDefaultValue)
{
	PopFloat(vec.fX, vecDefaultValue.fX);
	PopFloat(vec.fY, vecDefaultValue.fY);
	PopFloat(vec.fZ, vecDefaultValue.fZ);
}


void CSquirrelVM::PushBool(const bool& b)
{
	sq_pushbool(m_pVM, b);
}

void CSquirrelVM::PushInteger(const int& i)
{
	sq_pushinteger(m_pVM, i);
}

void CSquirrelVM::PushFloat(const float& f)
{
	sq_pushfloat(m_pVM, f);
}

void CSquirrelVM::PushString(const CString& str)
{
	sq_pushstring(m_pVM, str.Get(), str.GetLength());
}

void CSquirrelVM::PushVector(const CVector3& vec)
{
	PushFloat(vec.fX);
	PushFloat(vec.fY);
	PushFloat(vec.fZ);
}
