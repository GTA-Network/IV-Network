//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrelScriptArgument.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSquirrelScriptArgument.h"
#include <assert.h>

CSquirrelScriptArgument::CSquirrelScriptArgument()
	: CScriptArgument()
{

}

CSquirrelScriptArgument::~CSquirrelScriptArgument()
{

}


bool CSquirrelScriptArgument::push(SQVM * pVM)
{
	switch(GetType())
	{
		case ST_NULL:
			sq_pushnull(pVM);
			break;
		case ST_INTEGER:
			sq_pushinteger(pVM, GetInteger());
			break;
		case ST_BOOL:
			sq_pushbool(pVM, GetBool());
			break;
		case ST_FLOAT:
			sq_pushfloat(pVM, GetFloat());
			break;
		case ST_STRING:
			sq_pushstring(pVM, GetString()->Get(), GetString()->GetLength());
			break;
		case ST_ARRAY:
			{
				/*sq_newarray(pVM, 0);

				for(CSquirrelArguments::iterator iter = data.pArray->begin(); iter != data.pArray->end(); iter++)
				{
					(*iter)->push(pVM);
					sq_arrayappend(pVM, -2);
				}*/
				break;
			}
		case ST_TABLE:
			{
				/*assert(data.pArray->size() % 2 == 0);
				sq_newtable(pVM);

				for(CSquirrelArguments::iterator iter = data.pArray->begin(); iter != data.pArray->end(); iter++)
				{
					(*iter)->push(pVM);
					++iter;
					(*iter)->push(pVM);
					sq_createslot(pVM, -3);
				}*/
				break;
			}
			break;
		//case ST_CLOSURE:
		//case ST_NATIVECLOSURE:
		//	//sq_pushobject(pVM, data.sqObject);
		//	break;
		//case ST_INSTANCE:
		//	{
		//		/*SQObject obj;
		//		obj._type = OT_INSTANCE;
		//		obj._unVal.pInstance = data.pInstance;
		//		sq_pushobject(pVM, obj);*/
		//	}
		//	break;
		default:
			sq_pushnull(pVM);
			assert(0);
			return false;
	}
	return true;
}