//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CSquirrelVM.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSquirrelVM.h"
#include <CLogFile.h>
#include <SharedUtility.h>
#include <assert.h>
#include <map>
#include <Squirrel/sqvm.h>
#include <Squirrel/sqstdio.h>
#include <Squirrel/sqstdaux.h>
#include <Squirrel/sqstdstring.h>
#include <Squirrel/sqstdmath.h>
#include <Squirrel/sqstdstream.h>
#include <Squirrel/sqstdsystem.h>
#include "CScriptArgument.h"
#include "CScriptClass.h"

std::map<void*, HSQOBJECT> m_Instances;

void PrintFunction(SQVM * pVM, const char * szFormat, ...)
{
        va_list args;
        char szBuffer[512];
        va_start(args, szFormat);
        vsnprintf(szBuffer, sizeof(szBuffer), szFormat, args);
        va_end(args);
        CLogFile::Print(szBuffer);
}

CSquirrelVM::CSquirrelVM(CResource * pResource)
	: CScriptVM(pResource),
	m_iStackIndex(2)
{
	m_pVM = sq_open(1024);


	// Register the default error handlers
	sqstd_seterrorhandlers(m_pVM);

	// Push the root table onto the stack
	sq_pushroottable(m_pVM);

	sqstd_register_stringlib(m_pVM);

	sqstd_register_mathlib(m_pVM);

	sqstd_register_systemlib(m_pVM);

	sq_setprintfunc(m_pVM, PrintFunction, PrintFunction);
}


CSquirrelVM::~CSquirrelVM()
{
	// Pop the root table from the stack
	sq_pop(m_pVM, 1);

	// Close the squirrel VM
	sq_close(m_pVM);
	m_pVM = NULL;
}



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

void* CSquirrelVM::GetUserData(int idx)
{
	SQUserPointer p;
	sq_getuserpointer(m_pVM, -1, &p);
	return (void*)p;
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
	sq_setnativeclosurename(m_pVM, -1, szFunctionName);
	// Create a new slot
	sq_createslot(m_pVM, -3);
}
extern int iFuncIndex;
int oldtop = 0;


void CSquirrelVM::RegisterScriptClass(const char* className, scriptFunction pfnFunction, void* userPointer, const char* baseClass)
{

	iFuncIndex = 0;
#if 1
	int n = 0;
	oldtop = sq_gettop(m_pVM);
	sq_pushroottable(m_pVM);
	sq_pushstring(m_pVM, className, -1);

	if(baseClass) {
		sq_pushstring(m_pVM, baseClass, -1);
		if(SQ_FAILED(sq_get(m_pVM, -3))) { // make sure base exists
			sq_settop(m_pVM, oldtop);
			return;
		}
	}
	if(SQ_FAILED(sq_newclass(m_pVM, baseClass ? 1 : 0))) {
		sq_settop(m_pVM, oldtop);
		return;
	}

	sq_pushstring(m_pVM, _SC("constructor"), -1);
	if (userPointer != nullptr)
	{
		sq_pushuserpointer(m_pVM, userPointer);
		sq_newclosure(m_pVM, (SQFUNCTION) pfnFunction, 1);
	}
	else
		sq_newclosure(m_pVM, (SQFUNCTION)pfnFunction, 0);
	sq_newslot(m_pVM, -3, false); // Add the constructor method
#endif
}

SQInteger deleteClassInstance(SQUserPointer ptr, SQInteger size)
{
    int *p = static_cast<int *>(ptr);
    delete p;

    return 0;
}

void CSquirrelVM::SetClassInstance(const char* szClassName, void * pInstance)
{
	sq_setinstanceup(m_pVM, 1, (SQUserPointer *) pInstance);
	sq_setreleasehook(m_pVM, 1, deleteClassInstance);

	HSQOBJECT instance;
	sq_resetobject(&instance);
	sq_getstackobj(m_pVM, 1, &instance);
	sq_addref(m_pVM, &instance);
	m_Instances.insert(std::pair<void*, HSQOBJECT>(pInstance, instance));
}


bool CreateNativeClassInstance(HSQUIRRELVM v,
	const SQChar *classname,
	SQUserPointer ud,
	SQRELEASEHOOK hook)
	 {
			// If we don't do this, SquirrelVM keeps an old pointer around and this 
				// will be used by SquirrelObject. That crashes when using several VMs.
			
			int oldtop = sq_gettop(v);
		sq_pushroottable(v);
		sq_pushstring(v, classname, -1);
		if (SQ_FAILED(sq_rawget(v, -2))){ //Get the class (created with sq_newclass()).
			sq_settop(v, oldtop);
			return false;
			
		}
			//sq_pushroottable(v);
			if (SQ_FAILED(sq_createinstance(v, -1))) {
				sq_settop(v, oldtop);
				return false;
				
			}
		
			#ifdef SQ_USE_CLASS_INHERITANCE
			 HSQOBJECT ho;
		sq_getstackobj(v, -1, &ho); // OT_INSTANCE
		SquirrelObject instance(ho);
		SqPlus::PopulateAncestry(v, instance, ud);
		#endif
			
			sq_remove(v, -3); //removes the root table
		sq_remove(v, -2); //removes the class
		if (SQ_FAILED(sq_setinstanceup(v, -1, ud))) {
			sq_settop(v, oldtop);
			return false;
			
		}
		sq_setreleasehook(v, -1, hook);
		return true;
		}


bool CreateConstructNativeClassInstance(HSQUIRRELVM v, const SQChar * className) {
	int oldtop = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v, className, -1);
	if (SQ_FAILED(sq_rawget(v, -2))) { // Get the class (created with sq_newclass()).
		sq_settop(v, oldtop);
		return false;
		
	} // if
	#if 0
		 sq_remove(v, -3); // Remove the root table.
	sq_push(v, 1);    // Push the 'this'.
	#else // Kamaitati's change. 5/28/06 jcs.
		 sq_remove(v, -2); // Remove the root table.
	sq_pushroottable(v); // Push the 'this'.
	#endif
		 if (SQ_FAILED(sq_call(v, 1, SQTrue, false))) { // Call ClassName(): creates new instance and calls constructor (instead of sq_createinstance() where constructor is not called).
			sq_settop(v, oldtop);
			return false;
			
		} // if
	sq_remove(v, -2); // Remove the class.
		//  int newtop = sq_gettop(v);
		return true;
	
} // CreateConstructNativeClassInstance

void CSquirrelVM::PushInstance(const char* szClassName, void * pInstance)
{
	if (m_Instances.find(pInstance) != m_Instances.end())
	{
		sq_pushobject(m_pVM, m_Instances.find(pInstance)->second);
	}
	else
	{
		CreateConstructNativeClassInstance(m_pVM, szClassName);

		sq_setinstanceup(m_pVM, -1, (SQUserPointer *) pInstance);
		sq_setreleasehook(m_pVM, -1, deleteClassInstance);

		HSQOBJECT instance;
		sq_resetobject(&instance);
		sq_getstackobj(m_pVM, -1, &instance);
		sq_addref(m_pVM, &instance);
		m_Instances.insert(std::pair<void*, HSQOBJECT>(pInstance, instance));
	}
}

void* CSquirrelVM::PopInstance(const char * szClassName)
{

	SQUserPointer pInstance = nullptr;
	SQObjectType type = sq_gettype(m_pVM, m_iStackIndex);
	assert(type == SQObjectType::OT_INSTANCE);
	if (SQ_FAILED(sq_getinstanceup(m_pVM, m_iStackIndex++, &pInstance, nullptr)))
		pInstance = nullptr;

	return pInstance;
}

void* CSquirrelVM::GetClassInstance(const char* szClassName)
{
	SQUserPointer pInstance = nullptr;
	SQObjectType type = sq_gettype(m_pVM, 1);
	assert(type == SQObjectType::OT_INSTANCE);
	if(SQ_FAILED(sq_getinstanceup(m_pVM, 1, &pInstance, nullptr)))
		pInstance = nullptr;

	return pInstance;
}

void CSquirrelVM::RegisterClassFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount, const char* szFunctionTemplate)
{
	sq_pushstring(m_pVM, szFunctionName, -1);
	sq_newclosure(m_pVM, (SQFUNCTION)pfnFunction, 0);
	sq_newslot(m_pVM, -3, SQFalse);
}

void CSquirrelVM::FinishRegisterScriptClass()
{
	sq_newslot(m_pVM, -3, SQFalse);
	sq_pop(m_pVM, m_pVM->_top-oldtop);
	iFuncIndex = 0;
}

void CSquirrelVM::Pop(bool& b)
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

void CSquirrelVM::Pop(bool& b, bool bDefaultValue)
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

void CSquirrelVM::Pop(int& i)
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

void CSquirrelVM::Pop(int& i, int iDefaultValue)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_INTEGER)
	{
		sq_getinteger(m_pVM, m_iStackIndex++, &i);
		return;
	}
	else {
		if (argType == OT_NULL)
		{
			i = iDefaultValue;
			m_iStackIndex++;
			return;
		}
	}

	i = 0;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(unsigned int& i)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_INTEGER)
	{
		sq_getinteger(m_pVM, m_iStackIndex++, (int*) &i);
		return;
	}

	i = 0;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(unsigned int& i, unsigned int iDefaultValue)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_INTEGER)
	{
		sq_getinteger(m_pVM, m_iStackIndex++, (int*) &i);
		return;
	}
	else {
		if (argType == OT_NULL)
		{
			i = iDefaultValue;
			m_iStackIndex++;
			return;
		}
	}

	i = 0;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(long& i)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_INTEGER)
	{
		sq_getinteger(m_pVM, m_iStackIndex++, (int*) &i);
		return;
	}

	i = 0;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(long& i, long iDefaultValue)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_INTEGER)
	{
		sq_getinteger(m_pVM, m_iStackIndex++, (int*) &i);
		return;
	}
	else {
		if (argType == OT_NULL)
		{
			i = iDefaultValue;
			m_iStackIndex++;
			return;
		}
	}

	i = 0;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(unsigned long& i)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_INTEGER)
	{
		sq_getinteger(m_pVM, m_iStackIndex++, (int*) &i);
		return;
	}

	i = 0;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(unsigned long& i, unsigned long iDefaultValue)
{
	SQObjectType argType = sq_gettype(m_pVM, m_iStackIndex);
	if (argType == OT_INTEGER)
	{
		sq_getinteger(m_pVM, m_iStackIndex++, (int*) &i);
		return;
	}
	else {
		if (argType == OT_NULL)
		{
			i = iDefaultValue;
			m_iStackIndex++;
			return;
		}
	}

	i = 0;
	m_iStackIndex++;
}

void CSquirrelVM::Pop(float& f)
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

void CSquirrelVM::Pop(float& f, float fDefaultValue)
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

void CSquirrelVM::Pop(CString& str)
{
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

void CSquirrelVM::Pop(CString& str, CString strDefaultValue)
{
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

void CSquirrelVM::Pop(CVector3& vec)
{
	Pop(vec.fX);
	Pop(vec.fY);
	Pop(vec.fZ);
}


void CSquirrelVM::Pop(CVector3& vec, CVector3 vecDefaultValue)
{
	Pop(vec.fX, vecDefaultValue.fX);
	Pop(vec.fY, vecDefaultValue.fY);
	Pop(vec.fZ, vecDefaultValue.fZ);
}


void CSquirrelVM::Push(const bool& b)
{
	sq_pushbool(m_pVM, b);
}

void CSquirrelVM::Push(const int& i)
{
	sq_pushinteger(m_pVM, i);
}

void CSquirrelVM::Push(const unsigned int& i)
{
	sq_pushinteger(m_pVM, i);
}

void CSquirrelVM::Push(const long& i)
{
	sq_pushinteger(m_pVM, i);
}

void CSquirrelVM::Push(const unsigned long& i)
{
	sq_pushinteger(m_pVM, i);
}

void CSquirrelVM::Push(const float& f)
{
	sq_pushfloat(m_pVM, f);
}

void CSquirrelVM::Push(const CString& str)
{
	sq_pushstring(m_pVM, str.Get(), str.GetLength());
}

void CSquirrelVM::Push(const CVector3& vec)
{
	Push(vec.fX);
	Push(vec.fY);
	Push(vec.fZ);
}

void CSquirrelVM::PushArray(const CScriptArguments &array)
{
	sq_newarray(m_pVM, 0);
	for(auto pArgument : array.m_Arguments)
	{
		pArgument->Push(this);

		sq_arrayappend(m_pVM, -2);
	}
}


void CSquirrelVM::PushTable(const CScriptArguments &table)
{
	sq_newtable(m_pVM);
	for(auto iter = table.m_Arguments.begin(); iter != table.m_Arguments.end(); iter++)
	{
		(*iter)->Push(this);
		++iter;
		(*iter)->Push(this);
		sq_createslot(m_pVM, -3);
	}
}

CScriptArgument::ArgumentType CSquirrelVM::GetType(int idx)
{
	SQVM* VM = reinterpret_cast<CSquirrelVM*>(this)->GetVM();
	SQObjectPtr obj = stack_get(VM, idx);
	switch(obj._type)
	{
	case OT_FLOAT:
		{
			return CScriptArgument::ArgumentType::ST_FLOAT;
		}
	case OT_INTEGER:
		{
			return CScriptArgument::ArgumentType::ST_INTEGER;
		}
	case OT_BOOL:
		{
			return CScriptArgument::ArgumentType::ST_BOOL;
		}
	case OT_STRING:
		{
			return CScriptArgument::ArgumentType::ST_STRING;
		}
	case OT_TABLE:
		{
			return CScriptArgument::ArgumentType::ST_TABLE;
		}	
	case OT_ARRAY:
		{
			return CScriptArgument::ArgumentType::ST_ARRAY;
		}
	case OT_NULL:
	default:
		return CScriptArgument::ArgumentType::ST_INVALID;
	}
}