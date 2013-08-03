//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CGame.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CGame_h
#define CGame_h

class CGame {

public:

					CGame() { };
					~CGame() { };

	static void		Setup();
	static void		UnprotectMemory();
};

#endif // CGame_h