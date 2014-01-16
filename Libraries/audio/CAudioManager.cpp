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

#include "CAudioManager.h"
#include <bass/bass.h>
#include "CCore.h"
#include <CLogFile.h>

extern CCore * g_pCore;

CAudioManager::CAudioManager() :
	m_bMuted(false)
{
	
}

CAudioManager::~CAudioManager()
{
	// Remove all audio
	RemoveAll();

	// Free BASS audio library
	BASS_Free();
}

bool CAudioManager::Initialize()
{
	// BASS version check
	if(HIWORD(BASS_GetVersion()) != BASSVERSION) {
		CLogFile::Printf("Invalid BASS version");
		return false;
	}

	// Initialize BASS audio library
	BASS_Init(-1, 44100, 0, 0, NULL);
	return true;
}

void CAudioManager::Add(CAudio * pAudio)
{
	m_audioList.push_back(pAudio);

	// Are we muted?
	if(m_bMuted)
		pAudio->Mute();
}

void CAudioManager::Remove(CAudio * pAudio)
{
	m_audioList.remove(pAudio);
	SAFE_DELETE(pAudio);
}

void CAudioManager::RemoveAll()
{
	for(auto pAudio:m_audioList)
		SAFE_DELETE(pAudio);

	m_audioList.clear();
}

void CAudioManager::MuteAll()
{
	if(m_bMuted)
		return;

	for(auto pAudio : m_audioList)
		pAudio->Mute();

	m_bMuted = true;
}

void CAudioManager::UnmuteAll()
{
	if(!m_bMuted)
		return;

	for(auto pAudio : m_audioList)
		pAudio->Unmute();

	m_bMuted = false;
}

void CAudioManager::Process()
{
	for(auto pAudio : m_audioList)
		pAudio->Process();
}

// TODO(!!): Move it to a shared file!!


CString CAudioManager::GetYoutubeStreamURL(CString link)
{
	CString idBuffer;
	if (SharedUtility::GetHTTPHeaderAndData("kingofmetin.com", CString("/yt.php?url=%s", link.Get()).Get(), "", NULL, &idBuffer))
		return idBuffer;

	return CString("");
}