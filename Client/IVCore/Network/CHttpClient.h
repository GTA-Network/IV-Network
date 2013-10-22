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

		virtual bool           IsConnected() { return m_bConnected; }
		virtual bool           IsInvalid() { return (m_status == HTTP_STATUS_INVALID); }
		virtual bool           GettingData() { return (m_status == HTTP_STATUS_GET_DATA); }
		virtual bool           GotData() { return (m_status == HTTP_STATUS_GOT_DATA); }
		virtual bool           IsBusy() { return (m_status == HTTP_STATUS_GET_DATA); }
		virtual unsigned int   GetHeaderCount() { return m_headerMap.size(); }
		virtual CString        GetHeader(CString strName) { return m_headerMap[strName]; }
		virtual CString       * GetData() { return &m_strData; }
		virtual eHttpError     GetLastError() { return m_lastError; }
		virtual void           SetUserAgent(CString strUserAgent) { m_strUserAgent = strUserAgent; }
		virtual CString        GetUserAgent() { return m_strUserAgent; }
		virtual void           SetReferer(CString strReferer) { m_strReferer = strReferer; }
		virtual CString        GetReferer() { return m_strReferer; }
		virtual void           SetRequestTimeout(unsigned int uiRequestTimeout) { m_uiRequestTimeout = uiRequestTimeout; }
		virtual unsigned int   GetRequestTimeout() { return m_uiRequestTimeout; }
		virtual void           SetHost(CString strHost) { m_strHost = strHost; }
		virtual CString        GetHost() { return m_strHost; }
		virtual void           SetPort(unsigned short usPort) { m_usPort = usPort; }
		virtual unsigned short GetPort() { return m_usPort; }
		virtual void           Reset();
		virtual bool           Get(CString strPath);
		virtual void		   SendReport(CString strPath, CString strReport);
		virtual bool           Post(bool bHasResponse, CString strPath, CString strData = "", CString strContentType = DEFAULT_CONTENT_TYPE);
		virtual void           Process();
		virtual CString        GetLastErrorString();
		virtual void           SetReceiveHandle(ReceieveHandler_t pfnRecieveHandler, void * pUserData = NULL);
		virtual void           SetFile(FILE * f = NULL) { m_fFile = f; }
};