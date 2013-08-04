//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CScriptArgument.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScriptArgument_h
#define CScriptArgument_h

#include <Common.h>
#include <Network/CBitStream.h>

enum eScriptArgumentType {
	ST_NULL,
	ST_INTEGER,
	ST_FLOAT,
	ST_BOOL,
	ST_STRING,
	ST_TABLE,
	ST_ARRAY,
};

class CScriptArgument {

private:
	union
	{
		int i;
		bool b;
		float f;
		CString * str;
		// TODO add missing types described in enum
	} data;

	eScriptArgumentType type;
public:
	CScriptArgument() { type = ST_NULL; }
	CScriptArgument(int i) { type = ST_INTEGER; data.i = i; }
	CScriptArgument(bool b) { type = ST_BOOL; data.b = b; }
	CScriptArgument(float f) { type = ST_FLOAT; data.f = f; }
	CScriptArgument(CString str) { type = ST_STRING; data.str = new CString(str); }
	CScriptArgument(CString * str) { type = ST_STRING; data.str = str; }
	CScriptArgument(const char* sz) { type = ST_STRING; data.str = new CString(sz); }
	CScriptArgument(CBitStream * pBitStream);
	CScriptArgument(const CScriptArgument& p);
	~CScriptArgument();

	eScriptArgumentType	 GetType() { return type; }

	void                 reset();
	
	void                 serialize(CBitStream * pBitStream);
	void                 deserialize(CBitStream * pBitStream);

	void                 set(const CScriptArgument& p);
	void                 SetNull()                 { reset(); type = ST_NULL; }
	void                 SetInteger(int i)         { reset(); type = ST_INTEGER; data.i = i; }
	void                 SetBool   (bool b)        { reset(); type = ST_BOOL; data.b = b; }
	void                 SetFloat  (float f)       { reset(); type = ST_FLOAT; data.f = f; }
	void                 SetString (const char* s) { reset(); type = ST_STRING; data.str = new CString(s); }

	int                  GetInteger() const { return (type == ST_INTEGER) ? data.i : 0; }
	bool                 GetBool()    const { return (type == ST_BOOL)    ? data.b : (type == ST_INTEGER ? data.i != 0 : false); }
	float                GetFloat()   const { return (type == ST_FLOAT)   ? data.f : 0.0f; }
	CString			   * GetString()  const { return (type == ST_STRING)  ? data.str : NULL; }
};

#endif // CScriptArgument_h