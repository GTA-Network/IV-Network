//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: Input.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include <algorithm>
#include <list>
#include "Input.h"
#include <CString.h>

WNDPROC m_wWndProc = NULL;
bool bHUDDisabled = false;
//bool m_bWindowFocused = true;

std::list<CString> pressedKeys;

CString GetKeyNameByCode(DWORD dwCode)
{
	CString strCode;

	if(dwCode >= 0x30 && dwCode <= 0x39)
	{
		// 0-9
		strCode = (unsigned char)dwCode;
	}
	else if(dwCode >= 0x41 && dwCode <= 0x5A)
	{
		// lower case ascii a-z
		strCode = (unsigned char)(dwCode+0x20);
	}
	else if(dwCode >= VK_NUMPAD0 && dwCode <= VK_NUMPAD9)
	{
		strCode.Format("num_%d", dwCode-VK_NUMPAD0);
	}
	else if(dwCode >= VK_F1 && dwCode <= VK_F12)
	{
		strCode.Format("f%d", dwCode-VK_F1+1);
	}
	else
	{
		switch(dwCode)
		{
			case VK_TAB:
					strCode = "tab"; break;
			case VK_RETURN:
					strCode = "enter"; break;
			case VK_CONTROL:
					strCode = "ctrl"; break;
			case VK_SHIFT:
					strCode = "shift"; break;
			case VK_MENU:
					strCode = "alt"; break;
			case VK_ADD:
					strCode = "num_add"; break;
			case VK_SUBTRACT:
					strCode = "num_sub"; break;
			case VK_DIVIDE:
					strCode = "num_div"; break;
			case VK_MULTIPLY:
					strCode = "num_mul"; break;
			case VK_SPACE:
					strCode = "space"; break;
			case VK_LEFT:
					strCode = "arrow_left"; break;
			case VK_RIGHT:
					strCode = "arrow_right"; break;
			case VK_UP:
					strCode = "arrow_up"; break;
			case VK_DOWN:
					strCode = "arrow_down"; break;
			case VK_PRIOR:
					strCode = "page_up"; break;
			case VK_NEXT:
					strCode = "page_down"; break;
			case VK_END:
					strCode = "end"; break;
			case VK_HOME:
					strCode = "home"; break;
			case VK_INSERT:
					strCode = "insert"; break;
			case VK_DELETE:
					strCode = "delete"; break;
			case 0x1E:
					strCode = "backspace"; break;
			case 0x01:
					strCode = "esc"; break;
			case 0xC4: //german "umlaute"
					strCode = "ä"; break;
			case 0xE4:
					strCode = "ä"; break;
			case 0xD4:
					strCode = "ö"; break;
			case 0xF4:
					strCode = "ö"; break;
			case 0xDC:
					strCode = "ü"; break;
			case 0xFC:
					strCode = "ü"; break;

		}
	}

	return strCode;
}

bool HandleKeyInput(DWORD dwKey)
{
	switch(dwKey)
	{
	case VK_PRIOR: // Page Up
		// Does the chat window exist and is it enabled?
		/*if(g_pChatWindow && g_pChatWindow->IsEnabled())
		{
			// Move the chat window page upwards
			g_pChatWindow->PageUp();
			return true;
		}*/
		break;
	case VK_NEXT: // Page Down
		// Does the chat window exist and is it enabled?
		/*if(g_pChatWindow && g_pChatWindow->IsEnabled())
		{
			// Move the chat window page downwards
			g_pChatWindow->PageDown();
			return true;
		}*/
		break;
	}

	return false;
}

LRESULT APIENTRY WndProc_Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	return CallWindowProc(m_wWndProc, hWnd, uMsg, wParam, lParam);
}
