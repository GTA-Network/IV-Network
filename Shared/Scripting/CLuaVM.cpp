//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
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

CLuaVM::CLuaVM(CResource* pResource)
	: CScriptVM(pResource),
	m_bRegisterClass(false)
{
	m_pVM = luaL_newstate();
	luaL_openlibs(m_pVM);
}

CLuaVM::~CLuaVM()
{
	lua_close(m_pVM);
	m_pVM = NULL;

}

bool CLuaVM::LoadScript(CString script)
{
		CString scriptPath( "%s/%s", GetResource()->GetResourceDirectoryPath().Get(), script.Get());
	
	if(!SharedUtility::Exists(script.Get()) && luaL_loadfile(m_pVM, scriptPath.Get()) != 0)
	{
		CLogFile::Printf("[%s] Failed to load file %s.", GetResource()->GetName().Get(), script.Get());
		return false;
	} else {
		if(lua_pcall(m_pVM, 0, LUA_MULTRET, 0) == 0)
			CLogFile::Printf("\t[%s] Loaded file %s.", GetResource()->GetName().Get(), script.Get());
		return true;
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

void CLuaVM::RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount, const char* szFunctionTemplate, bool bPushRootTable)
{
	if(!m_bRegisterClass)
	{
		lua_register(m_pVM, szFunctionName, (lua_CFunction)pfnFunction);
	}
	else
	{
		lua_pushstring(m_pVM, "__class");
        lua_rawget(m_pVM, -2);

        lua_pushstring(m_pVM, szFunctionName);
        lua_pushstring(m_pVM, szFunctionName);
        lua_pushcclosure(m_pVM, (lua_CFunction)pfnFunction, 1);
        lua_rawset(m_pVM, -3);

        lua_pop(m_pVM, 1);
	}
}

void CLuaVM::RegisterClassStart(const char* className, const char* baseClass)
{
	m_strClassName = className;
	lua_pushstring(m_pVM, "mt");
    lua_newtable(m_pVM);
    lua_rawset(m_pVM, LUA_REGISTRYINDEX);

    lua_pushstring(m_pVM, "ud");
    lua_newtable(m_pVM );
    lua_rawset(m_pVM, LUA_REGISTRYINDEX);

	lua_newtable ( m_pVM );

    lua_pushstring(m_pVM, "__class");
    lua_newtable( m_pVM);
    lua_rawset(m_pVM, -3);

    lua_pushstring(m_pVM, "__get");
    lua_newtable(m_pVM);
    lua_rawset(m_pVM, -3);

    lua_pushstring(m_pVM, "__set");
    lua_newtable(m_pVM);
    lua_rawset(m_pVM, -3);

	m_bRegisterClass = true;
}

void CLuaVM::RegisterClassFinish()
{
	lua_pushstring(m_pVM, "mt");
	lua_rawget(m_pVM, LUA_REGISTRYINDEX);

	// store in registry
	lua_pushvalue(m_pVM, -2);
	lua_setfield(m_pVM, -2, m_strClassName.Get());

	lua_pop(m_pVM, 1);

	// register with environment
	lua_getfield(m_pVM, -1, "__class");
	lua_setglobal(m_pVM, m_strClassName.Get());

	lua_pop(m_pVM, 1);

	m_bRegisterClass = false;
}

void CLuaVM::PopBool(bool& b)
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

void CLuaVM::PopBool(bool& b, bool bDefaultValue)
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

void CLuaVM::PopInteger(int& i)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TBOOLEAN)
	{
		i = static_cast<int>(lua_tointeger(m_pVM, m_iStackIndex++));
		return;
	}

	i = 0;
	m_iStackIndex++;
}

void CLuaVM::PopInteger(int& i, int iDefaultValue)
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

void CLuaVM::PopFloat(float& f)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		f = static_cast<float>(lua_tointeger(m_pVM, m_iStackIndex++));
		return;
	}

	f = 0;
	m_iStackIndex++;
}

void CLuaVM::PopFloat(float& f, float fDefaultValue)
{
	int argType = lua_type(m_pVM, m_iStackIndex);
	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	{
		f = static_cast<int>(lua_tointeger(m_pVM, m_iStackIndex++));
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

void CLuaVM::PopString(CString& str)
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

void CLuaVM::PopString(CString& str, CString strDefaultValue)
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

void CLuaVM::PopVector(CVector3& vec)
{
	PopFloat(vec.fX);
	PopFloat(vec.fY);
	PopFloat(vec.fZ);
}

void CLuaVM::PopVector(CVector3& vec, CVector3 vecDefaultValue)
{
	PopFloat(vec.fX, vecDefaultValue.fX);
	PopFloat(vec.fY, vecDefaultValue.fY);
	PopFloat(vec.fZ, vecDefaultValue.fZ);
}

void CLuaVM::PushBool(const bool& b)
{
	lua_pushboolean(m_pVM, b);
}

void CLuaVM::PushInteger(const int& i)
{
	lua_pushinteger(m_pVM, i);
}

void CLuaVM::PushFloat(const float& f)
{
	lua_pushnumber(m_pVM, f);
}

void CLuaVM::PushString(const CString& str)
{
	lua_pushstring(m_pVM, str.Get());
}

void CLuaVM::PushVector(const CVector3& vec)
{
	PushFloat(vec.fX);
	PushFloat(vec.fY);
	PushFloat(vec.fZ);
}
