//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrelArguments.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CSquirrelArguments_h
#define CSquirrelArguments_h

#include <list>
#include <Common.h>
#include <Squirrel/squirrel.h>
#include <Math/CMaths.h>

class CSquirrelArguments;

class CSquirrelArgument
{
private:
	SQObjectType type;

public:
	union {
		int i;
		bool b;
		float f;
		CString* str;
		CSquirrelArguments* pArray;
		SQObject sqObject;
		SQInstance * pInstance;
	} data;

	CSquirrelArgument(){type=OT_NULL;}
	CSquirrelArgument(int i){type=OT_INTEGER; data.i=i;}
	CSquirrelArgument(bool b){type=OT_BOOL; data.b=b;}
	CSquirrelArgument(float f){type=OT_FLOAT; data.f=f;}
	CSquirrelArgument(CString* str){type=OT_STRING; data.str = new CString(*str);} // clone the string instead of referencing it
	CSquirrelArgument(CSquirrelArguments* pArray, bool isArray);
	CSquirrelArgument(SQObject o);

	~CSquirrelArgument();

	SQObjectType GetType(){return type;}

	bool push(SQVM* pVM);
};

class CSquirrelArguments {

private:
	std::list<CSquirrelArgument*>		* m_pArguments;
public:
	CSquirrelArguments(){ m_pArguments = new std::list<CSquirrelArgument*>(); }
	~CSquirrelArguments()
	{
		for(auto pArgument : *m_pArguments)
		{
			delete pArgument;
		}
	}

	std::list<CSquirrelArgument*> * GetArguments() { return m_pArguments; }

	void push_to_vm(SQVM* pVM);

	// All kind of push functions
	void push();
	void push(SQObject o);
	void push(int i);
	void push(bool b);
	void push(float f);
	void push(const char* c);
	void push(CString str);
	void push(CVector3 vec);
	void push(CSquirrelArguments* pArray, bool isArray);
	bool pushFromStack(SQVM* pVM, int idx);
	void pushFromStack(SQVM* pVM, int startidx, int count);
};

#endif // CSquirrelArguments_h