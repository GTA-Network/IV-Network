//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CAudioManager.cpp
// Project: Client.Core
// Author: Knight<xxx@xxx>
// License: See LICENSE in root directory
//
//==========================================================================================

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