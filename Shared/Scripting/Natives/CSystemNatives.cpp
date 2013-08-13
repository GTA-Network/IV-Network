//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CSystemNatives.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSystemNatives.h"

#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <CLogFile.h>
#include <Scripting/ResourceSystem/CResourceManager.h>

class CTestClass {
public:
	CTestClass() {printf("in constructor\n");}
	~CTestClass() {printf("in destructor\n");}
};

class CTestScriptClass
{
public:
	CTestScriptClass(int *VM) {
		printf("Hallooooooo\n");
		
	}
	~CTestScriptClass() {
		printf("fasfasfoo\n");
	}

	static int SetPosition(int * VM)
	{
		
		// Just an example how the new scripting works with a lua or a squirrel vm its not needed to create a native for every language
		CResource* pResource = CResourceManager::GetInstance()->Get(VM);
		if(pResource)
		{
			// We do not have to split it here because our CScriptVM class provides the necessary push and pop/get methods
			CScriptVM* pVM = pResource->GetVM();

			CTestClass* pTestClass = (CTestClass*)pVM->GetClassInstance("testClass");
			CVector3 vecPos;
			pVM->PopVector(vecPos);
			CLogFile::Printf("Vec %f | %f | %f", vecPos.fX, vecPos.fY, vecPos.fZ);
			pVM->ResetStackIndex();
		}

		return 0;
	}

	static int constructor(int *VM) {
		CResource* pResource = CResourceManager::GetInstance()->Get(VM);
		if(pResource)
		{
			CTestClass* pClass = new CTestClass();

			pResource->GetVM()->SetClassInstance("testClass", (void*)pClass);
			pResource->GetVM()->RegisterClassFunction("setPosition", SetPosition);
			pResource->GetVM()->RegisterClassFunction("setPosition2", SetPosition);
			pResource->GetVM()->RegisterClassFunction("setPosition3", SetPosition);
		}
		return 1;
	}
};

void CSystemNatives::Register(CScriptVM * pVM)
{
	pVM->RegisterFunction("print", Print);

	pVM->RegisterScriptClass("testClass", &CTestScriptClass::constructor);
}

int CSystemNatives::Print(int * VM)
{
	// Just an example how the new scripting works with a lua or a squirrel vm its not needed to create a native for every language
	CResource* pResource = CResourceManager::GetInstance()->Get(VM);
	
	if(pResource)
	{
		// We do not have to split it here because our CScriptVM class provides the necessary push and pop/get methods
		CScriptVM* pVM = pResource->GetVM();
		pVM->ResetStackIndex();
		CString strPrint;
		pVM->PopString(strPrint);
		CLogFile::Printf(strPrint);

		pVM->ResetStackIndex();
	}

	return 0;
}