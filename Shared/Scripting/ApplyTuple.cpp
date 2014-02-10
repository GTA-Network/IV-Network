#include "ApplyTuple.h"

#include "CLuaVM.h"
#include "CSquirrelVM.h"


#ifndef _CLIENT
#include "../Server/Entity/CVehicleEntity.h"
#endif

template<>
int getValue<int>(IScriptVM* pVM, int idx)
{
	int v;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	pVM->Pop(v);
	return v;
}

template<>
double getValue<double>(IScriptVM* pVM, int idx)
{
	float f;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ?  0 : 1));
	pVM->Pop(f);
	return f;
}

template<>
float getValue<float>(IScriptVM* pVM, int idx)
{
	float f;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	pVM->Pop(f);
	return f;
}

template<>
DWORD getValue<DWORD>(IScriptVM* pVM, int idx)
{
	DWORD dw = 0;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	pVM->Pop(dw);
	printf("Warning: not sure if this goes right [%s]\n", __FUNCSIG__);
	return dw;
}

template<>
bool getValue<bool>(IScriptVM* pVM, int idx)
{
	bool b;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	pVM->Pop(b);
	return b;
}

template<>
char getValue<char>(IScriptVM* pVM, int idx)
{
	printf("Warning: unable to pop this type [%s]\n", __FUNCSIG__);
	return 0;
}

template<>
unsigned int getValue<unsigned int>(IScriptVM* pVM, int idx)
{
	unsigned int ui = 0;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	//pVM->Pop(ui);
	printf("Warning: unable to pop this type [%s]\n", __FUNCSIG__);
	return ui;
}

template<>
const char *getValue<const char *>(IScriptVM* pVM, int idx)
{
	CString str;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	pVM->Pop(str);
	const char* sz = (char*)malloc(str.GetLength()+1);
	memset((void*)sz, 0, str.GetLength()+1);
	memcpy((void*)sz, (void*)str.Get(), str.GetLength());
	return sz;
}

template<>
CString getValue<CString>(IScriptVM* pVM, int idx)
{
	CString str;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	pVM->Pop(str);
	return str;
}


template<>
stScriptFunction getValue<stScriptFunction>(IScriptVM* pVM, int idx)
{
	stScriptFunction function;
	pVM->Pop(function);
	return function;
}

template<>
void returnValue(IScriptVM* pVM, int v)
{
	pVM->Push(v);
}

template<>
void returnValue(IScriptVM* pVM, double v)
{
	pVM->Push((float) v);
}

template<>
void returnValue(IScriptVM* pVM, float v)
{
	pVM->Push(v);
}

template<>
void returnValue(IScriptVM* pVM, unsigned int v)
{
	printf("Warning: unable to push this type [%s]\n", __FUNCSIG__);
}

template<>
void returnValue(IScriptVM* pVM, const char *v)
{
	pVM->Push(CString(v));
}

template<>
void returnValue(IScriptVM* pVM, CString v)
{
	pVM->Push(v);
}

template<>
void returnValue(IScriptVM* pVM, char v)
{
	printf("Warning: unable to push this type [%s]\n", __FUNCSIG__);
}

template<>
void returnValue(IScriptVM * pVM, DWORD v)
{
	pVM->Push((int) v);
}

template<>
void returnValue(IScriptVM * pVM, CVector3 v)
{
	CScriptArguments vec;
	vec.push(v.fX);
	vec.push(v.fY);
	vec.push(v.fZ);
	pVM->PushArray(vec);
}

template<>
void returnValue(IScriptVM* pVM, bool v)
{
	pVM->Push(v);
}

#ifndef _CLIENT
template<>
void returnValue(IScriptVM* pVM, CVehicleEntity* v)
{
	if (v)
	{
		pVM->PushInstance(v->GetScriptVehicle()->GetScriptClassName(), v->GetScriptVehicle());
	}
	else
	{
		pVM->Push(false);
	}
}
#endif

template<class T>
void returnValue(IScriptVM* pVM, T *v)
{
	printf("Warning: unable to push this type [%s]\n", __FUNCSIG__);
}


template<class T>
void returnValue(IScriptVM* pVM, T v)
{
	printf("Warning: unable to push this type [%s]\n", __FUNCSIG__);
}