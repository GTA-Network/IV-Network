#include "ApplyTuple.h"

template<>
int getValue<int>(CScriptVM* pVM, int idx)
{
	int v;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	pVM->Pop(v);
	return v;
}

template<>
double getValue<double>(CScriptVM* pVM, int idx)
{
	float f;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ?  0 : 1));
	pVM->Pop(f);
	return f;
}

template<>
float getValue<float>(CScriptVM* pVM, int idx)
{
	float f;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	pVM->Pop(f);
	return f;
}

template<>
DWORD getValue<DWORD>(CScriptVM* pVM, int idx)
{
	DWORD dw = 0;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	//pVM->Pop(dw);
	printf("Warning: unable to pop this type [%s]", __FUNCTION__);
	return dw;
}

template<>
bool getValue<bool>(CScriptVM* pVM, int idx)
{
	bool b;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	pVM->Pop(b);
	return b;
}

template<>
unsigned int getValue<unsigned int>(CScriptVM* pVM, int idx)
{
	unsigned int ui = 0;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	//pVM->Pop(ui);
	printf("Warning: unable to pop this type [%s]", __FUNCTION__);
	return ui;
}

template<>
const char *getValue<const char *>(CScriptVM* pVM, int idx)
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
void returnValue(CScriptVM* pVM, int v)
{
	pVM->Push(v);
}

template<>
void returnValue(CScriptVM* pVM, double v)
{
	pVM->Push((float) v);
}

template<>
void returnValue(CScriptVM* pVM, float v)
{
	pVM->Push(v);
}

template<>
void returnValue(CScriptVM* pVM, const char *v)
{
	pVM->Push(CString(v));
}

template<class T>
void returnValue(CScriptVM* pVM, T *v)
{

}


template<class T>
void returnValue(CScriptVM* pVM, T v)
{

}