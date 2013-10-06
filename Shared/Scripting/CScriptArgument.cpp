//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
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

#include "../Server/Entity/Entities.h"

CScriptArgument::~CScriptArgument()
{
	reset();
}

CScriptArgument::CScriptArgument(const CScriptArgument& p)
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
	case CScriptArgument::ArgumentType::ST_ENTITY:
		{
			pVM->PushInstance(data.pEntity->GetScriptClassName(), data.pEntity);
		}
		break;
	default:
		assert(0);
		break;
	};
}


void CScriptArgument::set(const CScriptArgument& p)
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



bool CScriptArgument::pushFromStack(CScriptVM * pVM, int idx)
{
	pVM->SetStackIndex(idx);
	switch(pVM->GetType(idx))
	{
	case CScriptArgument::ArgumentType::ST_FLOAT:
		{
			pVM->Pop(data.f);
			m_eType = CScriptArgument::ArgumentType::ST_FLOAT;
		}
		break;
	case CScriptArgument::ArgumentType::ST_INTEGER:
		{
			pVM->Pop(data.i);
			m_eType = CScriptArgument::ArgumentType::ST_INTEGER;
		}
		break;
	case CScriptArgument::ArgumentType::ST_BOOL:
		{
			pVM->Pop(data.b);
			m_eType = CScriptArgument::ArgumentType::ST_BOOL;
		}
		break;
	case CScriptArgument::ArgumentType::ST_STRING:
		{
			CString str;
			pVM->Pop(str);
			SetString(str);
			m_eType = CScriptArgument::ArgumentType::ST_STRING;
		}
		break;
	case CScriptArgument::ArgumentType::ST_TABLE:
		{
			CScriptArguments table;
			pVM->PopTable(table);
			SetTable(&table);
			m_eType = CScriptArgument::ArgumentType::ST_TABLE;
		}	
		break;
	case CScriptArgument::ArgumentType::ST_ARRAY:
		{
			m_eType = CScriptArgument::ArgumentType::ST_ARRAY;
		}
		break;
	case CScriptArgument::ArgumentType::ST_INVALID:
	default:
		{
			pVM->ResetStackIndex();
			reset();
			return false;
		}
	}
	pVM->ResetStackIndex();
	return true;
}