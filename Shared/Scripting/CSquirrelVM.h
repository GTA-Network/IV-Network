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

#ifndef CSquirrelVM_h
#define CSquirrelVM_h

#include "IScriptVM.h"

#include <map>
#include <Squirrel/squirrel.h>
#include <Squirrel/sqvm.h>
#include "CScriptArgument.h"

class CSquirrelVM : public IScriptVM 
{

private:
	SQVM*		m_pVM;
	int m_iStackIndex;
	std::map<void*, HSQOBJECT> m_Instances;
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
	void Pop(stScriptFunction& function);
	void Pop(CString& str, CString strDefaultValue);
	void Pop(CVector3& vec, CVector3 vecDefaultValue);
	void PopTable(CScriptArguments &table) {}

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


	void		 Call(stScriptFunction, CScriptArguments * pArgument = 0);

	
	
	void		 BeginRegisterScriptClass(const char* className, scriptFunction pfnFunction, void* userPointer = 0, const char* baseClass = 0);
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