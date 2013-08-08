//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrelArgument.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSquirrelArgument.h"
#include <assert.h>
#include <Squirrel/squirrel.h>
#include <Squirrel/sqobject.h>
#include <Squirrel/sqstring.h>

CSquirrelArgument::CSquirrelArgument(CSquirrelArguments* pArray, bool isArray)
{
	type = isArray ? OT_ARRAY : OT_TABLE;
	data.pArray=pArray;
}

CSquirrelArgument::CSquirrelArgument(SQObject o)
{
	type = o._type;

	switch(type)
	{
	case OT_INTEGER:
		data.i = o._unVal.nInteger;
		break;
	case OT_BOOL:
		data.b = (o._unVal.nInteger != 0);
		break;
	case OT_FLOAT:
		data.f = o._unVal.fFloat;
		break;
	case OT_STRING:
		data.str = new CString(o._unVal.pString->_val);
		break;
	case OT_NATIVECLOSURE:
	case OT_CLOSURE:
		data.sqObject = o;
		break;
	case OT_INSTANCE:
		data.pInstance = o._unVal.pInstance;
		break;
	}
}

CSquirrelArgument::~CSquirrelArgument()
{
	if(type == OT_STRING)
		delete data.str;
	else if(type == OT_ARRAY || type == OT_TABLE)
		delete data.pArray;
}


bool CSquirrelArgument::push(SQVM* pVM)
{
	switch(type)
	{
		case OT_NULL:
			sq_pushnull(pVM);
			break;
		case OT_INTEGER:
			sq_pushinteger(pVM, data.i);
			break;
		case OT_BOOL:
			sq_pushbool(pVM, data.b);
			break;
		case OT_FLOAT:
			sq_pushfloat(pVM, data.f);
			break;
		case OT_STRING:
			sq_pushstring(pVM, data.str->Get(), data.str->GetLength());
			break;
		case OT_ARRAY:
			{
				sq_newarray(pVM, 0);

				for(auto pArgument : *data.pArray->GetArguments())
				{
					pArgument->push(pVM);
					sq_arrayappend(pVM, -2);
				}
				break;
			}
		case OT_TABLE:
			{
				sq_newtable(pVM);

				int i = 0;
				assert( data.pArray->GetArguments()->size() % 2 == 0 );
				for(auto iter = data.pArray->GetArguments()->begin(); iter != data.pArray->GetArguments()->end(); ++ iter, ++ i )
				{
					(*iter)->push(pVM);
					++ iter;
					(*iter)->push(pVM);
					sq_createslot(pVM, -3);
				}
				break;
			}
			break;
		default:
			sq_pushnull(pVM); // table, whatsoever. do not even care. fix it if you dare.
			assert(0);
			return false;
	}
	return true;
}

//==========================================================================

void CSquirrelArguments::push_to_vm(SQVM* pVM)
{
	for(auto iter = m_pArguments->begin(); iter != m_pArguments->end(); ++ iter)
	{
		(*iter)->push(pVM);
	}
}

void CSquirrelArguments::push()
{
	m_pArguments->push_back(new CSquirrelArgument());
}

void CSquirrelArguments::push(int i)
{
	m_pArguments->push_back(new CSquirrelArgument(i));
}

void CSquirrelArguments::push(bool b)
{
	m_pArguments->push_back(new CSquirrelArgument(b));
}

void CSquirrelArguments::push(float f)
{
	m_pArguments->push_back(new CSquirrelArgument(f));
}

void CSquirrelArguments::push(const char* c)
{
	m_pArguments->push_back(new CSquirrelArgument(new CString(c)));
}

void CSquirrelArguments::push(CString str)
{
	m_pArguments->push_back(new CSquirrelArgument(new CString(str)));
}

void CSquirrelArguments::push(CVector3 vec)
{
	m_pArguments->push_back(new CSquirrelArgument(vec.fX));
	m_pArguments->push_back(new CSquirrelArgument(vec.fY));
	m_pArguments->push_back(new CSquirrelArgument(vec.fZ));
}

void CSquirrelArguments::push(CSquirrelArguments* pArray, bool isArray)
{
	m_pArguments->push_back(new CSquirrelArgument(pArray, isArray));
}

bool CSquirrelArguments::pushFromStack(SQVM* pVM, int idx)
{
	switch(sq_gettype(pVM,idx))
	{
		case OT_NULL:
			push();
			break;
		case OT_INTEGER:
			{
				int i;
				sq_getinteger(pVM, idx, &i);
				push(i);
			}
			break;
		case OT_BOOL:
			{
				SQBool b;
				sq_getbool(pVM, idx, &b);
				push(b!=0);
			}
			break;
		case OT_FLOAT:
			{
				float f;
				sq_getfloat(pVM, idx, &f);
				push(f);
			}
			break;
		case OT_STRING:
			{
				const char* szTemp;
				sq_getstring(pVM, idx, &szTemp);
				push(szTemp);
			}
			break;
		case OT_TABLE:
			{
				CSquirrelArguments* pArguments = new CSquirrelArguments();
				
				sq_push(pVM, idx);
				sq_pushnull(pVM);

				while(SQ_SUCCEEDED(sq_next(pVM,-2)))
				{
					if(!pArguments->pushFromStack(pVM, -2) || !pArguments->pushFromStack(pVM,-1))
					{
						sq_pop(pVM,4);
						delete pArguments;
						return false;
					}
					sq_pop(pVM,2);
				}
				sq_pop(pVM,2);

				push(pArguments, false);
				break;
			}
		case OT_ARRAY:
			{
				CSquirrelArguments* pArguments = new CSquirrelArguments();
				
				sq_push(pVM, idx);
				sq_pushnull(pVM);

				while(SQ_SUCCEEDED(sq_next(pVM,-2)))
				{
					if(!pArguments->pushFromStack(pVM,-1))
					{
						sq_pop(pVM,4);
						delete pArguments;
						return false;
					}
					sq_pop(pVM,2);
				}
				sq_pop(pVM,2);

				push(pArguments, true);
				break;
			}
		default:
			return false;
	}
	return true;
}

void CSquirrelArguments::pushFromStack(SQVM* pVM, int startidx, int count)
{
	for(int i = startidx; i < count; i++)
	{
		pushFromStack(pVM, i);
	}
}