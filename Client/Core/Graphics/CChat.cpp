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
extern CCore * g_pCore;

CChat::CChat( float fX, float fY )
{
	// Store the screen position
	m_fX = fX + 5.0f;
	m_fY = fY;

	// Reset variables
	SetVisible( true );
	SetInputVisible( false );
	m_uiNumLines = CHAT_MAX_LINES;
	m_uiMostRecentLine = 0;

	// Set the default input prefix
	SetInputPrefix( ">" );
}

CChat::~CChat( )
{

}

void CChat::Render( )
{
	// Is the chat window not visible?
	if( !IsVisible() )
		return;

	// Calculate the Y coordinate
	float fLineDifference = ( g_pCore->GetGraphics()->GetFontHeight() + 3.0f );
	float fOffsetY = ( CHAT_MAX_LINES * fLineDifference + 10.0f );

	unsigned int uiLine = ( m_uiMostRecentLine % CHAT_MAX_LINES );
	unsigned int uiLinesDrawn = 0;

	// Loop over all chat lines
	while( m_pChatLine[ uiLine ].IsActive() && uiLinesDrawn < m_uiNumLines )
	{
		// Draw the current chatline
		m_pChatLine[ uiLine ].Draw( m_fX, fOffsetY, true );

		// Adjust the offset
		fOffsetY -= fLineDifference;

		// Increase the total drawn lines
		uiLine = ( uiLine + 1 ) % CHAT_MAX_LINES;
		uiLinesDrawn++;

		// Is this line the end?
		if( uiLine == m_uiMostRecentLine )
			break;
	}

	// Is the input visible?
	if( IsInputVisible() )
	{
		g_pCore->GetGraphics()->DrawText( m_fX, ( m_fY + CHAT_MAX_LINES * fLineDifference + 10.0f ), D3DCOLOR_ARGB( 255, 255, 255, 255 ), 1.0f, 1, DT_NOCLIP, true, "%s %s", GetInputPrefix().Get(), GetInput().Get() );
	}
}

void CChat::Clear( )
{
	// Loop for all messages.
	for(int i = 0; i < CHAT_MAX_LINES; i++)
	{
		// Clear line text.
		m_pChatLine[i].SetText("");
	}
}

void CChat::ClearInput( bool bHideInput )
{
	// Clear the current input
	m_strCurrentInput.Clear();

	// Should we hide the input window?
	if( bHideInput )
	{
		// Hide the input
		SetInputVisible( false );
	}
}

void CChat::Output( const char * szFormat, ... )
{
	// Get the string arguments
	char szBuffer[ 2048 ];
	va_list vArgs;
	va_start( vArgs, szFormat );
	vsprintf( szBuffer, szFormat, vArgs );
	va_end( vArgs );

	CChatLine * pChatLine = NULL;
	
	m_uiMostRecentLine = ( m_uiMostRecentLine == 0 ? CHAT_MAX_LINES - 1 : m_uiMostRecentLine - 1 );
	pChatLine = &m_pChatLine[ m_uiMostRecentLine ];

	// Print the stuff in the chatlog
	CLogFile::Printf(szBuffer);

	// Is the line valid?
	if( pChatLine )
	{
		// Set the chat line text
		pChatLine->SetText( szBuffer );

		// Set the chat line active
		pChatLine->SetActive( true );
	}
}

bool CChat::HandleUserInput( unsigned int uMsg, DWORD dwChar )
{
	if( uMsg == WM_CHAR )
	{
		// Is the input not visible?
		if( !IsInputVisible() )
		{
			// Was the t key pressed?
			if( dwChar == 't' || dwChar == 'T' )
			{
				// Set the input visible
				SetInputVisible( true );

				return true;
			}
		}
		else
		{
			// Is the character valid?
			if( dwChar >= ' ' )
			{
				// Add the character to the current input
				m_strCurrentInput.Append( (unsigned char)dwChar );

				return true;
			}
		}
	}
	else if( uMsg == WM_KEYDOWN )
	{
		// Was the backspace key pressed?
		if( dwChar == VK_BACK )
		{
			// Is there anything to delete?
			if( GetInput().GetLength() > 0 )
			{
				// Delete the last character from the input
				m_strCurrentInput.Erase( (GetInput().GetLength() - 1), 1 );
			}

			return true;
		}
	}
	else if( uMsg == WM_KEYUP )
	{
		// Was the return key pressed?
		if( dwChar == VK_RETURN )
		{
			// Is the input visible?
			if( IsInputVisible() )
			{
				// Is there any input?
				if( GetInput().GetLength() > 0 )
				{
					// Process the input
					ProcessInput( );

					// Clear the current input
					ClearInput( );

					return true;
				}
				else
				{
					// Clear any current input and hide the input window (failsafe)
					ClearInput( );

					return true;
				}
			}
		}
	}

	return false;
}

CChatLine::CChatLine( )
{
	// Mark as not active
	SetActive( false );
}

void CChatLine::Draw( float fX, float fY, bool bShadow )
{
	g_pCore->GetGraphics()->DrawText( fX, fY, D3DCOLOR_ARGB( 255, 255, 255, 255 ), 1.0f, 1, DT_NOCLIP, bShadow, "%s", m_strText.Get() );
}

void CChat::ProcessInput( void )
{
	// Is there any input to process?
	if( GetInput().GetLength() > 0 )
	{
		// Is this a command?
		bool bIsCommand = (GetInput().GetChar(0) == CHAT_CMD_CHAR);

		// If this a command
		if( bIsCommand )
		{
			// Was this the quit command?
			if( GetInput() == "q" || GetInput() == "quit" || GetInput() == "exit" )
			{
				/*// Is the network connected?
				if( g_pCore->GetGame()->GetNetworkModule()->IsConnected() )
				{
					// Disconnect from the network
					g_pCore->GetGame()->GetNetworkModule()->Disconnect( );
				}*/

				// Terminate the current process
				TerminateProcess( GetCurrentProcess(), 0 );

				// Don't process this command anymore
				return;
			}
		}
		
		// Is the network module instance valid?
		/*if( g_pClient->GetGame()->GetNetworkModule() )
		{
			// Are we connected to a server?
			if( g_pClient->GetGame()->GetNetworkModule()->IsConnected() )
			{
				BitStream bitStream;
				RakString strInput;

				// Is this a command?
				if( bIsCommand )
				{
					// Write a 1
					bitStream.Write1();

					// Set the input, missing the command char
					strInput = (GetInput().Get() + 1);
				}
				else
				{
					// Write a 0
					bitStream.Write0();

					// Set the input
					strInput = GetInput().Get();

					// Ouput the message to the chat window
					Output( "%s: %s", g_pClient->GetNick().Get(), GetInput().Get() );
				}

				// Write the input
				bitStream.Write( strInput );

				// Send it to the server
				g_pClient->GetGame()->GetNetworkModule()->Call( RPC_PLAYER_CHAT, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, true );
			}
		}*/
	}
}