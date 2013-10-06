//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CScriptArgument.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScriptArgument_h
#define CScriptArgument_h

#include <Common.h>
#include <lua/lua.hpp>
#include "CScriptArguments.h"

class CScriptVM;
class CScriptArguments;

class CScriptEntity;

class CScriptArgument {
public:
	enum ArgumentType
	{
		ST_INVALID,
		ST_INTEGER,
		ST_BOOL,
		ST_FLOAT,
		ST_STRING,
		ST_ARRAY,
		ST_TABLE,
		ST_ENTITY,
	};
private:
	ArgumentType m_eType;
public:

	union
	{
		int i;
		bool b;
		float f;
		CString * str;
		CScriptArguments * pArray;
		CScriptEntity * pEntity;
	} data;

	CScriptArgument() { m_eType = ST_INVALID;}
	CScriptArgument(int i) { m_eType = ST_INTEGER; data.i = i; }
	CScriptArgument(bool b) { m_eType = ST_BOOL; data.b = b; }
	CScriptArgument(float f) { m_eType = ST_FLOAT; data.f = f; }
	CScriptArgument(const CScriptArgument& p);
	CScriptArgument(CString str) { m_eType = ST_STRING; data.str = new CString(str); }
	CScriptArgument(const CScriptArguments& array, bool isArray = true) { m_eType = (isArray ? ST_ARRAY : ST_TABLE); data.pArray = new CScriptArguments(array); }
	CScriptArgument(CScriptEntity* pEntity) { m_eType = ST_ENTITY; data.pEntity = pEntity; }
	~CScriptArgument();

	ArgumentType		 GetType() const { return m_eType; }

	void				 reset();

	void				 Push(CScriptVM* pVM);

	void                 set(const CScriptArgument& p);

	void                 SetNull()                 { reset(); m_eType = ST_INVALID; }
	void                 SetInteger(int i)         { reset(); m_eType = ST_INTEGER; data.i = i; }
	void                 SetBool   (bool b)        { reset(); m_eType = ST_BOOL; data.b = b; }
	void                 SetFloat  (float f)       { reset(); m_eType = ST_FLOAT; data.f = f; }
	void                 SetString (const char* s) { reset(); m_eType = ST_STRING; data.str = new CString(s); }
	void                 SetArray(CScriptArguments * pArray) { reset(); m_eType = ST_ARRAY; data.pArray = pArray; }
	void                 SetTable(CScriptArguments * pTable) { reset(); m_eType = ST_TABLE; data.pArray = pTable; }

	int                  GetInteger() const { return (m_eType == ST_INTEGER) ? data.i : 0; }
	bool                 GetBool()    const { return (m_eType == ST_BOOL)    ? data.b : false; }
	float                GetFloat()   const { return (m_eType == ST_FLOAT)   ? data.f : 0.0f; }
	const char         * GetString()  const { return (m_eType == ST_STRING)  ? data.str->Get() : NULL; }
	CScriptArguments   * GetTable() const { return (m_eType == ST_TABLE) ? data.pArray : NULL; }
	CScriptArguments   * GetArray() const { return (m_eType == ST_ARRAY) ? data.pArray : NULL; }

	bool pushFromStack(CScriptVM * pVM, int idx);
};

#endif // CScriptArgument_h