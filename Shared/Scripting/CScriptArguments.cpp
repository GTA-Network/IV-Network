//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CScriptArguments.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CScriptArguments.h"
#include "CScriptArgument.h"
#include "CScriptVM.h"

CScriptArguments::~CScriptArguments()
{
	reset();
}

CScriptArguments::CScriptArguments()
{
	reset();
}

void CScriptArguments::reset()
{
	for(auto pArgument : m_Arguments)
		delete pArgument;

	m_Arguments.clear();
}

CScriptArguments::CScriptArguments(const CScriptArguments& p)
{
	for(auto pArgument : p.m_Arguments)
		m_Arguments.push_back(new CScriptArgument(*pArgument));
}

void CScriptArguments::push(const CScriptArgument &arg)
{
	m_Arguments.push_back(new CScriptArgument(arg));
}

void CScriptArguments::push(int i)
{
	m_Arguments.push_back(new CScriptArgument(i));
}

void CScriptArguments::push(bool b)
{
	m_Arguments.push_back(new CScriptArgument(b));
}

void CScriptArguments::push(float f)
{
	m_Arguments.push_back(new CScriptArgument(f));
}

void CScriptArguments::push(const char* c)
{
	m_Arguments.push_back(new CScriptArgument(CString(c)));
}

void CScriptArguments::push(CString str)
{
	m_Arguments.push_back(new CScriptArgument(CString(str)));
}

void CScriptArguments::push(const CScriptArguments &array, bool isArray)
{
	m_Arguments.push_back(new CScriptArgument(array, isArray));
}

void CScriptArguments::push(CScriptArguments* pArray, bool isArray)
{
	m_Arguments.push_back(new CScriptArgument(*pArray, isArray));
}


void CScriptArguments::push(CScriptEntity* pEntity)
{
	m_Arguments.push_back(new CScriptArgument(pEntity));
}

void CScriptArguments::pushVector3(const CVector3 &vec3)
{
	m_Arguments.push_back(new CScriptArgument(vec3.fX));
	m_Arguments.push_back(new CScriptArgument(vec3.fY));
	m_Arguments.push_back(new CScriptArgument(vec3.fZ));
}