//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CLuaVM.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CLuaVM.h"
#include <lua/lua.hpp>
#include <SharedUtility.h>
#include <CLogFile.h>
#include "CScriptArgument.h"
#include "CScriptClass.h"

CLuaVM::CLuaVM(CResource* pResource)
	: IScriptVM(pResource),
	m_iStackIndex(1)
{
	m_pVM = luaL_newstate();
	luaL_openlibs(m_pVM);
}

CLuaVM::~CLuaVM()
{
	lua_close(m_pVM);
	m_pVM = NULL;

}

class Foo
{
public:
	Foo() { printf("hallo"); }
	Foo(int i) { printf("ctor! %i\n", i); }
	~Foo();

	int abc(int a, int b, int c) { printf("%i:%i:%i\n", a, b, c); return 143; }
	static void aaa() { printf("aaa!\n"); }
};

int LuaErrorReport(lua_State * L, int status)
{
	if (status && !lua_isnil(L, -1))
	{
		const char* msg = lua_tostring(L, -1);
		if (msg)
		{
			lua_getfield(L, LUA_RIDX_GLOBALS, "debug");
			if (!lua_istable(L, -1))
			{
				lua_pop(L, 1);
				return 1;
			}
			lua_getfield(L, -1, "traceback");
			if (!lua_isfunction(L, -1))
			{
				lua_pop(L, 1);
				return 1;
			}

			lua_pushvalue(L, 1);
			lua_pushinteger(L, 2);
			lua_call(L, 2, 1);

			printf("[LUA] Error: %s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
		
	}
	return 0;
}
#include <vector>

auto split(const std::string& value, char separator)
-> std::vector<std::string>
{
	std::vector<std::string> result;
	std::string::size_type p = 0;
	std::string::size_type q;
	while ((q = value.find(separator, p)) != std::string::npos) {
		result.emplace_back(value, p, q - p);
		p = q + 1;
	}
	result.emplace_back(value, p);
	return result;
}

bool CLuaVM::LoadScript(CString script)
{
	(new CScriptClass<Foo>("Foo"))->AddMethod("abc", &Foo::abc).AddMethod("new", &Foo::abc).Register(this);
	CString scriptPath( "%s/%s", GetResource()->GetResourceDirectoryPath().Get(), script.Get());
	
	if(!SharedUtility::Exists(script.Get()) && luaL_loadfile(m_pVM, scriptPath.Get()) != 0)
	{
		CLogFile::Printf("[%s] Failed to load file %s.", GetResource()->GetName().Get(), script.Get());
		return false;
	} 
	else 
	{
		if (lua_pcall(m_pVM, 0, LUA_MULTRET, 0) == 0)
		{
			CLogFile::Printf("\t[%s] Loaded file %s.", GetResource()->GetName().Get(), script.Get());
			return true;
		}
		else
		{
			std::string strRes = lua_tostring(m_pVM, -1);

			std::vector <std::string> vecSplit;
			vecSplit = split(strRes, ':');

			if (vecSplit.size() >= 3)
			{
				std::string strFile = vecSplit[0];
				int     iLine = atoi(vecSplit[1].c_str());
				std::string strMsg = vecSplit[2].substr(1);

				CLogFile::Printf("ERROR: %s:%d: %s", strFile.c_str(), iLine, strMsg.c_str());
			}
			else
			{
				CLogFile::Printf(strRes.c_str());
			}
		}
	}
	CLogFile::Printf("[%s] Failed to load file %s.", GetResource()->GetName().Get(), script.Get());
	return false;
}

bool CLuaVM::LoadScripts(std::list<CScript> scripts)
{
	for(auto Script : scripts)
		if (Script.GetType() != CLIENT_SCRIPT)
			if (!LoadScript(Script.GetScriptFileName()))
				return false;

	return true;
}
int iFuncIndex = 1;
void CLuaVM::RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount, const char* szFunctionTemplate, bool bPushRootTable)
{
	lua_register(m_pVM, szFunctionName, (lua_CFunction)pfnFunction);
}

static int gc_obj(lua_State *L) {
	CLogFile::Printf("Delete class");
	return 0;
}
static int clsIndex = 0;
int metatable = 0;
void CLuaVM::BeginRegisterScriptClass(const char* className, scriptFunction pfnFunction, void* userPointer, const char* baseClass)
{
	m_strClassName = className;

	lua_pushcclosure(m_pVM, (lua_CFunction)pfnFunction, 1);
	lua_setglobal(m_pVM, m_strClassName.Get());

	luaL_newmetatable(m_pVM, className);
	metatable = lua_gettop(m_pVM);

	lua_pushstring(m_pVM, "__gc");
	lua_pushcfunction(m_pVM, gc_obj);
	lua_settable(m_pVM, metatable);

	iFuncIndex = 0;
}

void CLuaVM::SetClassInstance(const char* szClassName, void * pInstance)
{
	void** a = (void**)lua_newuserdata(m_pVM, sizeof(int*));
	*a = pInstance;
	luaL_getmetatable(m_pVM, szClassName);
	lua_setmetatable(m_pVM, -2);
}

void * CLuaVM::GetClassInstance(const char* szClassName)
{
	return (void*)*(int**)lua_touserdata(m_pVM,  lua_upvalueindex(1));
}


void * CLuaVM::GetUserData(int idx)
{
	return (void*)lua_touserdata(m_pVM, idx);
}

void CLuaVM::RegisterClassFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount, const char* szFunctionTemplate)
{
	lua_pushstring(m_pVM, szFunctionName);
	lua_pushlightuserdata(m_pVM, this);
	lua_pushcclosure(m_pVM, (lua_CFunction)pfnFunction, 1);
	lua_settable(m_pVM, metatable);
}

void CLuaVM::FinishRegisterScriptClass()
{

}

void CLuaVM::Pop(bool& b)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TBOOLEAN)
	{
		b = lua_toboolean (m_pVM, m_iStackIndex++) ? true : false;
		return;
	}

	b = false;
	m_iStackIndex++;
}

void CLuaVM::Pop(bool& b, bool bDefaultValue)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TBOOLEAN)
	{
		b = lua_toboolean(m_pVM, m_iStackIndex++) ? true : false;
		return;
	} else {
		if(argType == LUA_TNONE || argType == LUA_TNIL)
		{
			b = bDefaultValue;
			m_iStackIndex++;
			return;
		}
	}
	b = false;
	m_iStackIndex++;
}

void CLuaVM::Pop(int& i)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		i = static_cast<int>(lua_tointeger(m_pVM, m_iStackIndex++));
		return;
	}

	i = 0;
	m_iStackIndex++;
}

void CLuaVM::Pop(int& i, int iDefaultValue)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		i = static_cast<int>(lua_tointeger(m_pVM, m_iStackIndex++));
		return;
	} else {
		if(argType == LUA_TNONE || argType == LUA_TNIL)
		{
			i = iDefaultValue;
		}
	}

	i = 0;
	m_iStackIndex++;
}

void CLuaVM::Pop(unsigned int& i)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		i = static_cast<unsigned int>(lua_tointeger(m_pVM, m_iStackIndex++));
		return;
	}

	i = 0;
	m_iStackIndex++;
}

void CLuaVM::Pop(unsigned int& i, unsigned int iDefaultValue)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		i = static_cast<int>(lua_tointeger(m_pVM, m_iStackIndex++));
		return;
	}
	else {
		if (argType == LUA_TNONE || argType == LUA_TNIL)
		{
			i = iDefaultValue;
		}
	}

	i = 0;
	m_iStackIndex++;
}

void CLuaVM::Pop(long& i)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		i = static_cast<long>(lua_tointeger(m_pVM, m_iStackIndex++));
		return;
	}

	i = 0;
	m_iStackIndex++;
}

void CLuaVM::Pop(long& i, long iDefaultValue)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		i = static_cast<int>(lua_tointeger(m_pVM, m_iStackIndex++));
		return;
	}
	else {
		if (argType == LUA_TNONE || argType == LUA_TNIL)
		{
			i = iDefaultValue;
		}
	}

	i = 0;
	m_iStackIndex++;
}

void CLuaVM::Pop(unsigned long& i)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		i = static_cast<unsigned long>(lua_tointeger(m_pVM, m_iStackIndex++));
		return;
	}

	i = 0;
	m_iStackIndex++;
}

void CLuaVM::Pop(unsigned long& i, unsigned long iDefaultValue)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		i = static_cast<int>(lua_tointeger(m_pVM, m_iStackIndex++));
		return;
	}
	else {
		if (argType == LUA_TNONE || argType == LUA_TNIL)
		{
			i = iDefaultValue;
		}
	}

	i = 0;
	m_iStackIndex++;
}

void CLuaVM::Pop(float& f)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		f = static_cast<float>(lua_tonumber(m_pVM, m_iStackIndex++));
		return;
	}

	f = 0;
	m_iStackIndex++;
}

void CLuaVM::Pop(float& f, float fDefaultValue)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		f = static_cast<int>(lua_tonumber(m_pVM, m_iStackIndex++));
		return;
	} else {
		if(argType == LUA_TNONE || argType == LUA_TNIL)
		{
			f = fDefaultValue;
		}
	}

	f = 0;
	m_iStackIndex++;
}

void CLuaVM::Pop(stScriptFunction &function)
{
	function.ref = -1;
	function.function = 0;
	if (lua_isfunction(m_pVM, m_iStackIndex++))
	{
		function.ref = luaL_ref(m_pVM, LUA_REGISTRYINDEX);
	}
	function.type = eFType::LUA_FUNCTION;
}

void CLuaVM::Pop(CString& str)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if(argType == LUA_TSTRING || argType == LUA_TNUMBER)
	{
		size_t length = 0;
		const char* szTmp = lua_tolstring(m_pVM, m_iStackIndex++, &length);
		str = szTmp;
		return;
	}

	str = "";
	m_iStackIndex++;
}

void CLuaVM::Pop(CString& str, CString strDefaultValue)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if(argType == LUA_TSTRING || argType == LUA_TNUMBER)
	{
		size_t length = 0;
		str.Set(lua_tolstring(m_pVM, m_iStackIndex++, &length), length);
		return;
	} else {
		if(argType == LUA_TNONE || argType == LUA_TNIL)
		{
			str = strDefaultValue;              
			m_iStackIndex++;
			return;
		}
	}

	str = "";
	m_iStackIndex++;
}

void CLuaVM::Pop(CVector3& vec)
{
	Pop(vec.fX);
	Pop(vec.fY);
	Pop(vec.fZ);
}

void CLuaVM::Pop(CVector3& vec, CVector3 vecDefaultValue)
{
	Pop(vec.fX, vecDefaultValue.fX);
	Pop(vec.fY, vecDefaultValue.fY);
	Pop(vec.fZ, vecDefaultValue.fZ);
}

void CLuaVM::Push(const bool& b)
{
	lua_pushboolean(m_pVM, b);
}

void CLuaVM::Push(const int& i)
{
	lua_pushinteger(m_pVM, i);
}

void CLuaVM::Push(const unsigned int& i)
{
	lua_pushinteger(m_pVM, i);
}

void CLuaVM::Push(const long& i)
{
	lua_pushinteger(m_pVM, i);
}

void CLuaVM::Push(const unsigned long& i)
{
	lua_pushinteger(m_pVM, i);
}

void CLuaVM::Push(const float& f)
{
	lua_pushnumber(m_pVM, f);
}

void CLuaVM::Push(const CString& str)
{
	lua_pushstring(m_pVM, str.Get());
}

void CLuaVM::Push(const CVector3& vec)
{
	Push(vec.fX);
	Push(vec.fY);
	Push(vec.fZ);
}

void CLuaVM::PushArray(const CScriptArguments &array)
{
	int index = 0;
	lua_newtable(m_pVM); 
	for(auto pArgument : array.m_Arguments)
	{
		lua_pushnumber(m_pVM, index);
		pArgument->Push(this);
		lua_settable(m_pVM, -3);
		index++;
	}
}

void CLuaVM::PushTable(const CScriptArguments &table)
{
	int index = 0;
	lua_newtable(m_pVM); 
	for(auto iter = table.m_Arguments.begin(); iter != table.m_Arguments.end(); iter++)
	{
		(*iter)->Push(this);
		++iter;
		(*iter)->Push(this);
		lua_settable(m_pVM, -3);
	}
}

CScriptArgument::ArgumentType CLuaVM::GetType(int idx)
{
	lua_State* VM = reinterpret_cast<CLuaVM*>(this)->GetVM();
	int lua_t = lua_type(VM, idx);
	switch(lua_t)
	{
	case LUA_TNUMBER:
		{
			if(lua_isnumber(VM, idx))
				return CScriptArgument::ArgumentType::ST_FLOAT;
			else
				return CScriptArgument::ArgumentType::ST_INTEGER;
		}
	case LUA_TBOOLEAN:
		{
			return CScriptArgument::ArgumentType::ST_BOOL;
		}
	case LUA_TSTRING:
		{
			return CScriptArgument::ArgumentType::ST_STRING;
		}
	case LUA_TTABLE:
		{
			return CScriptArgument::ArgumentType::ST_TABLE;
		}	
	case LUA_TNIL:
	default:
		return CScriptArgument::ArgumentType::ST_INVALID;
	}
}