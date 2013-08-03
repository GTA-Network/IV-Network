//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CInput.cpp
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#include "CInput.h"

extern bool g_bClose;

void CInput::InputThread(CThread* pThread)
{
	CString strInput = GetInput();
	while(true)
	{
		if(strInput == "quit")
			g_bClose = true;
	}
}


CString CInput::GetInput()
{
	char szInputBuffer[512]; // Buffer MUST be 3 or more (input char, \n, \0)
	CString strInputString;

	// Wait for input from the console
	// TODO: Make non-blocking
	fgets(szInputBuffer, sizeof(szInputBuffer), stdin);

	// Do we have anything in the input?
	if(szInputBuffer[0] != '\n')
	{
		// Append the input to the input string
		strInputString += szInputBuffer;

		// Get the input string length
		size_t sLength = strInputString.GetLength();

		// Is this the last of the input?
		if(strInputString[sLength - 1] == '\n')
		{
#ifdef _WIN32
			// Replace '\n' with '\0'
			strInputString.Truncate(sLength - 1);
#else
			// Replace '\r\n' with '\0'
			strInputString.Truncate(sLength - 2);
#endif

			// Return the input
			return strInputString;
		}
	}
	return strInputString;
}