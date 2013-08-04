//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CChat.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CChat_h
#define CChat_h

#include <Common.h>
#include <Windows.h>

#define			CHAT_MAX_LINES			10
#define			CHAT_CMD_CHAR			'/'

class CChatLine {

private:

	bool							m_bActive;
	CString							m_strText;

public:

	CChatLine( );
	~CChatLine( ) { };

	void							Draw( float fX, float fY, bool bShadow );

	void							SetActive( bool bActive ) { m_bActive = bActive; }
	bool							IsActive( ) { return m_bActive; }

	void							SetText( CString strText ) { m_strText = strText; }
	CString							GetText( ) { return m_strText; }

};

class CChat {

private:

	float							m_fX;
	float							m_fY;
	unsigned int					m_uiNumLines;
	unsigned int					m_uiMostRecentLine;
	bool							m_bVisible;
	bool							m_bInputVisible;

	CString							m_strInputPrefix;
	CString							m_strCurrentInput;

	CChatLine						m_pChatLine[ CHAT_MAX_LINES ];

public:

	CChat( float fX, float fY );
	~CChat( void );

	void					Render( void );

	void					SetVisible( bool bVisible ) { m_bVisible = bVisible; }
	bool					IsVisible( void ) { return m_bVisible; }

	void					SetInputVisible( bool bVisible ) { m_bInputVisible = bVisible; }
	bool					IsInputVisible( void ) { return m_bInputVisible; }

	void					SetInputPrefix( CString strInputPrefix ) { m_strInputPrefix = strInputPrefix; }
	CString					GetInputPrefix( void ) { return m_strInputPrefix; }

	CString					GetInput( void ) { return m_strCurrentInput; }

	void					Clear( void );
	void					ClearInput( bool bHideInput = true );

	void					Output( const char * szFormat, ... );
	bool					HandleUserInput( unsigned int uMsg, DWORD dwChar );

	void					ProcessInput( void );

};

#endif // CChat_h