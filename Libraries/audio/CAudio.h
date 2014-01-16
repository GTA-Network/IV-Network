/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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