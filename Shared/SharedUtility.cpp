//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: SharedUtility.cpp
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "SharedUtility.h"
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <mmsystem.h>
#include <sys/stat.h>
#include <direct.h>
#include <WS2tcpip.h>
#include <tlhelp32.h>
#include <md5/md5.h>
#else
#define stricmp strcasecmp
#define vsprintf_s vsprintf
#define vsnprintf_s vsnprintf
#define sprintf_s sprintf
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <limits.h>
#include <unistd.h>
#endif

#ifndef _WIN32
#define MAX_PATH PATH_MAX
#endif

namespace SharedUtility
{
	// Strip a path from a string array and
	// return weather or not the path was stripped
	bool StripPath1(char * szString)
	{
		for(size_t i = strlen(szString); i > 0; --i)
		{
#ifdef _WIN32
			if(szString[i] == '\\')
#else
			if(szString[i] == '/')
#endif
			{
				szString[i + 1] = '\0';
				return true;
			}
		}

		return false;
	}

	// Return the stripped path from a string
	// pointer but don't edit the actual pointer
	char * StripPath2(char * szString)
	{
		char * szPath = szString;
		char * szStrippedPath = (szString + strlen(szString));

		while(szStrippedPath != szPath)
		{
#ifdef _WIN32
			if(*szStrippedPath == '\\')
#else
			if(*szStrippedPath == '/')
#endif
				return (szStrippedPath + 1);

			szStrippedPath--;
		}

		return szPath;
	}

	const char * GetAppPath()
	{
#ifdef _WIN32
		static unsigned int nDummy;
#endif
		static char szAppPath[MAX_PATH];
#ifdef _WIN32
		HMODULE hModuleHandle;
		GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, 
			(LPCSTR)&nDummy, &hModuleHandle);
		GetModuleFileName(hModuleHandle, szAppPath, MAX_PATH);
#else
		readlink("/proc/self/exe", szAppPath, MAX_PATH);
#endif
		StripPath1(szAppPath);
		return szAppPath;
	}

	const char * GetExePath()
	{
		static char szExePath[MAX_PATH];
#ifdef _WIN32
		GetModuleFileName(GetModuleHandle(NULL), szExePath, MAX_PATH);
#else
		readlink("/proc/self/exe", szExePath, MAX_PATH);
#endif
		StripPath1(szExePath);
		return szExePath;
	}

	CString GetAbsolutePath(const char * szFormat, ...)
	{
		va_list args;
		char szBuffer[1024];
		va_start(args, szFormat);
		vsnprintf_s(szBuffer, sizeof(szBuffer), szFormat, args);
		va_end(args);
		return CString("%s%s", GetAppPath(), szBuffer);
	}

	CString FileNameFromPath(CString strPath)
	{
		// Find the last back slash
		unsigned int uiLastBackslash = strPath.ReverseFind('\\');

		// Find the last forward slash
		unsigned int uiLastForwardslash = strPath.ReverseFind('/');

		// Did we not find any slashes?
		if(uiLastBackslash == std::string::npos && uiLastForwardslash == std::string::npos)
		{
			// Return the path
			return strPath;
		}

		// Find the highest index out of the two last slashes
		unsigned int uiLastSlash = 0;
		{
			if(uiLastBackslash == std::string::npos)
				uiLastSlash = uiLastForwardslash;
			else if(uiLastForwardslash == std::string::npos)
				uiLastSlash = uiLastBackslash;
			else
				uiLastSlash = ((uiLastBackslash > uiLastForwardslash) ? uiLastBackslash : uiLastForwardslash);

			// Ignore the slash
			uiLastSlash++;
		}

		// Is the last slash invalid?
		if(uiLastSlash >= (strPath.GetLength() - 1))
		{
			// Return the path
			return strPath;
		}

		// Return the file name
		return strPath.Substring(uiLastSlash);
	}

#ifdef _WIN32
	int InjectLibraryIntoProcess(HANDLE hProcess, const char * szLibraryPath)
	{
		int iReturn = 0;

		// Get the length of the library path
		size_t sLibraryPathLen = (strlen(szLibraryPath) + 1);

		// Allocate the a block of memory in our target process for the library path
		void * pRemoteLibraryPath = VirtualAllocEx(hProcess, NULL, sLibraryPathLen, MEM_COMMIT, PAGE_READWRITE);

		// Write our library path to the allocated block of memory
		SIZE_T sBytesWritten = 0;
		WriteProcessMemory(hProcess, pRemoteLibraryPath, (void *)szLibraryPath, sLibraryPathLen, &sBytesWritten);

		if(sBytesWritten != sLibraryPathLen)
		{
			// Failed to write the library path
			iReturn = 1;
		}
		else
		{
			// Get the handle of Kernel32.dll
			HMODULE hKernel32 = GetModuleHandle("Kernel32");

			// Get the address of the LoadLibraryA function from Kernel32.dll
			FARPROC pfnLoadLibraryA = GetProcAddress(hKernel32, "LoadLibraryA");

			// Create a thread inside the target process to load our library
			HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pfnLoadLibraryA, pRemoteLibraryPath, 0, NULL);

			if(hThread)
			{
				// Wait for the created thread to end
				WaitForSingleObject(hThread, INFINITE);

				// Close our thread handle
				CloseHandle(hThread);
			}
			else
			{
				// Thread creation failed
				iReturn = 2;
			}
		}

		// Free the allocated block of memory inside the target process
		VirtualFreeEx(hProcess, pRemoteLibraryPath, sizeof(pRemoteLibraryPath), MEM_RELEASE);
		return iReturn;
	}

	int InjectLibraryIntoProcess(DWORD dwProcessId, const char * szLibraryPath)
	{
		// Open our target process
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

		if(!hProcess)
		{
			// Failed to open the process
			return 3;
		}

		// Inject the library into the process
		int iReturn = InjectLibraryIntoProcess(hProcess, szLibraryPath);

		// Close the process handle
		CloseHandle(hProcess);
		return iReturn;
	}

	bool GetProcessIdFromProcessName(char * szProcessName, DWORD * dwProcessId)
	{
		bool bReturn = false;

		// Create a tool help 32 process snapshot
		HANDLE hProcessSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if(!hProcessSnapShot)
			return false;

		PROCESSENTRY32 ProcessEntry;
		ProcessEntry.dwSize = sizeof(ProcessEntry);

		if(Process32First(hProcessSnapShot, &ProcessEntry))
		{
			// Enumerate through all processes
			while(Process32Next(hProcessSnapShot, &ProcessEntry))
			{
				// Check the process name to see if it matches szProcessName
				if(!strcmp(ProcessEntry.szExeFile, szProcessName))
				{
					// It matches, set the process id (if required) and return true
					if(dwProcessId)
						*dwProcessId = ProcessEntry.th32ProcessID;

					bReturn = true;
					break;
				}
			}
		}

		// Close the snapshot handle
		CloseHandle(hProcessSnapShot); 
		return bReturn;
	}

	bool IsProcessRunning(char * szProcessName)
	{
		// Simply return the value of GetProcessIdFromProcessName
		return GetProcessIdFromProcessName(szProcessName, NULL);
	}

	bool _TerminateProcess(char * szProcessName)
	{
		// Check if the process is running
		DWORD dwProcessId = 0;

		if(GetProcessIdFromProcessName(szProcessName, &dwProcessId))
		{
			// Attempt to open a handle to the process
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, dwProcessId);

			// Did the process handle open successfully?
			if(hProcess)
			{
				// Attempt to terminate the process
				if(TerminateProcess(hProcess, 0))
				{
					// Process terminated
					return true;
				}
			}
		}

		return false;
	}

	bool ReadRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, const char * szDefault, char * szData, DWORD dwSize)
	{
		HKEY hKey = NULL;

		if(RegOpenKeyEx(hKeyLocation, szSubKey, NULL, KEY_READ, &hKey) == ERROR_SUCCESS)
		{
			DWORD dwType = REG_SZ;
			LONG lStatus = RegQueryValueEx(hKey, szKey, NULL, &dwType, (BYTE *)szData, &dwSize);
			RegCloseKey(hKey);
			return (lStatus == ERROR_SUCCESS);
		}

		if(szDefault)
			strncpy(szData, szDefault, dwSize);

		return false;
	}

	bool WriteRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, char * szData, DWORD dwSize)
	{
		HKEY hKey = NULL;
		RegOpenKeyEx(hKeyLocation, szSubKey, NULL, KEY_WRITE, &hKey);

		if(!hKey)
			RegCreateKey(hKeyLocation, szSubKey, &hKey);

		if(hKey)
		{
			DWORD dwType = REG_SZ;
			RegSetValueEx(hKey, szKey, NULL, dwType, (BYTE *)szData, dwSize);
			RegCloseKey(hKey);
			return true;
		}

		return false;
	}

	int AnsiToUnicode(const char * szAnsiString, size_t sAnsiStringLength, wchar_t * wszUnicodeString, size_t sUnicodeStringLength, DWORD dwFlags)
	{
		return MultiByteToWideChar(CP_ACP, dwFlags, szAnsiString, sAnsiStringLength, wszUnicodeString, sUnicodeStringLength);
	}

	int UnicodeToAnsi(const wchar_t * wszUnicodeString, size_t sUnicodeStringLength, char * szAnsiString, size_t sAnsiStringLength, DWORD dwFlags)
	{
		return WideCharToMultiByte(CP_UTF8, dwFlags, wszUnicodeString, sUnicodeStringLength, szAnsiString, sAnsiStringLength, NULL, NULL);
	}

	bool SetClipboardText(const char * szString, size_t sStringSize)
	{
		// Attempt to open the clipboard
		if(OpenClipboard(NULL))
		{
			// Empty the clipboard
			EmptyClipboard();

			// Allocate the memory globally to store our cut text
			HGLOBAL hMemory = GlobalAlloc(GMEM_DDESHARE, sStringSize);

			// Lock the globally allocated memory then get a pointer to it
			char * szMemory = (char *)GlobalLock(hMemory);

			// Copy the cut text to the globally allocated memory
			strcpy(szMemory, szString);

			// Unlock the globally allocated memory
			GlobalUnlock(hMemory);

			// Set the clipboard data to the allocated memory
			SetClipboardData(CF_TEXT, hMemory);

			// Close the clipboard
			CloseClipboard();
			return true;
		}

		// Failed to open the clipboard
		return false;
	}

	const char * GetClipboardText()
	{
		// Attempt to open the clipboard
		if(OpenClipboard(NULL))
		{
			// Get a pointer to the clipboard text
			char * szClipboardText = (char *)GetClipboardData(CF_TEXT);

			// Return the clipboard text pointer
			return szClipboardText;
		}

		// Failed to open the clipboard
		return NULL;
	}
#endif

	const char * GetTimeAndDateString()
	{
		time_t timeValue;
		time(&timeValue);
		return ctime(&timeValue);
	}

	const char * GetTimeAndDateString2()
	{
		static char szTime[256];
		time_t t = time(NULL);
		const struct tm * tm = localtime(&t);
		strftime(szTime, sizeof(szTime), "%Y-%m-%d %H:%M:%S", tm);
		return szTime;
	}

	const char * GetTimeString()
	{
		static char szTime[256];
		time_t t = time(NULL);
		const struct tm * tm = localtime(&t);
		strftime(szTime, sizeof(szTime), "%H:%M:%S", tm);
		return szTime;
	}

	unsigned long GetTime()
	{
#ifdef _WIN32
		return timeGetTime();
#else
		timeval ts;
		gettimeofday(&ts,0);
		return (DWORD)(ts.tv_sec * 1000 + (ts.tv_usec / 1000));
#endif
	}

	bool Exists(const char * szPath)
	{
		struct stat St;
		return (stat(szPath, &St) == 0);
	}

	bool CopyFile(const char * szSource, const char * szDestination)
	{
		// Open the source file
		FILE * fSource = fopen(szSource, "rb");

		if(!fSource)
			return false;

		// Open the destination file
		FILE * fDestination = fopen(szDestination, "wb");

		if(!fDestination)
		{
			fclose(fSource);
			return false;
		}

		// Copy the source file to the destination file
		char szBuffer[8192];
		size_t sBytesRead = 0;

		while((sBytesRead = fread(szBuffer, 1, sizeof(szBuffer), fSource)) > 0)
		{
			fwrite(szBuffer, 1, sBytesRead, fDestination);
		}

		// Close the destination file
		fclose(fDestination);

		// Close the source file
		fclose(fSource);
		return true;
	}

	int CreateDirectory(const char * szPath)
	{
		// Create the directory
		int 
#ifdef _WIN32
			iReturn = mkdir(szPath);
#else
			iReturn = mkdir(szPath, 0775);
#endif

		// Was the directory created successfully?
		if(!iReturn)
			return 1;

		// Does the directory already exist?
		if(iReturn == EEXIST)
			return 2;

		// Failed to create the directory
		return 0;
	}

	unsigned int IVHash(std::string strString, unsigned int uiInitialHash, bool bEnsureLowercase)
	{
		// Ensure the string is lowercase if needed
		if(bEnsureLowercase)
		{
			for(size_t i = 0; i < strString.size(); i++)
				strString[i] = tolower(strString[i]);
		}

		// Set the initial hash value
		unsigned int uiValue = uiInitialHash;
		unsigned int uiTemp = 0;
		int iCurrent = 0;

		for(size_t sIndex = 0; sIndex < strString.size(); sIndex++)
		{
			iCurrent = strString[sIndex];

			if(iCurrent == '\\')
				iCurrent = '/';

			uiTemp = iCurrent;
			uiTemp = (uiTemp + uiValue);
			uiValue = (uiTemp << 10);
			uiTemp += uiValue;
			uiValue = (uiTemp >> 6);
			uiValue = (uiValue ^ uiTemp);
		}

		uiTemp = (uiValue << 3);
		uiTemp = (uiValue + uiTemp);
		unsigned int uiTemp2 = (uiTemp >> 11);
		uiTemp = (uiTemp2 ^ uiTemp);
		uiTemp2 = (uiTemp << 15);
		uiValue = (uiTemp2 + uiTemp);

		if(uiValue < 2)
			uiValue += 2;

		return uiValue;
	}

	const char * inet_ntop(int af, const void * src, char * dst, int cnt)
	{
		if(af == AF_INET || af == PF_INET)
		{
			sockaddr_in in;
			memset(&in, 0, sizeof(in));
			in.sin_family = af;
			memcpy(&in.sin_addr, src, sizeof(in_addr));
			getnameinfo((sockaddr *)&in, sizeof(sockaddr_in), dst, cnt, NULL, 0, NI_NUMERICHOST);
			return dst;
		}
		else if(af == AF_INET6 || af == PF_INET6)
		{
			struct sockaddr_in6 in;
			memset(&in, 0, sizeof(in));
			in.sin6_family = af;
			memcpy(&in.sin6_addr, src, sizeof(in.sin6_addr));
			getnameinfo((sockaddr *)&in, sizeof(sockaddr_in6), dst, cnt, NULL, 0, NI_NUMERICHOST);
			return dst;
		}

		return NULL;
	}

	int inet_pton(int af, const char * src, void * dst)
	{
		addrinfo hints, *res, *ressave;
		memset(&hints, 0, sizeof(addrinfo));
		hints.ai_family = af;

		if(getaddrinfo(src, NULL, &hints, &res) != 0)
			return -1;

		ressave = res;

		while(res)
		{
			memcpy(dst, res->ai_addr, res->ai_addrlen);
			res = res->ai_next;
		}

		freeaddrinfo(ressave);
		return 0;
	}

	CString RemoveIllegalCharacters(CString& strFileName)
	{
		// Reset the found count
		unsigned int uiFound = 0;

		// Loop until we have no illegal characters left
		do 
		{
			// test/../blah/./ah.txt -> test/blah/./ah.txt
			uiFound = strFileName.Substitute("../", "");

			// test\..\blah\.\ah.txt -> test\blah\.\ah.txt
			uiFound += strFileName.Substitute("..\\", "");

			// test/....//lol.txt    -> test/lol.txt
			uiFound += strFileName.Substitute(":/", "");

			// C:\test\lol.txt       -> Ctest\lol.txt
			uiFound += strFileName.Substitute(":\\", "");
		}
		while (uiFound != 0);

		// Return the file name
		return strFileName;
	}

	CString GetTimePassedFromTime(unsigned long ulTime)
	{
		int iSecondsPassed = ((GetTime() - ulTime) / 1000);
		int iSeconds       = (iSecondsPassed % 60);
		int iMinutesPassed = (iSecondsPassed / 60);
		int iMinutes       = (iMinutesPassed % 60);
		int iHoursPassed   = (iMinutesPassed / 60);
		int iHours         = (iHoursPassed % 60);
		int iDaysPassed    = (iHoursPassed / 24);
		int iDays          = (iDaysPassed % 24);
		return CString("%d day(s), %d hour(s), %d minute(s) and %d second(s)", iDays, iHours, iMinutes, iSeconds);
	}

#ifdef _CLIENT
	DWORD GetSerial()
	{
		// Get the C: serial
		DWORD dwSerial;
		GetVolumeInformation( "C:\\", NULL, 0, &dwSerial, NULL, NULL, NULL, 0 );

		return dwSerial;
	}

	CString GetSerialHash()
	{
		// Get the serial
		DWORD dwSerial = GetSerial( );

		char szSerialMask[] = "0000-0000";
		int i = 8;

		while( dwSerial > 0 && i >= 0 )
		{
			int v = ( dwSerial & 0xF );
			char ch = ( v < 10 ) ? '0' + v : 'A' + ( v + 10 );
			szSerialMask[i--] = ch;

			if( i == 4 )
				i--;

			dwSerial >>= 4;
		}

		return CString( "%s", md5( szSerialMask ).c_str() ).ToUpper();
	}
#endif
#ifdef _WIN32
	void SharedUtility::CheckGameDirectoryExists()
	{

	}

	void SharedUtility::DefineGameRegistryEntires() 
	{

	}

	void SharedUtility::CreateBasicMPDirectories()
	{

		// Check if we have the 'multiplayer' directory, if not: create it.
		char szExecutablePath[MAX_PATH];
		sprintf_s(szExecutablePath,GetAbsolutePath("").Get(),sizeof(MAX_PATH));

		CString strDirectories[] = {"multiplayer", "multiplayer\\common", "multiplayer\\pc", "multiplayer\\pc\\data", "multiplayer\\common\\data", 
				"multiplayer\\common\\data\\effects", "multiplayer\\pc\\textures"};

		for(size_t i = 0; i < ARRAY_LENGTH(strDirectories); i++) {
			CString strMultiplayerPath = szExecutablePath;

			strMultiplayerPath.AppendF(strDirectories[i]);
			CreateDirectoryA(strMultiplayerPath.Get());
		}
	}
#endif
	
	CString DiconnectReasonToString(unsigned uiReason)
	{
		CString strReason("Unknown");

		switch(uiReason)
		{
			case 0:		strReason.Set("Timed Out"); break;
			case 1:		strReason.Set("Quit"); break;
			case 2:		strReason.Set("Kicked"); break;
			case 3:		strReason.Set("Banned"); break;
		}

		return strReason;
	}

	bool GetHTTPData(CString host, CString page, CString &buffer)
	{
		SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		SOCKADDR_IN SockAddr;
		SockAddr.sin_port = htons(80);
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_addr.s_addr = *(DWORD*) gethostbyname(host.Get())->h_addr;

		if(connect(Socket, (SOCKADDR*) &SockAddr, sizeof(SockAddr)) != 0)
			return false;

		CString sendme = CString(
			"GET %s HTTP/1.1\r\n"
			"Host: %s\r\n"
			"Connection: close\r\n"
			"\r\n",
			page.Get(),
			host.Get()
			);

		send(Socket, sendme.Get(), sendme.GetLength(), 0);

		char* _buffer = new char[10000];
		memset(_buffer, 0, 10000);
		recv(Socket, _buffer, 10000, 0);
		buffer = _buffer;
		buffer.Erase(0, buffer.Find("\r\n\r\n") + strlen("\r\n\r\n"));
		delete[] _buffer;

		closesocket(Socket);
		return true;
	}

};