//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CHttpClient.h
// Project: Shared
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include <CString.h>
#include <map>

#define DEFAULT_CONTENT_TYPE "text/plain"

typedef bool(*ReceieveHandler_t)(const char * szData, unsigned int uiDataSize, void * pUserData);

enum eHttpStatus
{
	HTTP_STATUS_NONE,
	HTTP_STATUS_INVALID,
	HTTP_STATUS_GET_DATA,
	HTTP_STATUS_GOT_DATA
};

enum eHttpError
{
	HTTP_ERROR_NONE,
	HTTP_ERROR_SOCKET_PREPARE_FAILED,
	HTTP_ERROR_INVALID_HOST,
	HTTP_ERROR_IOCTL_FAILED,
	HTTP_ERROR_CONNECTION_FAILED,
	HTTP_ERROR_SEND_FAILED,
	HTTP_ERROR_REQUEST_TIMEOUT,
	HTTP_ERROR_NO_HEADER
};

class CHttpClient
{
	private:
			int                      m_iSocket;
			bool                     m_bConnected;
			CString                   m_strHost;
			unsigned short           m_usPort;
			eHttpStatus              m_status;
			std::map<CString, CString> m_headerMap;
			CString                   m_strData;
			eHttpError               m_lastError;
			CString                   m_strUserAgent;
			CString                   m_strReferer;
			unsigned int             m_uiRequestTimeout;
			unsigned int             m_uiRequestStart;
			ReceieveHandler_t        m_pfnReceiveHandler;
			void                   * m_pReceiveHandlerUserData;
			FILE                   * m_fFile;

			bool                   Connect();
			void                   Disconnect();
			bool                   Write(const char * szData, int iLen);
			int                    Read(char * szBuffer, int iLen);
			bool                   ParseHeaders(const char * szBuffer, int& iBufferSize, int& iHeaderSize);

	public:
		CHttpClient();
		~CHttpClient();

		bool           IsConnected() { return m_bConnected; }
		bool           IsInvalid() { return (m_status == HTTP_STATUS_INVALID); }
		bool           GettingData() { return (m_status == HTTP_STATUS_GET_DATA); }
		bool           GotData() { return (m_status == HTTP_STATUS_GOT_DATA); }
		bool           IsBusy() { return (m_status == HTTP_STATUS_GET_DATA); }
		unsigned int   GetHeaderCount() { return m_headerMap.size(); }
		CString        GetHeader(CString strName) { return m_headerMap[strName]; }
		CString		   GetData() { return m_strData; }
		eHttpError     GetLastError() { return m_lastError; }
		void           SetUserAgent(CString strUserAgent) { m_strUserAgent = strUserAgent; }
		CString        GetUserAgent() { return m_strUserAgent; }
		void           SetReferer(CString strReferer) { m_strReferer = strReferer; }
		CString        GetReferer() { return m_strReferer; }
		void           SetRequestTimeout(unsigned int uiRequestTimeout) { m_uiRequestTimeout = uiRequestTimeout; }
		unsigned int   GetRequestTimeout() { return m_uiRequestTimeout; }
		void           SetHost(CString strHost) { m_strHost = strHost; }
		CString        GetHost() { return m_strHost; }
		void           SetPort(unsigned short usPort) { m_usPort = usPort; }
		unsigned short GetPort() { return m_usPort; }
		void           Reset();
		bool           Get(CString strPath);
		void		   SendReport(CString strPath, CString strReport);
		bool           Post(bool bHasResponse, CString strPath, CString strData = "", CString strContentType = DEFAULT_CONTENT_TYPE);
		void           Process();
		CString        GetLastErrorString();
		void           SetReceiveHandle(ReceieveHandler_t pfnRecieveHandler, void * pUserData = NULL);
		void           SetFile(FILE * f = NULL) { m_fFile = f; }
};