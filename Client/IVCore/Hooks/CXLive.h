//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CXLive.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CXLive_h
#define CXLive_h

#include <Common.h>
#include <malloc.h>

// XLive Structure Replacements
struct FakeProtectedBuffer 
{
	DWORD	dwMagic;
	int		iSize;
	BYTE	byteData[4];
};

struct XUSER_READ_PROFILE_SETTINGS 
{
	DWORD	dwLength;
	BYTE *	pSettings;
};

// XLive Functions
int WINAPI XWSAStartup(WORD wVersionRequested, LPWSADATA lpWsaData);
void WINAPI XWSACleanup();
SOCKET WINAPI XSocketCreate(int af, int type, int protocol);
int WINAPI XSocketClose(SOCKET s);
int WINAPI XSocketShutdown(SOCKET s, int how);
int WINAPI XSocketIOCTLSocket(SOCKET s, long cmd, long * argp);
int WINAPI XSocketSetSockOpt(SOCKET s, int level, int optname, const char * optval, int optlen);
int WINAPI XSocketGetSockName(SOCKET s, sockaddr_in * name, int * namelen);
SOCKET WINAPI XSocketBind(SOCKET s, sockaddr_in * addr, int * addrlen);
int WINAPI XSocketConnect(SOCKET s, sockaddr_in * addr, int * addrlen);
int WINAPI XSocketListen(SOCKET s, int backlog);
SOCKET WINAPI XSocketAccept(SOCKET s, sockaddr_in * addr, int * addrlen);
int WINAPI XSocketSelect(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, const struct timeval * timeout);
int WINAPI XSocketRecv(SOCKET s, char * buf, int len, int flags);
int WINAPI XSocketRecvFrom(SOCKET s, char * buf, int len, int flags, sockaddr_in * from, int fromlen);
int WINAPI XSocketSend(SOCKET s, char * buf, int len, int flags);
int WINAPI XSocketSendTo(SOCKET s, char * buf, int len, int flags, sockaddr_in * to, int tolen);
int WINAPI XSocketInet_Addr(const char * cp);
int WINAPI XWSAGetLastError();
WORD WINAPI XSocketNTOHS(u_short netshort);
DWORD WINAPI XSocketNTOHL(u_long netlong);
int WINAPI XNetStartup(void *);
int WINAPI XNetCleanup();
int WINAPI XNetXnAddrToInAddr(DWORD, DWORD, DWORD * p);
DWORD WINAPI XNetServerToInAddr(DWORD, DWORD, DWORD);
int WINAPI XNetUnregisterInAddr(DWORD);
int WINAPI XNetGetConnectStatus(DWORD);
DWORD WINAPI XNetQosListen(DWORD, DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XNetQosLookup(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XNetQosRelease(DWORD);
DWORD WINAPI XNetGetTitleXnAddr(DWORD * pAddr);
DWORD WINAPI XNetGetEthernetLinkStatus();
DWORD WINAPI XNetSetSystemLinkPort(DWORD);
int WINAPI XNotifyGetNext(DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XNotifyPositionUI(DWORD dwPosition);
DWORD WINAPI XGetOverlappedExtendedError(void *);
DWORD WINAPI XGetOverlappedResult(void *, DWORD * pResult, DWORD);
int WINAPI XLiveInitialize(DWORD);
int WINAPI XLiveInput(DWORD * p);
int WINAPI XLiveRender();
int WINAPI XLiveUninitialize();
int WINAPI XLiveOnCreateDevice(DWORD, DWORD);
int WINAPI XLiveOnResetDevice(DWORD);
int WINAPI XHVCreateEngine(DWORD, DWORD, DWORD);
DWORD WINAPI XLivePBufferAllocate(int size, FakeProtectedBuffer ** pBuffer);
DWORD WINAPI XLivePBufferFree(FakeProtectedBuffer * pBuffer);
DWORD WINAPI XLivePBufferGetByte(FakeProtectedBuffer * pBuffer, int offset, BYTE * value);
DWORD WINAPI XLivePBufferSetByte(FakeProtectedBuffer * pBuffer, int offset, BYTE value);
DWORD WINAPI XLivePBufferGetDWORD(FakeProtectedBuffer * pBuffer, DWORD dwOffset, DWORD * pdwValue);
DWORD WINAPI XLivePBufferSetDWORD(FakeProtectedBuffer * pBuffer, DWORD dwOffset, DWORD dwValue);
int WINAPI XLiveGetUpdateInformation(DWORD);
int WINAPI XLiveUpdateSystem(DWORD);
int WINAPI XLivePreTranslateMessage(DWORD);
DWORD WINAPI XLiveProtectData(BYTE * pInBuffer, DWORD dwInDataSize, BYTE * pOutBuffer, DWORD * pDataSize, HANDLE h);
DWORD WINAPI XLiveUnprotectData(BYTE * pInBuffer, DWORD dwInDataSize, BYTE * pOutBuffer, DWORD * pDataSize, HANDLE h);
DWORD WINAPI XLiveCreateProtectedDataContext(DWORD * dwType, HANDLE * pHandle);
DWORD WINAPI XLiveQueryProtectedDataInformation(HANDLE h, DWORD * p);
DWORD WINAPI XLiveCloseProtectedDataContext(HANDLE h);
int WINAPI XShowPlayerReviewUI(DWORD, DWORD, DWORD);
int WINAPI XShowGuideUI(DWORD);
int WINAPI XCloseHandle(DWORD);
int WINAPI XShowGamerCardUI(DWORD, DWORD, DWORD);
int WINAPI XCancelOverlapped(DWORD);
int WINAPI XEnumerate(HANDLE hEnum, void * pvBuffer, DWORD cbBuffer, DWORD *, void * pOverlapped);
int WINAPI XShowSigninUI(DWORD, DWORD);
int WINAPI XUserGetXUID(DWORD, DWORD * pXuid);
int WINAPI XUserGetSigninState(DWORD);
int WINAPI XUserGetName(DWORD dwUserId, char * pBuffer, DWORD dwBufLen);
int WINAPI XUserAreUsersFriends(DWORD, DWORD, DWORD, DWORD, DWORD);
int WINAPI XUserCheckPrivilege(DWORD user, DWORD priv, PBOOL b);
int WINAPI XUserGetSigninInfo(DWORD dwUser, DWORD type, DWORD * pInfo);
HANDLE WINAPI XNotifyCreateListener(DWORD l, DWORD h);
int WINAPI XUserSetProperty(DWORD, DWORD, DWORD, DWORD);
int WINAPI XUserSetContext(DWORD, DWORD, DWORD);
DWORD WINAPI XUserWriteAchievements(DWORD, DWORD, DWORD);
DWORD WINAPI XUserCreateAchievementEnumerator(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, PHANDLE phEnum);
DWORD WINAPI XUserReadStats(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD * pcbResults, DWORD * pResults, void *);
DWORD WINAPI XUserCreateStatsEnumeratorByRank(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, PHANDLE phEnum);
DWORD WINAPI XUserCreateStatsEnumeratorByXuid(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, PHANDLE phEnum);
int WINAPI XUserSetContextEx(DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XLivePBufferGetByteArray(FakeProtectedBuffer * pBuffer, int offset, BYTE * destination, int size);
DWORD WINAPI XLivePBufferSetByteArray(FakeProtectedBuffer * pBuffer, int offset, BYTE * source, int size);
int WINAPI XLiveInitializeEx(void *, int);
DWORD WINAPI XSessionCreate(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XStringVerify(DWORD, DWORD, DWORD, DWORD, DWORD, WORD * pResult, DWORD);
DWORD WINAPI XStorageUploadFromMemory(DWORD, DWORD, DWORD, DWORD, DWORD);
int WINAPI XOnlineStartup();
int WINAPI XOnlineCleanup();
DWORD WINAPI XFriendsCreateEnumerator(DWORD, DWORD, DWORD, DWORD, DWORD);
int WINAPI XUserMuteListQuery(DWORD, DWORD, DWORD, DWORD);
int WINAPI XInviteGetAcceptedInfo(DWORD, DWORD);
int WINAPI XInviteSend(DWORD, DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XSessionWriteStats(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
int WINAPI XSessionStart(DWORD, DWORD, DWORD);
DWORD WINAPI XSessionSearchEx(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XSessionModify(DWORD, DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XSessionMigrateHost(DWORD, DWORD, DWORD, DWORD);
int WINAPI XOnlineGetNatType();
DWORD WINAPI XSessionLeaveLocal(DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XSessionJoinRemote(DWORD, DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XSessionJoinLocal(DWORD, DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XSessionGetDetails(DWORD, DWORD, DWORD, DWORD);
int WINAPI XSessionFlushStats(DWORD, DWORD);
DWORD WINAPI XSessionDelete(DWORD, DWORD);
DWORD WINAPI XUserReadProfileSettings(DWORD dwTitleId, DWORD dwUserIndex, DWORD dwNumSettingIds, DWORD * pdwSettingIds, DWORD * pcbResults, XUSER_READ_PROFILE_SETTINGS * pResults, DWORD pOverlapped);
int WINAPI XSessionEnd(DWORD, DWORD);
DWORD WINAPI XSessionArbitrationRegister(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD) ;
DWORD WINAPI XTitleServerCreateEnumerator(DWORD, DWORD, DWORD, PHANDLE phEnum) ;
DWORD WINAPI XSessionLeaveRemote(DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XUserWriteProfileSettings(DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XStorageBuildServerPath(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
DWORD WINAPI XStorageDownloadToMemory(DWORD dwUserIndex, DWORD, DWORD, DWORD, DWORD, DWORD, void *);
DWORD WINAPI XLiveProtectedVerifyFile(HANDLE hContentAccess, VOID * pvReserved, PCWSTR pszFilePath);
DWORD WINAPI XLiveContentCreateAccessHandle(DWORD dwTitleId, void * pContentInfo, DWORD dwLicenseInfoVersion, void * xebBuffer, DWORD dwOffset, HANDLE * phAccess, void * pOverlapped);
DWORD WINAPI XLiveContentUninstall(void * pContentInfo, void * pxuidFor, void * pInstallCallbackParams);
DWORD WINAPI XLiveContentGetPath(DWORD dwUserIndex, void * pContentInfo, wchar_t * pszPath, DWORD * pcchPath);
DWORD WINAPI XLiveContentCreateEnumerator(DWORD, void *, DWORD *pchBuffer, HANDLE * phContent);
DWORD WINAPI XLiveContentRetrieveOffersByDate(DWORD dwUserIndex, DWORD dwOffserInfoVersion, SYSTEMTIME * pstStartDate, void * pOffserInfoArray, DWORD * pcOfferInfo, void * pOverlapped);
DWORD WINAPI XShowMarketplaceUI(DWORD dwUserIndex, DWORD dwEntryPoint, ULONGLONG dwOfferId, DWORD dwContentCategories);
DWORD WINAPI xlive_5367(HANDLE, DWORD, DWORD, BYTE *, DWORD);
DWORD WINAPI xlive_5372(HANDLE, DWORD, DWORD, DWORD, BYTE *, HANDLE);

// Hook Class
class CXLiveHook {
public:
	static void Install();
};


#endif // CXLive_h