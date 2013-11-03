//========== IV:Network - https://github.com/GTA-Network/IV-Network ======================
//
// Author: Knight
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
	if(HIWORD(BASS_GetVersion()) != BASSVERSION)
	{
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
	for(std::list<CAudio *>::iterator iter = m_audioList.begin(); iter != m_audioList.end(); iter++)
		SAFE_DELETE(*iter);

	m_audioList.clear();
}

void CAudioManager::MuteAll()
{
	if(m_bMuted)
		return;

	for(std::list<CAudio *>::iterator iter = m_audioList.begin(); iter != m_audioList.end(); iter++)
		(*iter)->Mute();

	m_bMuted = true;
}

void CAudioManager::UnmuteAll()
{
	if(!m_bMuted)
		return;

	for(std::list<CAudio *>::iterator iter = m_audioList.begin(); iter != m_audioList.end(); iter++)
		(*iter)->Unmute();

	m_bMuted = false;
}

void CAudioManager::Process()
{
	for(std::list<CAudio *>::iterator iter = m_audioList.begin(); iter != m_audioList.end(); iter++)
		(*iter)->Process();
}

bool GetHTTPData(CString host, CString page, CString &buffer)
{
	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *(DWORD*) gethostbyname(host.Get())->h_addr;

	if (connect(Socket, (SOCKADDR*) &SockAddr, sizeof(SockAddr)) != 0)
		return false;

	CString sendme = CString(
		"GET %s HTTP/1.1\r\n"
		"Host: %s\r\n"
		"Connection: close\r\n"
		"\r\n", 
		page.Get(),
		host.Get()
	);

	send(Socket, sendme.Get(), sendme.GetLength(), 0);

	char* _buffer = new char[10000];
	memset(_buffer, 0, 10000);
	recv(Socket, _buffer, 10000, 0);
	buffer = _buffer;
	buffer.Erase(0, buffer.Find("\r\n\r\n") + strlen("\r\n\r\n"));
	delete [] _buffer;

	closesocket(Socket);
	return true;
}

CString CAudioManager::GetYoutubeStreamURL(CString link)
{
	CString idBuffer;
	if (GetHTTPData("www.youtube-mp3.org", CString("/a/pushItem/?item=%s", link.Get()).Get(), idBuffer))
	{
		CString sessionBuffer;
		if (GetHTTPData("www.youtube-mp3.org", CString("/a/itemInfo/?video_id=%s", idBuffer.Get()).Get(), sessionBuffer))
		{
			CLogFile::Print(sessionBuffer.Get());
			
			if (sessionBuffer.Find("\"h\" : \""))
			{
				sessionBuffer.Erase(0, sessionBuffer.Find("\"h\" : \"") + strlen("\"h\" : \""));
				sessionBuffer.Erase(sessionBuffer.Find("\""), sessionBuffer.GetLength());
			}

			Sleep(3000);

			return CString("http://www.youtube-mp3.org/get?video_id=%s&h=%s", idBuffer.Get(), sessionBuffer.Get());
		}
	}
	return CString("");
}