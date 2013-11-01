#include <Common.h>
#include <CCore.h>
#include <Scripting/CClientCommands.h>
#include "CChat.h"
#include "..\IV\CIVScript.h"

extern CCore * g_pCore;

CChat::CChat() :
	m_bVisible(false), m_bTypeing(false)
{
	for (int i = 0; i < CHAT_MAX_LINES; ++i)
		m_szMessages[i] = CString("");

	m_szTypeing = CString("");
}

CChat::~CChat()
{
	for (int i = 0; i < CHAT_MAX_LINES; ++i)
		delete [] m_szMessages[i];

	delete [] m_szTypeing;
}

/*void removeColorCodes(char* text)
{
char* tmptext = new char[CHAT_MAX_CHAT_LENGTH];

for (int i = 0, i2 = 0; i < CHAT_MAX_CHAT_LENGTH; ++i)
{
if (text[i] != '#')
{
tmptext[i2] = text[i];
++i2;
}
else
i += 6;
}

strcpy_s(text, CHAT_MAX_CHAT_LENGTH, tmptext);

delete[] tmptext;
}*/

void CChat::Render()
{
	if (!m_bVisible)
		return;
	
	float fY = 16.0f;

	for (int i = 0; i < CHAT_RENDER_LINES; ++i)
	{
		char* text = new char[CHAT_MAX_CHAT_LENGTH];
		strcpy_s(text, CHAT_MAX_CHAT_LENGTH, m_szMessages[CHAT_MAX_LINES - CHAT_RENDER_LINES + i].Get());
		 
		DWORD color = D3DCOLOR_ARGB(255, 255, 255, 255);
		float fX = 26.0f;

		for (int i = 0; i < CHAT_MAX_CHAT_LENGTH; ++i)
		{
			if (text[i] == '\0')
				break;

			if (text[i] != '#')
			{
				g_pCore->GetGraphics()->DrawText(fX, fY, color, 1.0f, DT_NOCLIP, true, CString("%c", text[i]).Get());
				fX += g_pCore->GetGraphics()->GetCharacterWidth(text[i]);
			}
			else
			{
				DWORD tmpcolor = 0;
				sscanf_s(text + i + 1, "%06x", &tmpcolor);
				color = D3DCOLOR_ARGB(255, ((tmpcolor >> 16) & 0xFF), ((tmpcolor >> 8) & 0xFF), (tmpcolor & 0xFF));
				i += 6;
			}
		}

		fY += g_pCore->GetGraphics()->GetFontHeight();

		delete [] text;
	}

	if (m_bTypeing)
	{
		g_pCore->GetGraphics()->DrawText(26.0f, fY, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, DT_NOCLIP, true, "Say:");
		g_pCore->GetGraphics()->DrawText(58.0f, fY, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, DT_NOCLIP, true, m_szTypeing);
	}
}

void CChat::Print(CString text)
{
	text = text.Substring(0, CHAT_MAX_CHAT_LENGTH);

	delete [] m_szMessages[0];

	for (int i = 0; i < CHAT_MAX_LINES-1; ++i)
		m_szMessages[i] = m_szMessages[i + 1];

	m_szMessages[CHAT_MAX_LINES - 1] = text;
}

void CChat::HandleUserInput(unsigned int uMsg, WPARAM dwChar)
{
	if (uMsg == WM_CHAR)
	{
		if (dwChar == VK_ESCAPE)
		{
			m_bTypeing = false;
		}
		else if (dwChar == VK_RETURN && m_bTypeing)
		{
			m_bTypeing = false;

			if (m_szTypeing.GetLength() > 0)
			{
				if (g_pCore->GetNetworkManager() && g_pCore->GetNetworkManager()->IsConnected())
				{
					if (m_szTypeing.GetChar(0) == '/')
					{
						size_t sCommandEnd = m_szTypeing.Find(" ");
						if (sCommandEnd == std::string::npos)
							sCommandEnd = m_szTypeing.GetLength();

						if (CClientCommands::HandleUserInput(m_szTypeing.Substring(1, (sCommandEnd - 1)), sCommandEnd < m_szTypeing.GetLength() ? m_szTypeing.Substring((sCommandEnd + 1), m_szTypeing.GetLength()) : ""))
							return;
					}

					RakNet::BitStream bitStream;

					if (m_szTypeing.GetChar(0) == '/')
						bitStream.Write1();
					else
						bitStream.Write0();

					bitStream.Write(m_szTypeing.Get());
					g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_PLAYER_CHAT), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, true);
				}
			}

			CIVScript::SetPlayerControlForTextChat(g_pCore->GetGame()->GetLocalPlayer()->GetScriptingHandle(), false);
		}
		else if (dwChar == VK_BACK && m_bTypeing)
		{
			if (m_szTypeing.GetLength() > 0)
				m_szTypeing.Resize((m_szTypeing.GetLength() - 1));
		}
		else if((dwChar == 'T' || dwChar == 't') && !m_bTypeing)
		{
			m_bTypeing = true;
			m_szTypeing.Clear();

			CIVScript::SetPlayerControlForTextChat(g_pCore->GetGame()->GetLocalPlayer()->GetScriptingHandle(), true);
		}
		else if (m_bTypeing && (m_szTypeing.GetLength() < CHAT_MAX_CHAT_LENGTH))
		{
			m_szTypeing += dwChar;
		}
	}
}

void CChat::Clear()
{
	for (int i = 0; i < CHAT_MAX_LINES; ++i)
		m_szMessages[i].Clear();
}