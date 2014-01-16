/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CScriptVM_h
#define CScriptVM_h

#include <Common.h>
#include <Math/CMaths.h>
#include <list>

#include "CScript.h"
#include "ResourceSystem/CResource.h"
#include "CScriptArguments.h"
#include "CScriptArgument.h"

#include <assert.h>
#include <Squirrel/squirrel.h>
#include <Squirrel/sqstate.h>
#include <Squirrel/sqvm.h>
#include <Squirrel/sqobject.h>

// Helper macro to get the vm in scripting native;
#define GET_SCRIPT_VM_SAFE 	CResource* pResource = CResourceManager::GetInstance()->Get(VM); if(!pResource)return 0; CScriptVM* pVM = pResource->GetVM();if(!pVM) return 0;
#define GET_ENTITY_SAFE CNetworkEntity* pEntity = (CNetworkEntity*)pVM->GetClassInstance(""); if(!pEntity) return 0;

enum eVMType
{
	LUA_VM,
	SQUIRREL_VM,
	UNKNOWN_VM,
};

enum eFType
{
	LUA_FUNCTION,
	SQUIRREL_FUNCTION,
};

struct stScriptFunction
{
	int ref;
	SQObjectPtr function;
	eFType  type;
};

class CResource;

class CScriptVM {

private:
	CResource * m_pResource;
public:
	CScriptVM(CResource * pResource) { m_pResource = pResource; }
	~CScriptVM() {};

	typedef int (*scriptFunction)(int*);

	CResource * GetResource() { return m_pResource; }

	virtual eVMType GetVMType() = 0;

	virtual bool LoadScript(CString script) = 0;	// Replace string with script
	virtual bool LoadScripts(std::list<CScript> scripts) = 0;

	virtual void Pop(bool& b) = 0;
	virtual void Pop(int& i) = 0;
	virtual void Pop(unsigned int& i) = 0;
	virtual void Pop(long& i) = 0;
	virtual void Pop(unsigned long& i) = 0;
	virtual void Pop(float& f) = 0;
	virtual void Pop(CString& str) = 0;
	virtual void Pop(CVector3& vec) = 0;

	virtual void Pop(bool& b, bool bDefaultValue) = 0;
	virtual void Pop(int& i, int iDefaultValue) = 0;
	virtual void Pop(unsigned int& i, unsigned int iDefaultValue) = 0;
	virtual void Pop(long& i, long iDefaultValue) = 0;
	virtual void Pop(unsigned long& i, unsigned long iDefaultValue) = 0;
	virtual void Pop(float& f, float fDefaultValue) = 0;
	virtual void Pop(stScriptFunction& function) = 0;
	virtual void Pop(CString& str, CString strDefaultValue) = 0;
	virtual void Pop(CVector3& vec, CVector3 vecDefaultValue) = 0;
	//virtual void PopArray(CScriptArguments &array) = 0;
	virtual void PopTable(CScriptArguments &table) = 0;

	virtual void Push(const bool& b) = 0;
	virtual void Push(const int& i) = 0;
	virtual void Push(const unsigned int& i) = 0;
	virtual void Push(const long& i) = 0;
	virtual void Push(const unsigned long& i) = 0;
	virtual void Push(const float& f) = 0;
	virtual void Push(const CString& str) = 0;
	virtual void Push(const CVector3& vec) = 0;
	virtual void PushArray(const CScriptArguments &array) = 0;
	virtual void PushTable(const CScriptArguments &table) = 0;

	virtual CScriptArgument::ArgumentType GetType(int idx) = 0;

	virtual void Call(stScriptFunction, CScriptArguments * pArgument = 0) = 0;

	virtual void SetStackIndex(int iStackIndex) = 0;
	virtual void ResetStackIndex() = 0;

	virtual int	 GetArgumentCount() = 0;

	virtual void RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL, bool bPushRootTable = false) = 0;

	virtual void RegisterScriptClass(const char* className, scriptFunction pfnFunction, void* userPointer = 0, const char* baseClass = 0) = 0;
	virtual void RegisterClassFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL) = 0;
	virtual void FinishRegisterScriptClass() = 0;
	virtual void* GetUserData(int idx) = 0;

	//virtual void * PopInstance(const char szClassName) = 0;
	virtual void PushInstance(const char* szClassName, void * pInstance) = 0;
	virtual void SetClassInstance(const char* szClassName, void * pInstance) = 0;
	virtual void* GetClassInstance(const char* szClassName) = 0;
};

#endif // CScriptVM_h