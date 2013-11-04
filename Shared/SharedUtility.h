//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: SharedUtility.h
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef SharedUtility_h
#define SharedUtility_h

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#else
#include <sys/time.h>
#if !defined(_DWORD_DEF)
typedef unsigned long DWORD;
#define _DWORD_DEF
#endif
#endif

#include <string>
#include "Common.h"
#include "CString.h"


namespace SharedUtility
{
	// Strip a path from a string array and
	// return weather or not the path was stripped
	bool StripPath1(char * szString);

	// Return the stripped path from a string
	// pointer but don't edit the actual pointer
	char * StripPath2(char * szString);

	// Return the current applications path
	const char * GetAppPath();

	// Return the current executables path
	const char * GetExePath();

	// Prepend the application path to the string provided
	CString GetAbsolutePath(const char * szFormat, ...);

	// Return the filename from the path
	CString FileNameFromPath(CString strPath);

#ifdef _WIN32
	// Inject the library into the specified process
	int InjectLibraryIntoProcess(HANDLE hProcess, const char * szLibraryPath);

	// Get the process id's handle then inject the library into it
	int InjectLibraryIntoProcess(DWORD dwProcessId, const char * szLibraryPath);

	// Get the process id from the process name (If it is running)
	bool GetProcessIdFromProcessName(char * szProcessName, DWORD * dwProcessId);

	// Return weather the specified process is running
	bool IsProcessRunning(char * szProcessName);

	// Terminate the specified process
	bool _TerminateProcess(char * szProcessName);

	// Read a string from the registry
	bool ReadRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, const char * szDefault, char * szData, DWORD dwSize);

	// Write a string to the registry
	bool WriteRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, char * szData, DWORD dwSize);

	// Convert an Ansi string to a Unicode string
	int AnsiToUnicode(const char * szAnsiString, size_t sAnsiStringLength, wchar_t * wszUnicodeString, size_t sUnicodeStringLength, DWORD dwFlags = NULL);

	// Convert a Unicode string to an Ansi string
	int UnicodeToAnsi(const wchar_t * wszUnicodeString, size_t sUnicodeStringLength, char * szAnsiString, size_t sAnsiStringLength, DWORD dwFlags = NULL);

	// Set the text in the windows clipboard
	bool SetClipboardText(const char * szString, size_t sStringSize);

	// Get the text in the windows clipboard
	const char * GetClipboardText();
#endif

	// Returns the current time and date in the
	// format 'DOW MO DY HR:MN:SC YR'
	const char * GetTimeAndDateString();

	// Returns the current time in the format
	// 'YYYY-MM-DD HR:MN:SC'
	const char * GetTimeAndDateString2();

	// Returns the current time in the format
	// 'HR:MN:SC'
	const char * GetTimeString();

	// TODO: TimeInit and TimeShutdown from Networked: IV
	// 
	unsigned long GetTime();

	// Check if a path exists
	bool Exists(const char * szPath);

	// Copy a file to another file
	bool CopyFile(const char * szSource, const char * szDestination);

	// Creates a directory
	int CreateDirectory(const char * szPath);

	// Parts taken from SparkIV
	// All of the IV hash functions merged into one
	unsigned int IVHash(std::string strString, unsigned int uiInitialHash = 0, bool bEnsureLowercase = true);

	// Replacement for inet_ntop
	const char * inet_ntop(int af, const void * src, char * dst, int cnt);

	// Replacement for inet_pton
	int inet_pton(int af, const char * src, void * dst);

	// Remove illegal characters from a file name
	CString RemoveIllegalCharacters(CString& strFileName);

	// Return a string with the amount of time passed from the specified time
	CString GetTimePassedFromTime(unsigned long ulTick);

#ifdef _CLIENT
	DWORD				GetSerial();
	CString				GetSerialHash();
#endif

	// Define registrys
	void DefineGameRegistryEntires();
	void CheckGameDirectoryExists();
	void CreateBasicMPDirectories();

	CString	DiconnectReasonToString(unsigned int uiReason);

	bool GetHTTPData(CString host, CString page, CString &buffer);
}

#endif