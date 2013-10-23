//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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
#include <d3d9.h>
#include <list>

class CChatLineSection {
public:

	std::string				m_strText;
	CColor					m_Color;
	float					m_fCachedWidth;
	unsigned int			m_uiCachedLength;
	float					m_fCachedOnScaleX;
	std::string				m_strTimestamp;
							
							CChatLineSection		();
							CChatLineSection		(const CChatLineSection& other);
	CChatLineSection&		operator =				(const CChatLineSection& other);
	inline bool				operator==				(const CChatLineSection& other)
	{
	return (m_strText == m_strText
	&& !memcmp(&m_Color, &m_Color, sizeof(m_Color)) 
	&& m_fCachedWidth == m_fCachedWidth
	&& m_uiCachedLength == m_uiCachedLength 
	&& m_fCachedOnScaleX == m_fCachedOnScaleX);
	}

	void					Draw					(float fX, float fY, unsigned char ucAlpha, bool bShadow);

	void					SetText					(CString strText) { m_strText = strText; }
	CString					GetText					() { return CString(m_strText.c_str()); }

	inline	void			SetColor				(CColor& color) { m_Color = color; }
	inline	void			GetColor				(CColor& color) { color = m_Color; }

	float					GetWidth				();

};

class CChatLine
{

public:

	bool											m_bActive;
	std::list< CChatLineSection >					m_Sections;

							CChatLine				();
							~CChatLine				() { };

	bool					IsColorCode				(const char * szColorCode);
	CString					RemoveColorCodes		(const char * szText);
	const char				* Format				(const char * szText, float fWidth, CColor& color, bool bColorCoded);
	void					Draw					(float fX, float fY, unsigned char ucAlpha, bool bShadow);

	void					SetActive				(bool bActive) { m_bActive = bActive; }
	bool					IsActive				(void) { return m_bActive; }

	float					GetWidth				();

};

class CChatInputLine : public CChatLine
{

public:

	void					Draw					(float fX, float fY, unsigned char ucAlpha, bool bShadow);
	void					Clear					();

	CChatLineSection								m_Prefix;
	std::list< CChatLine >							m_ExtraLines;

};

class CChat
{

private:
	
	CChatLine				m_Lines[ CHAT_MAX_LINES ];
	CChatInputLine			m_InputLine;

	unsigned int			m_uiScrollOffset;
	float					m_fSmoothScroll;
	float					m_fSmoothLastTimeSeconds;
	float					m_fSmoothAllowAfter;
	float					m_fSmoothScrollResetTime;

	float					m_fX;
	float					m_fY;

	CString					m_strInputText;
	CString					m_strCommand;

	bool					m_bVisible;
	bool					m_bInputBlocked;
	bool					m_bInputVisible;
	bool					m_bPaused;
	bool					m_bMap;
	bool					m_bOldState;


	int						m_iRenderLines;
	unsigned int			m_uiNumLines;
	unsigned int			m_uiMostRecentLine;
	unsigned int			m_uiCurrentPageScroll;
	
	CColor					m_Color;
	CColor					m_TextColor;
	CColor					m_InputTextColor;


	int						m_iCurrentHistory;
	int						m_iTotalHistory;
	CString					m_strHistory[ CHAT_MAX_HISTORY ];
	CString					m_strInputHistory;

public:

							CChat					(float fX, float fY);
							~CChat					();

	void					Setup					(D3DPRESENT_PARAMETERS * pPresentParameters);
	void					Reset					();
	void					Render					(void);

	void					SetVisible				(bool bVisible) { m_bVisible = bVisible; }
	bool					IsVisible				() { return m_bVisible; }

	void					SetInputVisible			(bool bInputVisible);
	bool					IsInputVisible			() { return m_bInputVisible; }

	void					SetInput				(CString strInput);
	CString					GetInput				() { return m_strInputText; }

	void					SetInputPrefix			(CString strInputPrefix) { m_InputLine.m_Prefix.SetText(strInputPrefix); }
	CString					GetInputPrefix			() { return m_InputLine.m_Prefix.GetText(); }

	CColor					GetTextColor			() { return m_TextColor; }
	CColor					GetInputTextColor		() { return m_InputTextColor; }

	float					GetPosition				(bool bPositionType = false);

	void					Output					(const char * szText, bool bColorCoded = false);
	void					Outputf					(bool bColorCoded, const char * szFormat, ...);

	void					Clear					();
	void					ClearInput				();

	static	float			GetFontHeight			();
	static	float			GetCharacterWidth		(int iChar);

	void					ScrollUp				();
	void					ScrollDown				();

	bool					HandleUserInput			(unsigned int uMsg, DWORD dwChar);
	void					ProcessInput			();

	void					UpdateSmoothScroll		(float * pfPixelScroll, int * piLineScroll);

	bool					IsPaused				() { return m_bPaused; }
	bool					IsMapShowing			() { return m_bMap; }

	void					AddToHistory			();
	void					AlignHistory			();
	void					HistoryUp				();
	void					HistoryDown				();

};

#endif // CChat_h