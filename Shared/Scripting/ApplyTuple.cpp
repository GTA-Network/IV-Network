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
const char *getValue<const char *>(CScriptVM* pVM, int idx)
{
	CString str;
	pVM->SetStackIndex(idx - (pVM->GetVMType() == LUA_VM ? 0 : 1));
	pVM->Pop(str);
	return str.Get();
}