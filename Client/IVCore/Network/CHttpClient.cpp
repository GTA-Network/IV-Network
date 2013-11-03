//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CHttpClient.cpp
// Project: Shared
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CHttpClient.h"
#include <SharedUtility.h>

#ifndef _WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#define closesocket close
#include <string.h>
#include <stdio.h>
#else
#include <winsock2.h>
#include <winsock.h>
#endif

#define MAX_BUFFER 8192
#define DEFAULT_PORT 80
#define DEFAULT_USER_AGENT "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:25.0) Gecko/20100101 Firefox/25.0"
#define DEFAULT_REFERER "http://gta-network.net/"

CHttpClient::CHttpClient() :
	m_iSocket(INVALID_SOCKET), m_bConnected(false), m_usPort(DEFAULT_PORT),
	m_status(HTTP_STATUS_NONE), m_lastError(HTTP_ERROR_NONE), m_strUserAgent(DEFAULT_USER_AGENT),
	m_strReferer(DEFAULT_REFERER), m_uiRequestTimeout(30000), m_uiRequestStart(0),
	m_pfnReceiveHandler(NULL), m_pReceiveHandlerUserData(NULL), m_fFile(NULL)
{
	// If windows startup winsock
#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	// Reset the host
	m_strHost.Clear();

	// Reset the headers
	m_headerMap.clear();

	// Reset the data
	m_strData.Clear();
}

CHttpClient::~CHttpClient()
{
	// If we are connected to a host disconnect
	if (m_bConnected)
		Disconnect();

	// If windows cleanup winsock
#ifdef _WIN32
	WSACleanup();
#endif
}

bool CHttpClient::Connect()
{
	// Prepare the socket
	m_iSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_iSocket == INVALID_SOCKET)
	{
		// Failed to prepare the socket, set the last error
		m_lastError = HTTP_ERROR_SOCKET_PREPARE_FAILED;
		return false;
	}

	// Get the host
	hostent * heHost = gethostbyname(m_strHost.Get());

	if (heHost == NULL)
	{
		// Failed to get the host, set the last error
		m_lastError = HTTP_ERROR_INVALID_HOST;
		return false;
	}

	// Prepare a socket address
	sockaddr_in sinAddress;
	sinAddress.sin_family = AF_INET;
	sinAddress.sin_port = htons(m_usPort);
	sinAddress.sin_addr = *((in_addr *) heHost->h_addr);
	memset(&sinAddress.sin_zero, 0, (sizeof(char) * 8));

	// Try to connect
	if (connect(m_iSocket, (sockaddr *) &sinAddress, sizeof(sockaddr)) < 0)
	{
		// Disconnect
		Disconnect();

		// Connection failed, set the last error
		m_lastError = HTTP_ERROR_CONNECTION_FAILED;
		return false;
	}

	// Set the connected flag to true
	m_bConnected = true;
	return true;
}

void CHttpClient::Disconnect()
{
	// Is the socket valid?
	if (m_iSocket != INVALID_SOCKET)
	{
		// Close the socket
		closesocket(m_iSocket);

		// Invalidate the socket
		m_iSocket = INVALID_SOCKET;
	}

	// Set the connected flag to false
	m_bConnected = false;
}

bool CHttpClient::Write(const char * szData, int iLen)
{
	// Try to send
	if (send(m_iSocket, szData, iLen, 0) < 0)
	{
		// Send failed
		m_lastError = HTTP_ERROR_SEND_FAILED;
		return false;
	}

	// Send success
	return true;
}

int CHttpClient::Read(char * szBuffer, int iLen)
{
	// Set the socket to non blocking
#ifdef _WIN32
	u_long sockopt = 1;
	ioctlsocket(m_iSocket, FIONBIO, &sockopt);
#else
	int flags = fcntl(m_iSocket, F_GETFL, 0);
	UNSET_BIT(flags, O_NONBLOCK);
	fcntl(m_iSocket, F_SETFL, flags);
#endif

	// Try to receive
	int iBytesRead = recv(m_iSocket, szBuffer, iLen, 0);

	// Set the socket to blocking
#ifdef _WIN32
	sockopt = 0;
	ioctlsocket(m_iSocket, FIONBIO, &sockopt);
#else
	SET_BIT(flags, O_NONBLOCK);
	fcntl(m_iSocket, F_SETFL, flags);
#endif
	return iBytesRead;
}

void CHttpClient::Reset()
{
	// Are we connected?
	if (IsConnected())
	{
		// Disconnect
		Disconnect();
	}

	// Set the status to none
	m_status = HTTP_STATUS_NONE;
	SetFile();
}

bool CHttpClient::Get(CString strPath)
{
	// Connect to the host
	if (!Connect())
	{
		// Connect failed
		return false;
	}

	// Reset the header and data
	m_headerMap.clear();
	m_strData.Clear();

	// Prepare the GET command
	CString strGet("GET %s HTTP/1.0\r\n" \
		"Host: %s\r\n" \
		"User-Agent: %s\r\n" \
		"Referer: %s\r\n" \
		"Connection: close\r\n" \
		"\r\n",
		strPath.Get(), m_strHost.Get(),
		m_strUserAgent.Get(), m_strReferer.Get());

	// Send the GET command
	if (!Write(strGet.C_String(), strGet.GetLength()))
	{
		//CLogFile::Printf("HTTP REQUEST FAILED!");
		// Send failed
		return false;
	}

	// Set the status to get data
	m_status = HTTP_STATUS_GET_DATA;

	// Set the request start
	m_uiRequestStart = SharedUtility::GetTime();
	return true;
}

// Send Report writes data into the header(can be readout with php://input http://php.net/manual/en/function.http-get-request-body.php
void CHttpClient::SendReport(CString strPath, CString strReport)
{
	// Connect to the host
	if (!Connect())
	{
		// Connect failed
		return;
	}

	// Reset the header and data
	m_headerMap.clear();
	m_strData.Clear();

	// Prepare the GET command
	CString strGet("GET %s HTTP/1.0\r\n" \
		"Host: %s\r\n" \
		"User-Agent: %s\r\n" \
		"Referer: %s\r\n" \
		"Connection: close\r\n" \
		"\n%s" \
		"\r\n",
		strPath.Get(), m_strHost.Get(),
		m_strUserAgent.Get(), m_strReferer.Get(), strReport.Get());

	// Send the GET command
	if (!Write(strGet.C_String(), strGet.GetLength()))
	{
		// Send failed
		return;
	}

	// Set the status to get data
	m_status = HTTP_STATUS_GET_DATA;

	// Set the request start
	m_uiRequestStart = SharedUtility::GetTime();
	return;
}

bool CHttpClient::Post(bool bHasResponse, CString strPath, CString strData, CString strContentType)
{
	// Connect to the host
	if (!Connect())
	{
		// Connect failed
		return false;
	}

	// Reset the header and data
	m_headerMap.clear();
	m_strData.Clear();

	// Prepare the POST command
	CString strGet("POST %s HTTP/1.0\r\n" \
		"Host: %s\r\n" \
		"User-Agent: %s\r\n\r\n" \
		"Referer: %s\r\n" \
		"Content-Type: %s\r\n" \
		"Content-Length: %d\r\n" \
		"Connection: close\r\n" \
		"\r\n" \
		"%s",
		strPath.Get(), m_strHost.Get(), m_strUserAgent.Get(),
		m_strReferer.Get(), strContentType.Get(), strData.GetLength(),
		strData.Get());

	// Send the POST command
	if (!Write(strGet.C_String(), strGet.GetLength()))
	{
		// Send failed
		return false;
	}

	// Do we have a response
	if (bHasResponse)
	{
		// Set the status to get data
		m_status = HTTP_STATUS_GET_DATA;

		// Set the request start
		m_uiRequestStart = SharedUtility::GetTime();
	}
	else
	{
		// Disconnect from the host
		Disconnect();
	}

	return true;
}

// find s2 in s1 (with size s1_s) starting from index sp and ending at s1_s or first instance of ts
int strfind(const char * s1, int s1_s, const char * s2, int sp = 0, char * ts = NULL)
{
	for (int i = sp; i < s1_s; i++)
	{
		if (ts)
		{
			if (s1[i] == ts[0])
			{
				for (int j = 0; j < (int) strlen(ts); j++)
				{
					if (s1[i + j] != ts[j])
						break;

					return -1;
				}
			}
		}

		if (s1[i] == s2[0])
		{
			for (int j = 0; j < (int) strlen(s2); j++)
			{
				if (s1[i + j] != s2[j])
					break;

				return i;
			}
		}
	}

	return -1;
}

bool CHttpClient::ParseHeaders(const char * szBuffer, int& iBufferSize, int& iHeaderSize)
{
	// Find amount of whitespace
	int iWhiteSpace = 0;

	for (int i = 0; i < iBufferSize; i++)
	{
		if (szBuffer[i] != ' ')
			break;

		// Increment the whitespace amount
		iWhiteSpace++;
	}

	// Increment the header size
	iHeaderSize += iWhiteSpace;

	// Ignore the version, status code and status message
	// Will be in format 'HTTP/1.0 200 OK\r\n'
	int iIgnore = strfind(szBuffer, iBufferSize, "\r\n", iHeaderSize);

	if (iIgnore == -1)
		return false;

	int iIgnoreSize = (iIgnore - iHeaderSize);

	// Increment the header size
	iHeaderSize += (iIgnoreSize + 2); // + 2 for '\r\n'

	// Find all headers
	int iNameSplit;
	int iValueSplit;

	while ((iNameSplit = strfind(szBuffer, iBufferSize, ": ", iHeaderSize, "\r\n")) != -1)
	{
		// Get the header name
		int iNameSize = (iNameSplit - iHeaderSize);
		CString strName;
		strName.Set((szBuffer + iHeaderSize), iNameSize);

		// Increment the header size
		iHeaderSize += (iNameSize + 2); // + 2 for '\r\n'

		// Find the value end
		iValueSplit = strfind(szBuffer, iBufferSize, "\r\n", iHeaderSize);

		// Did we not find a value end?
		if (iValueSplit == -1)
			return false;

		// Get the header value
		int iValueSize = (iValueSplit - iHeaderSize);
		CString strValue;
		strValue.Set((szBuffer + iHeaderSize), iValueSize);

		// Increment the header size
		iHeaderSize += (iValueSize + 2); // + 2 for '\r\n'

		// Add the header to the header map
		m_headerMap[strName] = strValue;
	}

	// Did we not get any headers?
	if (m_headerMap.empty())
		return false;

	// Ignore the '\r\n' after the headers
	iHeaderSize += 2;

	// Decrement the buffer size by the header size
	iBufferSize -= iHeaderSize;

	// Success
	return true;
}

void CHttpClient::Process()
{
	// Do we have a request start and has the request timed out?
	if (m_uiRequestStart > 0 && (SharedUtility::GetTime() - m_uiRequestStart) >= m_uiRequestTimeout)
	{
		// Set the status to none
		m_status = HTTP_STATUS_NONE;

		// Request timed out, set the last error
		m_lastError = HTTP_ERROR_REQUEST_TIMEOUT;

		// Reset the request start
		m_uiRequestStart = 0;

		// Disconnect from the host
		Disconnect();
		return;
	}

	// Are we not in idle status?
	if (m_status != HTTP_STATUS_NONE)
	{
		switch (m_status)
		{
		case HTTP_STATUS_GET_DATA:
			{
				// Prepare a buffer
				char szBuffer[MAX_BUFFER];
				memset(szBuffer, 0, sizeof(szBuffer));

				// Try to read from the socket
				int iBytesRecieved = Read(szBuffer, sizeof(szBuffer));
				int iHeaderSize = 0;

				// Did we get anything?
				if (iBytesRecieved > 0)
				{
					// Are the headers empty?
					if (m_headerMap.empty())
					{
						// Parse the headers
						if (!ParseHeaders(szBuffer, iBytesRecieved, iHeaderSize))
						{
							// We don't have a header, set the status
							m_status = HTTP_STATUS_INVALID;

							// Set the last error
							m_lastError = HTTP_ERROR_NO_HEADER;

							// Reset the request start
							m_uiRequestStart = 0;

							// Disconnect from the host
							Disconnect();
							return;
						}

						// Do we not have any data?
						if (iBytesRecieved == 0)
							return;
					}

					// Skip the header data if we have any
					char * szData = (iBytesRecieved ? (szBuffer + iHeaderSize) : NULL);

					// Call the receive handler if we have one
					if (m_pfnReceiveHandler)
					{
						if (m_pfnReceiveHandler(szData, iBytesRecieved, m_pReceiveHandlerUserData))
							m_strData.Append(szData, iBytesRecieved);
					}
					// Write response data to file if we have one set
					else if (m_fFile != NULL)
						fwrite(szData, 1, iBytesRecieved, m_fFile);
				}
				else if (iBytesRecieved == 0)
				{
					// We got data, set the status
					m_status = HTTP_STATUS_GOT_DATA;

					// Reset the request start
					m_uiRequestStart = 0;

					// Disconnect from the host
					Disconnect();
				}
								 }

			break;
		}
	}
}

CString CHttpClient::GetLastErrorString()
{
	CString strError("Unknown");

	switch (GetLastError())
	{
	case HTTP_ERROR_SOCKET_PREPARE_FAILED:
		strError.Set("Failed to prepare socket");
		break;
	case HTTP_ERROR_INVALID_HOST:
		strError.Set("Invalid host");
		break;
	case HTTP_ERROR_IOCTL_FAILED:
		strError.Set("IoCtl failed");
		break;
	case HTTP_ERROR_CONNECTION_FAILED:
		strError.Set("Connection failed");
		break;
	case HTTP_ERROR_SEND_FAILED:
		strError.Set("Send failed");
		break;
	case HTTP_ERROR_REQUEST_TIMEOUT:
		strError.Set("Request timed out");
		break;
	case HTTP_ERROR_NO_HEADER:
		strError.Set("No header");
		break;
	case HTTP_ERROR_NONE:
		strError.Set("No error");
		break;
	}

	return strError;
}

void CHttpClient::SetReceiveHandle(ReceieveHandler_t pfnRecieveHandler, void * pUserData)
{
	m_pfnReceiveHandler = pfnRecieveHandler;
	m_pReceiveHandlerUserData = pUserData;
}

