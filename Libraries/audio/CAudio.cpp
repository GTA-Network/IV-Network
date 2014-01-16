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

#include "CAudio.h"
#include <bass/bass.h>
#include <SharedUtility.h>
#include "CCore.h"

extern CCore * g_pCore;

CAudio::CAudio(CString strStreamName, bool bReplay, bool bIsOnlineStream) : 
			   m_strStreamName(strStreamName), m_bReplay(bReplay), m_bIsOnlineStream(bIsOnlineStream), 
			   m_bUsePosition(false), m_fRange(0.0f), m_fVolume(100.0f),
			   m_bIsMuted(false), m_dwChannel(0)
{
	
}

CAudio::~CAudio()
{
	Stop();
	Unload();
}

bool CAudio::Load()
{
	if(m_dwChannel == 0) 
	{
		// Create BASS stream
		if(m_bIsOnlineStream)
			m_dwChannel = BASS_StreamCreateURL(m_strStreamName, 0, (BASS_STREAM_BLOCK | BASS_STREAM_STATUS | BASS_STREAM_AUTOFREE), 0, 0);
		else
			m_dwChannel = BASS_StreamCreateFile(FALSE, m_strStreamName, 0, 0, BASS_STREAM_PRESCAN);

		// stream create check
		if(m_dwChannel != 0) 
		{
			BASS_ChannelSetAttribute(m_dwChannel, BASS_ATTRIB_VOL, (m_fVolume * 0.01f));
			return true;
		}
	}

	return false;
}

void CAudio::Unload()
{
	// Do we have a valid channel?
	if(m_dwChannel != 0) 
	{
		// Free BASS stream
		BASS_StreamFree(m_dwChannel);
		m_dwChannel = 0;
	}
}

bool CAudio::Play()
{
	// Do we have a valid channel?
	if(m_dwChannel != 0)
		return (BASS_ChannelPlay(m_dwChannel, FALSE) != 0);

	return false;
}

void CAudio::Pause()
{
	// Do we have a valid channel?
	if(m_dwChannel != 0)
		BASS_ChannelPause(m_dwChannel);
}

bool CAudio::IsPlaying()
{
	// Do we have a valid channel?
	if(m_dwChannel != 0)
		return (BASS_ChannelIsActive(m_dwChannel) == BASS_ACTIVE_PLAYING);

	return false;
}

bool CAudio::IsPaused()
{
	// Do we have a valid channel?
	if(m_dwChannel != 0)
		return (BASS_ChannelIsActive(m_dwChannel) == BASS_ACTIVE_PAUSED);

	return false;
}

bool CAudio::IsStalled()
{
	// Do we have a valid channel?
	if(m_dwChannel != 0)
		return (BASS_ChannelIsActive(m_dwChannel) == BASS_ACTIVE_STALLED);

	return false;
}

void CAudio::Stop()
{
	// Do we have a valid channel?
	if(m_dwChannel != 0)
		BASS_ChannelStop(m_dwChannel);
}

void CAudio::SetUsePosition(bool bUsePosition)
{
	m_bUsePosition = bUsePosition;
}

void CAudio::SetPosition(CVector3 vecPosition, float fRange)
{
	m_vecPosition = vecPosition;
	m_fRange = fRange;
}

void CAudio::GetPosition(CVector3& vecPosition, float& fRange)
{
	vecPosition = m_vecPosition;
	fRange = m_fRange;
}

void CAudio::SetVolume(float fVolume)
{
	// Volume check
	m_fVolume = Math::Clamp(0.0f, fVolume, 100.0f);

	// Do we have a valid channel?
	if(m_dwChannel != 0) 
	{
		// New volume
		if(!m_bIsMuted)
			BASS_ChannelSetAttribute(m_dwChannel, BASS_ATTRIB_VOL, (m_fVolume * 0.01f));
	}
}

float CAudio::GetVolume()
{
	if(m_bIsMuted)
		return 0.0f;

	// Do we have a valid channel?
	if(m_dwChannel != 0) 
	{
		// Current volume
		float fVolume;
		BASS_ChannelGetAttribute(m_dwChannel, BASS_ATTRIB_VOL, &fVolume);
		return fVolume/0.01f;
	}

	return 0.0f;
}

void CAudio::Mute()
{
	if(!m_bIsMuted) 
	{
		// Do we have a valid channel?
		if(m_dwChannel != 0)
			BASS_ChannelSetAttribute(m_dwChannel, BASS_ATTRIB_VOL, 0.0f);

		// Flag as muted
		m_bIsMuted = true;
	}
}

void CAudio::Unmute()
{
	if(m_bIsMuted) 
	{
		// Do we have a valid channel?
		if(m_dwChannel != 0)
			BASS_ChannelSetAttribute(m_dwChannel, BASS_ATTRIB_VOL, (m_fVolume * 0.01f));

		// Flag as not muted
		m_bIsMuted = false;
	}
}

void CAudio::Process()
{
	if(m_bUsePosition) 
	{
		CVector3 vecLocalPlayer;
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecLocalPlayer);

		float fDistance = Math::GetDistanceBetweenPoints3D(vecLocalPlayer.fX, vecLocalPlayer.fY, vecLocalPlayer.fZ, m_vecPosition.fX, m_vecPosition.fY, m_vecPosition.fZ);

		if(fDistance < m_fRange) 
		{
			float fVolume = exp(-fDistance * (5.0f / m_fRange));
			SetVolume(fVolume / 0.01f);
		}
		else
			SetVolume(0.0f);
	}
}

int CAudio::GetLength()
{
	if (m_bIsOnlineStream)
		return -1;
	
	// Do we have a valid channel?
	if (m_dwChannel) 
	{
		// get length
		long length = BASS_ChannelGetLength (m_dwChannel, BASS_POS_BYTE);
		
		// convert into seconds and return
		return BASS_ChannelBytes2Seconds(m_dwChannel, length);
	}
	return -1;
}

bool CAudio::SetAt(int iTime)
{
	if (m_bIsOnlineStream)
		return false;

	// Do we have a valid channel?
	if (m_dwChannel) 
	{
		long lTime =BASS_ChannelSeconds2Bytes (m_dwChannel, iTime);
		BASS_ChannelSetPosition(m_dwChannel, lTime, BASS_POS_BYTE);
		return true;
	}
	return false;
}	

int CAudio::GetAt() 
{
	if (m_bIsOnlineStream)
		return -1;

	// Do we have a valid channel?
	if (m_dwChannel) 
	{
		long length = BASS_ChannelGetPosition(m_dwChannel, BASS_POS_BYTE);
		return BASS_ChannelBytes2Seconds (m_dwChannel, length);
	}
	return -1;
}