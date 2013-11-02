//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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

#include "CScriptArgument.h"

class CSquirrelVM : public CScriptVM {

private:
	SQVM*		m_pVM;
	int m_iStackIndex;
public:
	CSquirrelVM(CResource * pResource);
	~CSquirrelVM();

	eVMType GetVMType() { return SQUIRREL_VM; }
	SQVM*			GetVM() { return m_pVM; }

	bool LoadScript(CString script);		// Replace string with script
	bool LoadScripts(std::list<CScript> scripts);

	void Pop(bool& b);
	void Pop(int& i);
	void Pop(unsigned int& i);
	void Pop(long& i);
	void Pop(unsigned long& i);
	void Pop(float& f);
	void Pop(CString& str);
	void Pop(CVector3& vec);

	void Pop(bool& b, bool bDefaultValue);
	void Pop(int& i, int iDefaultValue);
	void Pop(unsigned int& i, unsigned int iDefaultValue);
	void Pop(long& i, long iDefaultValue);
	void Pop(unsigned long& i, unsigned long iDefaultValue);
	void Pop(float& f, float fDefaultValue);
	void Pop(CString& str, CString strDefaultValue);
	void Pop(CVector3& vec, CVector3 vecDefaultValue);

	void Push(const bool& b);
	void Push(const int& i);
	void Push(const unsigned int& i);
	void Push(const long& i);
	void Push(const unsigned long& i);
	void Push(const float& f);
	void Push(const CString& str);
	void Push(const CVector3& vec);
	void PushArray(const CScriptArguments &array);
	void PushTable(const CScriptArguments &table);

	virtual CScriptArgument::ArgumentType GetType(int idx);

	int			 GetArgumentCount() { return sq_gettop(m_pVM); }

	void		 SetStackIndex(int iStackIndex) { m_iStackIndex = iStackIndex; }
	void		 ResetStackIndex() { m_iStackIndex = 2; }

	void		 RegisterScriptClass(const char* className, scriptFunction pfnFunction, void* userPointer = 0, const char* baseClass = 0);
	void		 RegisterClassFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL);
	void		 FinishRegisterScriptClass();
	void		*GetUserData(int idx);

	void *		PopInstance(const char *szClassName);
	void		PushInstance(const char* szClassName, void * pInstance);

	void		 SetClassInstance(const char* szClassName, void * pInstance);
	void		 *GetClassInstance(const char* szClassName);

	void		 RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL, bool bPushRootTable = false);
};

#endif // CSquirrelVM_h