//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CInput.h
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CInput_h
#define CInput_h

#include <Threading/CThread.h>

class CInput {

private:

public:
	CInput();
	~CInput();

	static CString	GetInput();
	static void		ProcessInput(CString strInput);
	static void		InputThread(CThread* pThread);
};

#endif // CInput_h