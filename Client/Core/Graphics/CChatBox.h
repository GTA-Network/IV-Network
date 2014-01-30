
#ifndef CChatBox_h
#define CChatBox_h

#include <Common.h>
#include "CGUI.h"

/** This stores the text the player has entered into the entrybox of
* the console/chat window.  It keeps all the commands that the player
* has entered in sequential order, either chat phrases or /commands.
*/
class CChatHistory
{
private:
	/// the current position
	unsigned int index;
	const char* empty;

	/// array of strings to store our history
	std::vector<std::string> history;

public:
	CChatHistory() { index = 0; empty = ""; }

	/// add a new string, the last one typed
	void Add(const char* str)
	{
		std::string cmd = str;
		history.push_back(cmd);
		index = history.size();
	}

	/// Get a string from the history
	const char* GetCommand(unsigned int n)
	{
		if (history.size() == 0)
		{
			return 0;
		}

		if (n >= history.size())
		{
			return history.back().c_str();
		}
		else
			return history[n].c_str();
	}

	/// Return the next command from history (empty for the last)
	const char* GetNext()
	{
		if (index < history.size() - 1)
			index++;
		else
			return empty;

		return GetCommand(index);
	}

	/// Return the previous command from history
	const char* GetPrev()
	{
		if (index > 0)
			index--;

		return GetCommand(index);
	}
};

class CChatBox
{
private:
	CGUI			* m_pGUI;
	CEGUI::Window	* m_pChatWindow;
	CEGUI::Listbox	* m_pChatOutputWindow;
	CEGUI::Editbox	* m_pInputBox;

	CChatHistory	* m_pChatHistory;
	bool			m_bVisible;

	bool Event_KeyPressed(const CEGUI::EventArgs& e);
	bool Event_EditTextAccepted(const CEGUI::EventArgs& e);
public:
	CChatBox(CGUI * pGUI);
	~CChatBox();

	bool	Initialize();

	void	Output(const char* szText);
	void	Outputf(const char* szText, ...);

	bool	IsVisible() { return m_bVisible; }
	void	SetVisible(bool bVisible);
	bool	IsEnabled();

	CString	GetInputText();

	void	Enable();
	void	Disable();
};

#endif // CChatBox_h