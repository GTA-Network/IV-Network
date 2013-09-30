//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CDirectInput8Hook.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CDirectInput8Hook_h
#define CDirectInput8Hook_h

#include "StdDXInc.h"

typedef HRESULT	( WINAPI * DirectInput8Create_t )( HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN );

class CDirectInput8Hook {

private:

	static	bool						m_bInstalled;

public:

	static	DirectInput8Create_t		m_pDirectInput8Create;
	static	bool						Install( );
	static	void						Uninstall( );

};

#endif // CDirectInput8Hook_h