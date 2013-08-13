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

	virtual void PopBool(bool& b) {}
	virtual void PopInteger(int& i) {}
	virtual void PopFloat(float& f) {}
	virtual void PopString(CString& str) {}
	virtual void PopVector(CVector3& vec) {}

	virtual void PopBool(bool& b, bool bDefaultValue) {}
	virtual void PopInteger(int& i, int iDefaultValue) {}
	virtual void PopFloat(float& f, float fDefaultValue) {}
	virtual void PopString(CString& str, CString strDefaultValue) {}
	virtual void PopVector(CVector3& vec, CVector3 vecDefaultValue) {}

	virtual void PushBool(const bool& b) {}
	virtual void PushInteger(const int& i) {}
	virtual void PushFloat(const float& f) {}
	virtual void PushString(const CString& str) {}
	virtual void PushVector(const CVector3& vec) {}

	virtual void ResetStackIndex() {}
	virtual void RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL, bool bPushRootTable = false) {}

	virtual void RegisterScriptClass(const char* className, scriptFunction pfnFunction, const char* baseClass = 0) {}
	virtual void RegisterClassFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL) {}
	virtual void SetClassInstance(const char* szClassName, void * pInstance) { }
	virtual void* GetClassInstance(const char* szClassName) {return 0;}
};

#endif // CScriptVM_h