//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CHooks.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CHooks_h
#define CHooks_h

class CHooks {
public:
					CHooks() { };
					~CHooks() { };

	static void		IncreasePoolSizes(int multi);
	static void		Intialize();
};

#endif // CHooks_h