//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrelVM.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CSquirrelVM_h
#define CSquirrelVM_h

#include "CScriptVM.h"
#include <Squirrel/squirrel.h>

class CSquirrelVM : public CScriptVM {

private:
	SQVM*		m_pVM;
	int m_iStackIndex;
public:
	CSquirrelVM(CResource * pResource);
	~CSquirrelVM();

	virtual eVMType GetVMType() { return SQUIRREL_VM; }
	SQVM*			GetVM() { return m_pVM; }

	virtual bool LoadScript(CString script);		// Replace string with script
	virtual bool LoadScripts(std::list<CScript> scripts);

	virtual void Pop(bool& b);
	virtual void Pop(int& i);
	virtual void Pop(float& f);
	virtual void Pop(CString& str);
	virtual void Pop(CVector3& vec);

	virtual void Pop(bool& b, bool bDefaultValue);
	virtual void Pop(int& i, int iDefaultValue);
	virtual void Pop(float& f, float fDefaultValue);
	virtual void Pop(CString& str, CString strDefaultValue);
	virtual void Pop(CVector3& vec, CVector3 vecDefaultValue);

	virtual void Push(const bool& b);
	virtual void Push(const int& i);
	virtual void Push(const float& f);
	virtual void Push(const CString& str);
	virtual void Push(const CVector3& vec);
	virtual void PushArray(const CScriptArguments &array);
	virtual void PushTable(const CScriptArguments &table);

	void		 ResetStackIndex() { m_iStackIndex = 2; }

	virtual void RegisterScriptClass(const char* className, scriptFunction pfnFunction, const char* baseClass = 0);
	virtual void RegisterClassFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL);
	virtual void SetClassInstance(const char* szClassName, void * pInstance);
	void		 *GetClassInstance(const char* szClassName);

	void		 RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL, bool bPushRootTable = false);
};

#endif // CSquirrelVM_h