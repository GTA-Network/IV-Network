#ifndef CCHAT_H
#define CCHAT_H

class CChat
{
private:
	bool m_bVisible;
	CString m_szMessages[CHAT_MAX_LINES];
	bool m_bTypeing;
	CString m_szTypeing;

public:
	CChat();
	~CChat();

	void SetVisible(bool bVisible) { m_bVisible = bVisible; }

	void Render();

	void Print(CString text);

	void HandleUserInput(unsigned int uMsg, WPARAM dwChar);
	void Clear();
};

#endif