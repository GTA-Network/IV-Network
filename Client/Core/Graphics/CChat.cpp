//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CChat.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CChat.h"
#include <CCore.h>
#include <Game/IVEngine/CIVModelManager.h>
extern CCore * g_pCore;

CChat::CChat(float fX, float fY)
{
	// Store the chat window screen position
	m_fX = fX;
	m_fY = fY;

	// Reset the variables
	SetVisible(true);
	m_bPaused = false;
	m_bMap = false;
	m_bOldState = false;
	m_uiNumLines = CHAT_MAX_LINES;
	m_uiMostRecentLine = 0;
	m_TextColor = CHAT_TEXT_COLOR;
	m_InputTextColor = CColor(255, 255, 255, 255);
	m_iRenderLines = 10;

	// Scroll
	m_uiScrollOffset = 0;
	m_fSmoothScroll = 0;
	m_fSmoothLastTimeSeconds = 0;
	m_fSmoothAllowAfter = 0;
	m_fSmoothScrollResetTime = 0;

	// History
	m_iCurrentHistory = -1;
	m_iTotalHistory = 0;

	// Input
	SetInputVisible(false);
	SetInputPrefix("> Say: ");
}

CChat::~CChat()
{
	Clear();
	ClearInput();
}

void CChat::Setup(D3DPRESENT_PARAMETERS * pPresentParameters)
{
	// Get the chat x, y position from the settings
	float fX = 50.0f;
	float fY = 50.0f;

	// Work out the maximum coordinates
	float fMaxX = (1920.0f - CHAT_WIDTH); // Or should we use already 2500 ?
	float fMaxY = (1080.0f - (m_iRenderLines * (CChat::GetFontHeight() + 2.0f) + 10.0f + 30.0f));

	// Clamp the coordinates
	fX = Math::Clamp(0.0f, fX, fMaxX);
	fY = Math::Clamp(0.0f, fY, fMaxY);

	// Store the chat position
	m_fX = fX;
	m_fY = fY;
}

void CChat::Render()
{
	// Is the chat window not visible?
	if(!m_bVisible)
		return;

	// Work out Y offset the position
	float fLineDifference = (CChat::GetFontHeight() + 2.0f);
	float fOffsetY = (m_iRenderLines * fLineDifference + 10.0f);

	// Apply line smooth scroll
	unsigned int uiLine = (m_uiMostRecentLine % m_iRenderLines);
	unsigned int uiLinesDrawn = 0;

	// Loop over all chatlines
	while(m_Lines[ uiLine ].IsActive() && uiLinesDrawn < m_uiNumLines)
	{
		// Draw the current line
		m_Lines[ uiLine ].Draw(m_fX, fOffsetY, 255, true);

		// Adjust the offset
		fOffsetY -= fLineDifference;

		// Increment the lines drawn
		uiLine = (uiLine + 1) % m_iRenderLines;
		uiLinesDrawn++;

		// Is this line the end?
		if(uiLine == m_uiMostRecentLine)
			break;
	}

	// Is the input visible?
	if(m_bInputVisible)
	{
		float y = (m_fY + (m_iRenderLines * fLineDifference) + 30.0f);
		m_InputLine.Draw(m_fX, y, 255, true);
	}

}

void CChat::Output(const char * szText, bool bColorCoded)
{
	//CLogFile::Printf("CChat::Output: %s",szText);
	 
	CChatLine * pLine = NULL;
	const char * szRemainingText = szText;
	CColor color = m_TextColor;

	do
	{
		m_uiMostRecentLine = (m_uiMostRecentLine == 0 ? m_iRenderLines - 1 : m_uiMostRecentLine - 1);
		
		pLine = &m_Lines[ m_uiMostRecentLine ];
		
		if(pLine)
		{
			szRemainingText = pLine->Format(szRemainingText, CHAT_WIDTH, color, bColorCoded);
			
			pLine->SetActive(true);
			
		}
	}
	while(szRemainingText);
}

void CChat::Outputf(bool bColorCoded, const char * szFormat, ...)
{
	char szString[512];

	va_list ap;
	va_start(ap, szFormat);
	vsprintf_s(szString, szFormat, ap);
	va_end(ap);

	Output(szString, bColorCoded);
}

void CChat::Clear()
{
	for(int i = 0; i < CHAT_MAX_LINES; i++)
	{
		m_Lines[ i ].SetActive(false);
	}

	m_uiMostRecentLine = 0;
	m_fSmoothScroll = 0;
}

void CChat::ClearInput()
{
	m_strInputText.Clear();
	m_InputLine.Clear();
}

float CChat::GetFontHeight()
{
	return g_pCore->GetGraphics()->GetFontHeight(1.0f);
}

float CChat::GetCharacterWidth(int iChar)
{
	return g_pCore->GetGraphics()->GetCharacterWidth((char)iChar, 1.0f);
}

void CChat::SetInputVisible(bool bVisible)
{
	m_bInputVisible = bVisible;

	// Unlock the player controls
	if(g_pCore->GetGame()->GetLocalPlayer() && !bVisible)
		g_pCore->GetGame()->GetLocalPlayer()->SetPlayerControlAdvanced(true,true);
}

bool CChat::HandleUserInput(unsigned int uMsg, DWORD dwChar)
{
	// Was it a key release?
	if(uMsg == WM_KEYUP)
	{
		if(dwChar == VK_ESCAPE)
		{
			
		}
		else if(dwChar == VK_RETURN)
		{
			// Is the input enabled?
			if(m_bInputVisible)
			{
				// Process input
				ProcessInput();

				// Clear the input buffer
				m_strInputText.Clear();

				// Clear the input line
				m_InputLine.Clear();

				// Disable input
				SetInputVisible(false);
				return true;
			}
		}
		else if (dwChar == VK_UP)
		{
			// Move the history up
			HistoryUp();

			return true;
		}
		else if(dwChar == VK_DOWN)
		{
			// Move the history down
			HistoryDown();

			return true;
		}
	}
	else if(uMsg == WM_KEYDOWN)
	{
		if(dwChar == VK_BACK)
		{
			// Is the input enabled?
			if(m_bInputVisible)
			{
				// Is there any input to delete?
				if(m_strInputText.GetLength() > 0)
				{
					// Resize the input
					m_strInputText.Resize((m_strInputText.GetLength() - 1));

					// Set the input
					SetInput(m_strInputText);

					return true;
				}
			}
		}
		else if(dwChar == VK_PRIOR)
		{
			// Scroll the page up
			ScrollUp();

			return true;
		}
		else if(dwChar == VK_NEXT)
		{
			// Scroll the page down
			ScrollDown();

			return true;
		}
	}
	else if(uMsg == WM_CHAR)
	{
		if(dwChar == 't' || dwChar == 'T' || dwChar == '`') // 0x54
		{
			// Is the input disabeld, we're not paused and not in the map ?
			if(!m_bInputVisible && !m_bPaused && !m_bMap)
			{
				// Enable the input
				SetInputVisible(true);

				// Lock the player controls
				g_pCore->GetGame()->GetLocalPlayer()->SetPlayerControlAdvanced(false,false);
				return true;
			}
		}

		// Is the input enbaled?
		if(m_bInputVisible)
		{
			// Is the char a valid input?
			if(dwChar >= ' ')
			{
				// We haven't exceeded the max input
				if(m_strInputText.GetLength() < CHAT_MAX_CHAT_LENGTH)
				{
					// Add the character to the input text
					m_strInputText += (char)dwChar;

					// Set the input
					SetInput(m_strInputText);
				}

				return true;
			}
		}
	}

	return false;
}

void CChat::ProcessInput()
{
	// Was anything entered?
	if(m_strInputText.GetLength() > 0)
	{
		// Is the input a command?
		bool bIsCommand = (m_strInputText.GetChar(0) == CHAT_COMMAND_CHAR);

		if(bIsCommand)
		{
			// Get the end of the command
			size_t sCommandEnd = m_strInputText.Find(" ");

			// If we don't have a valid end use the end of the string
			if (sCommandEnd == std::string::npos)
			{
				sCommandEnd = m_strInputText.GetLength();
			}

			// Get the command name
			std::string strCommand = m_strInputText.Substring(1, (sCommandEnd - 1));

			// Get the command parameters
			std::string strParams;

			// Do we have any parameters?
			if(sCommandEnd < m_strInputText.GetLength())
			{
				strParams = m_strInputText.Substring((sCommandEnd + 1), m_strInputText.GetLength());
			}

			AddToHistory();
			if(strCommand == "q" || strCommand == "quit" || strCommand == "exit")
			{
				/*// Are we connected to the network?
				if(g_pCore->GetNetworkModule()->IsConnected())
				{
					// Disconnect and shutdown RakNet
					pCore->GetNetworkModule()->Shutdown(500, false);
				}
				*/
				TerminateProcess(GetCurrentProcess(), 0);

				return;
			}
			else if(strCommand == "cv")
			{
				int iVehicleType = 90;

				CVector3 vecCreatePos; 
				g_pCore->GetGame()->GetLocalPlayer()->GetPosition(&vecCreatePos);

				CVehicleEntity * pVehicle = new CVehicleEntity(iVehicleType,vecCreatePos,0.0f,0,0,0,0);
				if(pVehicle)
				{
					//pVehicle->SetId(g_pCore->GetGame()->GetVehicleManager()->FindFreeSlot());

					pVehicle->Create();

					pVehicle->SetPosition(vecCreatePos);
					
					//pVehicle->SetModel (CIVModelManager::GetModelIndexFromHash(iVehicleType));
				}
			}
			else if(strCommand == "cp")
			{
				CVector3 vecCreatePos; 
				g_pCore->GetGame()->GetLocalPlayer()->GetPosition(&vecCreatePos);

				CPlayerEntity * pPlayer = new CPlayerEntity(false);
				if(pPlayer)
				{
					pPlayer->Create();

					pPlayer->Teleport(vecCreatePos);
				}
			}
			else if(strCommand == "spawn")
			{
				g_pCore->GetChat()->Output("Spawning local player ...",false);
				g_pCore->GetGame()->OnClientReadyToGamePlay();
			}
			else if(strCommand == "chat-renderlines")
			{
				if(strParams.size() <= 0)
					return Output("USE: /chat-renderlines [amount]", false);

				// Get the amount of lines to render
				int iRenderLines = atoi(strParams.c_str());

				if(iRenderLines <= 0 || iRenderLines > CHAT_RENDER_LINES)
					return Output("USE: /chat-renderlines [amount]", false);

				// Set the render lines amount
				CVAR_SET_INTEGER("chat-renderlines", iRenderLines);
				m_iRenderLines = iRenderLines;

				// Save the settings
				CSettings::Save();

				Outputf(false, " -> Chat render lines set to %d.", iRenderLines);
				return;
			}
		}

		if(!bIsCommand)
		{
			// Temporary(to print messages, until we've added the network manager
			CString strInput = m_strInputText.Get();
			Outputf(false, "%s:%s", g_pCore->GetNick().Get(), m_strInputText.Get());
			AddToHistory();
		}

		// Is the network module instance valid?
		/*if(pCore->GetNetworkModule())
		{
			// Are we connected?
			if(pCore->GetNetworkModule()->IsConnected())
			{
				RakNet::BitStream bitStream;
				RakNet::RakString strInput;

				// Check if we have a valid string(otherwise if we don't check it -> crash)
				String Checkstring;
				Checkstring.Append(m_strInputText.Get());
				for(int i = 0; i < m_strInputText.GetLength(); i++)
				{
					if(Checkstring[i] >= 'a' && Checkstring[i] <= 'z')
						continue;
					if(Checkstring[i] >= 'A' && Checkstring[i] <= 'Z')
						continue;
					if(Checkstring[i] >= '0' && Checkstring[i] <= '9')
						continue;
					if(Checkstring[i] == '[' || Checkstring[i] == ']' || Checkstring[i] == '(' || Checkstring[i] == ')')
						continue;
					if(Checkstring[i] == '_' || Checkstring[i] == ' ')
						continue;
					if(Checkstring[i] == '.' || Checkstring[i] == ':' || Checkstring[i] == ',' || Checkstring[i] == ';');
						continue;

					return Output("Unkown message input, please use only words from a-z", false);
				}

				// Is this a command?
				if(bIsCommand)
				{
					// Write 1
					bitStream.Write1();

					// Set the input minus the command character
					strInput = (m_strInputText.Get() + 1);
				}
				else
				{
					// Write 0
					bitStream.Write0();

					// Set the input
					strInput = m_strInputText.Get();

					// 
					Outputf(true, "#%s%s#FFFFFF: %s", String::DecimalToString(pCore->GetPlayerManager()->GetLocalPlayer()->GetColour()).Get(), pCore->GetNick().Get(), m_strInputText.Get());
				}

				// Write the input
				bitStream.Write(strInput.C_String());

				// Send it to the server
				pCore->GetNetworkModule()->Call(RPC_PLAYER_CHAT, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, true);

				// Add this message to the history
				AddToHistory();
			}
		}*/
	}
}

void CChat::SetInput(CString strText)
{
	// Clear the current line
	m_InputLine.Clear();

	CColor color = m_InputTextColor;
	const char * szRemainingText = m_InputLine.Format(strText.Get(), (CHAT_WIDTH - m_InputLine.m_Prefix.GetWidth()), color, false);

	CChatLine * pLine = NULL;

	while(szRemainingText && m_InputLine.m_ExtraLines.size() < 2)
	{
		m_InputLine.m_ExtraLines.resize(m_InputLine.m_ExtraLines.size() + 1);
		CChatLine& line = *(m_InputLine.m_ExtraLines.end() - 1);
		szRemainingText = line.Format(szRemainingText, CHAT_WIDTH, color, false);
	}

	if(strText != m_strInputText)
		m_strInputText = strText;

	if(szRemainingText)
		m_strInputText.Resize((szRemainingText - strText.Get()));
}

void CChat::ScrollUp()
{
	
}

void CChat::ScrollDown()
{
	
}

void CChat::AddToHistory()
{
	// Align the history
	AlignHistory();

	// Add the current mesasge to the history
	m_strHistory[0] = GetInput();

	// Reset the current history
	m_iCurrentHistory = -1;

	// Increase the total history
	if(m_iTotalHistory < CHAT_MAX_HISTORY)
		m_iTotalHistory ++;
}

void CChat::AlignHistory()
{
	// Loop through all the history items
	for(unsigned int i = (CHAT_MAX_HISTORY - 1); i; i--)
	{
		// Align the current chat history item
		m_strHistory[i] = m_strHistory[i - 1];
	}
}

void CChat::HistoryUp()
{
	// Is there any history to move to?
	if(m_iCurrentHistory < CHAT_MAX_HISTORY && ((m_iTotalHistory - 1) > m_iCurrentHistory))
	{
		//
		if(m_iCurrentHistory == -1)
			m_strInputHistory = GetInput();

		// Increase the current history
		m_iCurrentHistory ++;

		// Is there no history here?
		if(m_strHistory[m_iCurrentHistory].GetLength() == 0)
		{
			// Decrease the current history
			m_iCurrentHistory --;
		}

		// Set the input
		SetInput(m_strHistory[m_iCurrentHistory]);
	}
}

void CChat::HistoryDown()
{
	// Can we move down?
	if(m_iCurrentHistory > -1)
	{
		// Decrease the current history
		m_iCurrentHistory --;

		//
		if(m_iCurrentHistory == -1)
			SetInput(m_strInputHistory);
		else
			SetInput(m_strHistory[m_iCurrentHistory]);
	}
}

CChatLine::CChatLine()
{
	m_bActive = false;
}

bool CChatLine::IsColorCode(const char * szColorCode)
{
	if(*szColorCode != '#')
		return false;

	bool bValid = true;

	for(int i = 0; i < 6; i++)
	{
		char c = szColorCode[ 1 + i ];
		if (!isdigit ((unsigned char)c) && (c < 'A' || c > 'F') && (c < 'a' || c > 'f'))
        {
            bValid = false;
            break;
        }
	}

	return bValid;
}

const char * CChatLine::Format(const char * szText, float fWidth, CColor& color, bool bColorCoded)
{
	float fCurrentWidth = 0.0f;
	m_Sections.clear();

	const char * szSectionStart = szText;
	const char * szSectionEnd = szText;
	const char * szLastWrapPoint = szText;
	 
	bool bLastSection = false;

	while(!bLastSection)
	{ 
		m_Sections.resize(m_Sections.size() + 1);

		CChatLineSection& section = *(m_Sections.end() - 1);
		section.SetColor(color);

		if(m_Sections.size() > 1 && bColorCoded)
			szSectionEnd += 7;
		 
		szSectionStart = szSectionEnd;
		szLastWrapPoint = szSectionStart;
		 
		while(true)
		{
			float fCharWidth = CChat::GetCharacterWidth(*szSectionEnd);
			if(*szSectionEnd == '\0' || *szSectionEnd == '\n' || (fCurrentWidth + fCharWidth) > fWidth)
			{
				bLastSection = true;
				break;
			} 
			if(bColorCoded && IsColorCode(szSectionEnd))
			{
				unsigned long ulColor = 0;
				sscanf_s(szSectionEnd + 1, "%06x", &ulColor);
				color = CColor(((ulColor >> 16) & 0xFF), ((ulColor >> 8) & 0xFF), (ulColor & 0xFF), 255);
				break;
			} 
			if(isspace((unsigned char) *szSectionEnd) || ispunct((unsigned char) *szSectionEnd))
			{
				szLastWrapPoint = szSectionEnd;
			}
			 
			fCurrentWidth += fCharWidth;
			szSectionEnd++;
		}
		 
		section.m_strText.assign(szSectionStart, szSectionEnd - szSectionStart);
	}

	if(*szSectionEnd == '\0')
	{
		return NULL;
	}
	else if(*szSectionEnd == '\n')
	{
		return szSectionEnd + 1;
	}
	else
	{ 
		// Word wrap
		if(szLastWrapPoint == szSectionStart)
		{
			if(szLastWrapPoint == szText)
				return szSectionEnd;
			else
				m_Sections.pop_back();
		}
		else
		{ 
			(*(m_Sections.end() - 1)).m_strText.resize(szLastWrapPoint - szSectionStart);
		}
		return szLastWrapPoint;
	}
}

void CChatLine::Draw(float fX, float fY, unsigned char ucAlpha, bool bShadow)
{
	float fOffsetX = fX;
	std::vector< CChatLineSection >::iterator iter = m_Sections.begin();

	for(; iter != m_Sections.end(); iter++)
	{
		(*iter).Draw(fOffsetX, fY, ucAlpha, bShadow);
		fOffsetX += (*iter).GetWidth();
	}
}

float CChatLine::GetWidth()
{
	if(m_Sections.size() < 1)
		return 0.0f;

	float fWidth = 0.0f;
    std::vector < CChatLineSection >::iterator it;
    for (it = m_Sections.begin (); it != m_Sections.end(); it++)
    {
        fWidth += (*it).GetWidth ();
    }
    return fWidth;
}

void CChatInputLine::Draw(float fX, float fY, unsigned char ucAlpha, bool bShadow)
{
	CColor colPrefix;
	m_Prefix.GetColor(colPrefix);

	if(colPrefix.A > 0)
		m_Prefix.Draw(fX, fY, colPrefix.A, bShadow);

	CChat * g_pChat = g_pCore->GetChat();
	if(g_pChat->m_InputTextColor.A > 0 && m_Sections.size() > 0)
	{
		m_Sections[ 0 ].Draw(fX + m_Prefix.GetWidth(), fY, g_pChat->m_InputTextColor.A, bShadow);

		float fLineDifference = CChat::GetFontHeight();

		std::vector< CChatLine >::iterator iter = m_ExtraLines.begin();

		for(; iter != m_ExtraLines.end(); iter++)
		{
			fY += fLineDifference;
			(*iter).Draw(fX, fY, g_pChat->m_InputTextColor.A, bShadow);
		}
	}
}

void CChatInputLine::Clear()
{
	m_Sections.clear();
	m_ExtraLines.clear();
}

CChatLineSection::CChatLineSection()
{
	m_fCachedWidth = -1.0f;
	m_uiCachedLength = 0;
	m_fCachedOnScaleX = 0.0f;
}

CChatLineSection::CChatLineSection(const CChatLineSection& other)
{
	*this = other;
}

CChatLineSection& CChatLineSection::operator = (const CChatLineSection& other)
{
	m_strText = other.m_strText;
	m_Color = other.m_Color;
	m_fCachedWidth = other.m_fCachedWidth;
	m_uiCachedLength = other.m_uiCachedLength;
	m_fCachedOnScaleX = other.m_fCachedOnScaleX;
	return *this;
}

void CChatLineSection::Draw(float fX, float fY, unsigned char ucAlpha, bool bShadow)
{
	if(!m_strText.empty() && ucAlpha > 0)
	{
		g_pCore->GetGraphics()->DrawText(fX, fY, D3DCOLOR_ARGB(ucAlpha, 255, 255, 255), 1.0f, 1, DT_NOCLIP, bShadow, m_strText.c_str());
	}
}

float CChatLineSection::GetWidth()
{
	if (m_fCachedWidth < 0.0f || m_strText.size () != m_uiCachedLength || g_pCore->GetChat()->m_fX != m_fCachedOnScaleX)
    {
        m_fCachedWidth = 0.0f;
        for (unsigned int i = 0; i < m_strText.size (); i++)
        {
            m_fCachedWidth += CChat::GetCharacterWidth(m_strText[ i ]);            
        }
        m_uiCachedLength = m_strText.size ();
		m_fCachedOnScaleX = g_pCore->GetChat()->m_fX;
    }
    return m_fCachedWidth;
}