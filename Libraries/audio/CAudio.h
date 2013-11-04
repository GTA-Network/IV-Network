//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CAudio.h
// Project: Client.Core
// Author: Knight<xxx@xxx>
// License: See LICENSE in root directory
//
//==========================================================================================

#include <Common.h>

#ifndef CAUDIO_H
#define CAUDIO_H

class CAudio {
private:
	CString			m_strStreamName;
	bool			m_bReplay;
	bool			m_bIsOnlineStream;
	bool			m_bUsePosition;
	CVector3		m_vecPosition;
	float			m_fRange;
	float			m_fVolume;
	bool			m_bIsMuted;
	DWORD			m_dwChannel;

public:
					CAudio(CString strStreamName, bool bReplay = false, bool bIsOnlineStream = false);
					~CAudio();

	bool			Load();
	inline bool		IsLoaded() { return (m_dwChannel != 0); }
	void			Unload();
	bool			Play();
	void			Pause();
	bool			IsPlaying();
	bool			IsPaused();
	bool			IsStalled();
	void			Stop();
	void			SetUsePosition(bool bUsePosition);
	inline bool		GetUsePosition() { return m_bUsePosition; }
	void			SetPosition(CVector3 vecPosition, float fRange);
	void			GetPosition(CVector3& vecPosition, float& fRange);
	void			SetVolume(float fVolume);
	float			GetVolume();
	void			Mute();
	inline bool		IsMuted() { return m_bIsMuted; }
	void			Unmute();
	void			Process();
	int				GetLength();
	bool			SetAt(int iTime);
	int				GetAt();
};

#endif // CAUDIO_H