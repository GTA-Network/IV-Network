//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CAudioManager.h
// Project: Client.Core
// Author: Knight<xxx@xxx>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CAUDIOMANAGER_H
#define CAUDIOMANAGER_H

#include "CAudio.h"

class CAudioManager {
private:
	std::list<CAudio *>	 m_audioList;
	bool				 m_bMuted;

public:
						CAudioManager();
						~CAudioManager();

	bool				Initialize();
	void				Add(CAudio * pAudio);
	void				Remove(CAudio * pAudio);
	void				RemoveAll();
	void				MuteAll();
	inline bool			IsMuted() { return m_bMuted; }
	void				UnmuteAll();
	void				Process();
	CString				GetYoutubeStreamURL(CString link);
};

#endif // CAUDIOMANAGER_H