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

#ifndef CScriptArguments_h
#define CScriptArguments_h

#include <Common.h>
#include <list>

class CScriptArgument;
class CScriptVM;

class CScriptEntity;

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
	void push(CScriptEntity* pEntity);
	void pushVector3(const CVector3 &vec3);

	CScriptArgument pop();
	bool popVector3(CVector3 &vec3);

	std::list<CScriptArgument *> m_Arguments;
};

#endif // CScriptArguments_h