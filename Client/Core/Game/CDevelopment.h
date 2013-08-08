//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CDevelopment.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CDevelopment_h
#define CDevelopment_h

class CDevelopment {
private:
	bool		bDebugView;
public:
				CDevelopment();
				~CDevelopment();

	void		Process();
	void		SetDebugView(bool bView) { bDebugView = bView; }
	bool		GetDebugView() { return bDebugView; }
};

#endif // CDevelopment_h