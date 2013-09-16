//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CScriptVM.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScriptVM_h
#define CScriptVM_h

#include <Common.h>
#include <Math/CMaths.h>
#include <list>

#include "CScript.h"
#include "ResourceSystem/CResource.h"
#include "CScriptArguments.h"
#include "CScriptArgument.h"
// Helper macro to get the vm in scripting native;
#define GET_SCRIPT_VM_SAFE 	CResource* pResource = CResourceManager::GetInstance()->Get(VM); if(!pResource)return 0; CScriptVM* pVM = pResource->GetVM();if(!pVM) return 0;
#define GET_ENTITY_SAFE CNetworkEntity* pEntity = (CNetworkEntity*)pVM->GetClassInstance(""); if(!pEntity) return 0;

enum eVMType
{
	LUA_VM,
	SQUIRREL_VM,
	UNKNOWN_VM,
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

	virtual eVMType GetVMType() { return UNKNOWN_VM; }

	virtual bool LoadScript(CString script) { return false; }		// Replace string with script
	virtual bool LoadScripts(std::list<CScript> scripts) { return false; }

	virtual void Pop(bool& b) {}
	virtual void Pop(int& i) {}
	virtual void Pop(float& f) {}
	virtual void Pop(CString& str) {}
	virtual void Pop(CVector3& vec) {}

	virtual void Pop(bool& b, bool bDefaultValue) {}
	virtual void Pop(int& i, int iDefaultValue) {}
	virtual void Pop(float& f, float fDefaultValue) {}
	virtual void Pop(CString& str, CString strDefaultValue) {}
	virtual void Pop(CVector3& vec, CVector3 vecDefaultValue) {}
	virtual void PopArray(CScriptArguments &array) {}
	virtual void PopTable(CScriptArguments &table) {}

	virtual void Push(const bool& b) {}
	virtual void Push(const int& i) {}
	virtual void Push(const float& f) {}
	virtual void Push(const CString& str) {}
	virtual void Push(const CVector3& vec) {}
	virtual void PushArray(const CScriptArguments &array) {}
	virtual void PushTable(const CScriptArguments &table) {}

	virtual CScriptArgument::ArgumentType GetType(int idx) { return CScriptArgument::ArgumentType::ST_INVALID; }

	virtual void SetStackIndex(int iStackIndex) { }
	virtual void ResetStackIndex() {}

	virtual int	 GetArgumentCount() { return 0; }

	virtual void RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL, bool bPushRootTable = false) {}

	virtual void RegisterScriptClass(const char* className, scriptFunction pfnFunction, void* userPointer = 0, const char* baseClass = 0) {}
	virtual void RegisterClassFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL) {}
	virtual void FinishRegisterScriptClass() {}
	virtual void* GetUserData(int idx) { return 0; }

	virtual void PushInstance(const char* szClassName, void * pInstance) { } 
	virtual void SetClassInstance(const char* szClassName, void * pInstance) { }
	virtual void* GetClassInstance(const char* szClassName) {return 0;}
};

#endif // CScriptVM_h