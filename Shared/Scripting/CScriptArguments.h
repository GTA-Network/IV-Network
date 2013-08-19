//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CScriptArguments.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScriptArguments_h
#define CScriptArguments_h

#include <Common.h>
#include <list>

class CScriptArgument;

class CScriptArguments {

private:
	
public:
	CScriptArguments();
	CScriptArguments(const CScriptArguments& p);
	~CScriptArguments();

	void reset();

	void push(int i);
	void push(bool b);
	void push(float f);
	void push(const char* c);
	void push(CString str);
	void push(const CScriptArgument &arg);
	void push(const CScriptArguments &array, bool isArray);
	void push(CScriptArguments* pArray, bool isArray);
	void pushVector3(const CVector3 &vec3);

	CScriptArgument pop();
	bool popVector3(CVector3 &vec3);

	std::list<CScriptArgument *> m_Arguments;
};

#endif // CScriptArguments_h