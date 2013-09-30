//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CInput.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
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