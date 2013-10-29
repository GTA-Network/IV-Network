//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CContextSwitch.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CContextSwitch_h
#define CContextSwitch_h

class CContextSwitch {
private:

public:
	CContextSwitch() { };
	~CContextSwitch() { };

	static void InstallKeySyncHooks();
};

#endif // CContextSwitch_h