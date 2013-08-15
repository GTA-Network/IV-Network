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

	virtual void PopBool(bool& b);
	virtual void PopInteger(int& i);
	virtual void PopFloat(float& f);
	virtual void PopString(CString& str);
	virtual void PopVector(CVector3& vec);

	virtual void PopBool(bool& b, bool bDefaultValue);
	virtual void PopInteger(int& i, int iDefaultValue);
	virtual void PopFloat(float& f, float fDefaultValue);
	virtual void PopString(CString& str, CString strDefaultValue);
	virtual void PopVector(CVector3& vec, CVector3 vecDefaultValue);

	virtual void PushBool(const bool& b);
	virtual void PushInteger(const int& i);
	virtual void PushFloat(const float& f);
	virtual void PushString(const CString& str);
	virtual void PushVector(const CVector3& vec);

	void		 ResetStackIndex() { m_iStackIndex = 2; }

	virtual void RegisterScriptClass(const char* className, scriptFunction pfnFunction, const char* baseClass = 0);
	virtual void RegisterClassFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL);
	virtual void SetClassInstance(const char* szClassName, void * pInstance);
	void		 *GetClassInstance(const char* szClassName);

	void		 RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL, bool bPushRootTable = false);
};

#endif // CSquirrelVM_h