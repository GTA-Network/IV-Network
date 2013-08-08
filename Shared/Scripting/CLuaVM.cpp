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

CLuaVM::CLuaVM()
	: CScriptVM()
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

	return false;
}

bool CLuaVM::LoadScripts(std::list<CScript> scripts)
{

	return false;
}

void CLuaVM::RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount, const char* szFunctionTemplate, bool bPushRootTable)
{
	lua_register(m_pVM, szFunctionName, (lua_CFunction)pfnFunction);
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
		size_t length;
		str.Set(lua_tolstring(m_pVM, m_iStackIndex++, &length), length);
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
		size_t length;
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
