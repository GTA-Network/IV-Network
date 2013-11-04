//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CChat.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CCHAT_H
#define CCHAT_H

class CChat {
private:
	bool		m_bVisible;
	CString		m_szMessages[CHAT_MAX_LINES];
	bool		m_bTypeing;
	CString		m_szTypeing;
	int			m_iCurrent;
	CString		m_szPlayerMessages[CHAT_MAX_LINES];
	int			m_iScroll;
	int			m_iPos;
	bool		m_bInsert;

public:
				CChat();
				~CChat();

	void		SetVisible(bool bVisible) { m_bVisible = bVisible; }

	void		Render();

	void		Print(CString text);

	void		HandleUserInput(unsigned int uMsg, WPARAM dwChar);
	void		Clear();

private:
	void		Log(CString text);
};

#endif