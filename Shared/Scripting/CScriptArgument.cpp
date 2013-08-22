//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CScriptArgument.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CScriptArgument.h"
#include "CScriptVM.h"
#include <assert.h>

CScriptArgument::~CScriptArgument()
{
	reset();
}

CScriptArgument::CScriptArgument(CScriptArgument& p)
{
	set(p);
}

void CScriptArgument::reset()
{
	if(m_eType == ST_STRING)
		delete data.str;
	else if(m_eType == ST_ARRAY || m_eType == ST_TABLE)
		delete data.pArray;

	m_eType = ST_INVALID;
}


void CScriptArgument::Push(CScriptVM * pVM)
{
	switch(GetType())
	{
	case CScriptArgument::ArgumentType::ST_INTEGER:
		{
			pVM->Push(GetInteger());
		}
		break;
	case CScriptArgument::ArgumentType::ST_BOOL:
		{
			pVM->Push(GetBool());
		}
		break;
	case CScriptArgument::ArgumentType::ST_FLOAT:
		{
			pVM->Push(GetFloat());
		}
		break;
	case CScriptArgument::ArgumentType::ST_STRING:
		{
			pVM->Push(CString(GetString()));
		}
		break;
	case CScriptArgument::ArgumentType::ST_ARRAY:
		{
			pVM->PushArray(*GetArray());
		}
		break;
	case CScriptArgument::ArgumentType::ST_TABLE:
		{
			pVM->PushTable(*GetTable());
		}
		break;
	default:
		assert(0);
		break;
	};
}


void CScriptArgument::set(CScriptArgument& p)
{
	m_eType = p.GetType();

	switch(m_eType)
	{
	case ST_INVALID:
		break;
	case ST_INTEGER:
		data.i = p.data.i;
		break;
	case ST_BOOL:
		data.b = p.data.b;
		break;
	case ST_FLOAT:
		data.f = p.data.f;
		break;
	case ST_STRING:
		data.str = new CString(p.data.str->Get());
		break;
	case ST_ARRAY:
	case ST_TABLE:
		data.pArray = new CScriptArguments(*p.data.pArray);
		break;
	}
}