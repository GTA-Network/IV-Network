//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CXLive.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CXLive.h"
#include <Patcher/CPatcher.h>

// XLive Functions
int WINAPI XWSAStartup(WORD wVersionRequested, LPWSADATA lpWsaData)
{
	lpWsaData->wVersion = 2;
	return 0;
}

void WINAPI XWSACleanup()
{
	return;
}

SOCKET WINAPI XSocketCreate(int af, int type, int protocol)
{
	return INVALID_SOCKET;
}

int WINAPI XSocketClose(SOCKET s)
{
	return 0;
}

int WINAPI XSocketShutdown(SOCKET s, int how)
{
	return 0;
}

int WINAPI XSocketIOCTLSocket(SOCKET s, long cmd, long * argp)
{
	return 0;
}

int WINAPI XSocketSetSockOpt(SOCKET s, int level, int optname, const char * optval, int optlen)
{
	return 0;
}

int WINAPI XSocketGetSockName(SOCKET s, sockaddr_in * name, int * namelen)
{
	if(namelen && name && *namelen == sizeof(sockaddr_in)) 
		memset(name, 0, sizeof(sockaddr_in));

	return 0;
}

SOCKET WINAPI XSocketBind(SOCKET s, sockaddr_in * addr, int * addrlen)
{
	return INVALID_SOCKET;
}

int WINAPI XSocketConnect(SOCKET s, sockaddr_in * addr, int * addrlen)
{
	return 0;
}

int WINAPI XSocketListen(SOCKET s, int backlog)
{
	return 0;
}

SOCKET WINAPI XSocketAccept(SOCKET s, sockaddr_in * addr, int * addrlen)
{
	return INVALID_SOCKET;
}

int WINAPI XSocketSelect(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, const struct timeval * timeout)
{
	return 0;
}

int WINAPI XSocketRecv(SOCKET s, char * buf, int len, int flags)
{
	return 0;
}

int WINAPI XSocketRecvFrom(SOCKET s, char * buf, int len, int flags, sockaddr_in * from, int fromlen)
{
	return 0;
}

int WINAPI XSocketSend(SOCKET s, char * buf, int len, int flags)
{
	return 0;
}

int WINAPI XSocketSendTo(SOCKET s, char * buf, int len, int flags, sockaddr_in * to, int tolen)
{
	return 0;
}

int WINAPI XSocketInet_Addr(const char * cp)
{
	return 0;
}

int WINAPI XWSAGetLastError()
{
	return WSAENETDOWN; // 0 ?
}

WORD WINAPI XSocketNTOHS(u_short netshort)
{
	return((netshort & 0xFF00) >> 8) | ((netshort & 0xFF) << 8);
}

DWORD WINAPI XSocketNTOHL(u_long netlong)
{
	return((netlong & 0xFF000000) >> 24) | ((netlong & 0x00FF0000) >> 8) | ((netlong & 0x0000FF00) << 8) | ((netlong & 0x000000FF) << 24);
}

int WINAPI XNetStartup(void *)
{
	return 0;
}

int WINAPI XNetCleanup()
{
	return 0;
}

int WINAPI XNetXnAddrToInAddr(DWORD, DWORD, DWORD * p)
{
	*p = 0;
	return 0;
}

DWORD WINAPI XNetServerToInAddr(DWORD, DWORD, DWORD)
{
	return 0;
}

int WINAPI XNetUnregisterInAddr(DWORD)
{
	return 0;
}

int WINAPI XNetGetConnectStatus(DWORD)
{
	return 0;	
}

DWORD WINAPI XNetQosListen(DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

DWORD WINAPI XNetQosLookup(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

DWORD WINAPI XNetQosRelease(DWORD)
{
	return 0; 
}

DWORD WINAPI XNetGetTitleXnAddr(DWORD * pAddr)
{
	*pAddr = 0x0100007F; // 127.0.0.1
	return 4; 
}

DWORD WINAPI XNetGetEthernetLinkStatus()
{
	return 1; 
}

DWORD WINAPI XNetSetSystemLinkPort(DWORD)
{
	return 0; 
}

int WINAPI XNotifyGetNext(DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

DWORD WINAPI XNotifyPositionUI(DWORD dwPosition)
{
	return 0;
}

DWORD WINAPI XGetOverlappedExtendedError(void *)
{
	return 0;
}

DWORD WINAPI XGetOverlappedResult(void *, DWORD * pResult, DWORD)
{
	if(pResult)
		*pResult = 0;	// 0 elements enumerated

	return 0;
}

int WINAPI XLiveInitialize(DWORD)
{
	return 0;
}

int WINAPI XLiveInput(DWORD * p)
{
	p[5] = 0;
	return 1;	// -1 ?
}

int WINAPI XLiveRender()
{
	return 0;
}

int WINAPI XLiveUninitialize()
{
	return 0;
}

int WINAPI XLiveOnCreateDevice(DWORD, DWORD)
{
	return 0;
}

int WINAPI XLiveOnResetDevice(DWORD)
{
	return 0;
}

int WINAPI XHVCreateEngine(DWORD, DWORD, DWORD)
{
	// Disable live voice
	return -1;
}

DWORD WINAPI XLivePBufferAllocate(int size, FakeProtectedBuffer ** pBuffer)
{
	*pBuffer = (FakeProtectedBuffer *)malloc(size + 16);

	if(!*pBuffer) 
		return E_OUTOFMEMORY;

	// Some arbitrary number
	(*pBuffer)->dwMagic = FAKE_MAGIC;
	(*pBuffer)->iSize = size;
	return 0;
}

DWORD WINAPI XLivePBufferFree(FakeProtectedBuffer * pBuffer)
{
	if(pBuffer && pBuffer->dwMagic == FAKE_MAGIC)
		free(pBuffer);

	return 0;
}

DWORD WINAPI XLivePBufferGetByte(FakeProtectedBuffer * pBuffer, int offset, BYTE * value)
{
	if(!pBuffer || pBuffer->dwMagic != FAKE_MAGIC || !value || offset < 0 || offset > pBuffer->iSize)
		return 0;

	*value = pBuffer->byteData[offset];
	return 0;
}

DWORD WINAPI XLivePBufferSetByte(FakeProtectedBuffer * pBuffer, int offset, BYTE value)
{
	if(!pBuffer || pBuffer->dwMagic != FAKE_MAGIC || offset < 0 || offset > pBuffer->iSize)
		return 0;

	pBuffer->byteData[offset] = value;
	return 0;
}

DWORD WINAPI XLivePBufferGetDWORD(FakeProtectedBuffer * pBuffer, DWORD dwOffset, DWORD * pdwValue)
{
	if(!pBuffer || pBuffer->dwMagic != FAKE_MAGIC || dwOffset < 0 || dwOffset > (DWORD)(pBuffer->iSize - 4) || !pdwValue)
		return 0;

	*pdwValue = *(DWORD *)(pBuffer->byteData + dwOffset);
	return 0;
}

DWORD WINAPI XLivePBufferSetDWORD(FakeProtectedBuffer * pBuffer, DWORD dwOffset, DWORD dwValue)
{
	if(!pBuffer || pBuffer->dwMagic != FAKE_MAGIC || dwOffset < 0 || dwOffset > (DWORD)(pBuffer->iSize - 4))
		return 0;

	*(DWORD *)(pBuffer->byteData + dwOffset) = dwValue;
	return 0;
}

int WINAPI XLiveGetUpdateInformation(DWORD)
{
	// No update
	return -1;
}

int WINAPI XLiveUpdateSystem(DWORD)
{
	// No update
	return -1;
}

int WINAPI XLivePreTranslateMessage(DWORD)
{
	return 0;
}

DWORD WINAPI XLiveProtectData(BYTE * pInBuffer, DWORD dwInDataSize, BYTE * pOutBuffer, DWORD * pDataSize, HANDLE h)
{
	*pDataSize = dwInDataSize;

	if(*pDataSize >= dwInDataSize && pOutBuffer)
		memcpy(pOutBuffer, pInBuffer, dwInDataSize);

	return 0;
}

DWORD WINAPI XLiveUnprotectData(BYTE * pInBuffer, DWORD dwInDataSize, BYTE * pOutBuffer, DWORD * pDataSize, HANDLE h)
{
	*pDataSize = dwInDataSize;

	if(*pDataSize >= dwInDataSize && pOutBuffer)
		memcpy(pOutBuffer, pInBuffer, dwInDataSize);

	return 0;
}

DWORD WINAPI XLiveCreateProtectedDataContext(DWORD * dwType, HANDLE * pHandle)
{
	if(pHandle)
		*pHandle =(HANDLE)1;

	return 0;
}

DWORD WINAPI XLiveQueryProtectedDataInformation(HANDLE h, DWORD * p)
{
	return 0;
}

DWORD WINAPI XLiveCloseProtectedDataContext(HANDLE h)
{
	return 0;
}

int WINAPI XShowPlayerReviewUI(DWORD, DWORD, DWORD)
{
	return 0;
}

int WINAPI XShowGuideUI(DWORD)
{
	return 1;
}

int WINAPI XCloseHandle(DWORD)
{
	return 0;
}

int WINAPI XShowGamerCardUI(DWORD, DWORD, DWORD)
{
	return 0;
}

int WINAPI XCancelOverlapped(DWORD)
{
	return 0;
}

int WINAPI XEnumerate(HANDLE hEnum, void * pvBuffer, DWORD cbBuffer, DWORD *, void * pOverlapped)
{
	// Some error?
	return 0;
}

int WINAPI XShowSigninUI(DWORD, DWORD)
{
	return 0;
}

int WINAPI XUserGetXUID(DWORD, DWORD * pXuid)
{
	pXuid[0] = pXuid[1] = 0x10001000; 

	// ???
	return 0;
}

int WINAPI XUserGetSigninState(DWORD)
{
	// eXUserSigninState_SignedInLocally
	return 1;
}

int WINAPI XUserGetName(DWORD dwUserId, char * pBuffer, DWORD dwBufLen)
{
	if(dwBufLen < 6)
		return 1;

	strcpy(pBuffer, "IV:N");
	return 0;
}

int WINAPI XUserAreUsersFriends(DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

int WINAPI XUserCheckPrivilege(DWORD user, DWORD priv, PBOOL b)
{
	*b = false;
	return 0;
}

int WINAPI XUserGetSigninInfo(DWORD dwUser, DWORD type, DWORD * pInfo)
{
	// Some arbitrary id for offline user, INVALID_XUID for online user
	pInfo[0] = pInfo[1] = (type == 2) ? ((dwUser + 1) * 0x10001000) : 0;
	return 0;
}

HANDLE WINAPI XNotifyCreateListener(DWORD l, DWORD h)
{
	// Any non-zero value (Zero treated as fatal error).
	return(HANDLE)1;
}

int WINAPI XUserSetProperty(DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

int WINAPI XUserSetContext(DWORD, DWORD, DWORD)
{
	return 0;
}

DWORD WINAPI XUserWriteAchievements(DWORD, DWORD, DWORD)
{
	return 0;
}

DWORD WINAPI XUserCreateAchievementEnumerator(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, PHANDLE phEnum)
{
	*phEnum = INVALID_HANDLE_VALUE;
	return 0;
}

DWORD WINAPI XUserReadStats(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD * pcbResults, DWORD * pResults, void *)
{
	*pcbResults = 4;
	*pResults = 0;
	return 0;
}

DWORD WINAPI XUserCreateStatsEnumeratorByRank(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, PHANDLE phEnum)
{
	*phEnum = INVALID_HANDLE_VALUE;
	return 0;
}

DWORD WINAPI XUserCreateStatsEnumeratorByXuid(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, PHANDLE phEnum)
{
	*phEnum = INVALID_HANDLE_VALUE;
	return 0;
}

int WINAPI XUserSetContextEx(DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

DWORD WINAPI XLivePBufferGetByteArray(FakeProtectedBuffer * pBuffer, int offset, BYTE * destination, int size)
{
	if(!pBuffer || pBuffer->dwMagic != FAKE_MAGIC || !destination || offset < 0 || offset+size > pBuffer->iSize)
		return 0;

	memcpy(destination, pBuffer->byteData+offset, size);
	return 0;
}

DWORD WINAPI XLivePBufferSetByteArray(FakeProtectedBuffer * pBuffer, int offset, BYTE * source, int size)
{
	if(!pBuffer || pBuffer->dwMagic != FAKE_MAGIC || !source || offset < 0 || offset+size > pBuffer->iSize)
		return 0;

	memcpy(pBuffer->byteData+offset, source, size);
	return 0;
}

int WINAPI XLiveInitializeEx(void *, int)
{
	return 0;
}

DWORD WINAPI XSessionCreate(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return -1;
}

DWORD WINAPI XStringVerify(DWORD, DWORD, DWORD, DWORD, DWORD, WORD * pResult, DWORD)
{
	*pResult = 0;
	return 0;
}

DWORD WINAPI XStorageUploadFromMemory(DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

int WINAPI XOnlineStartup()
{
	return 0; 
}

int WINAPI XOnlineCleanup()
{
	return 0;
}

DWORD WINAPI XFriendsCreateEnumerator(DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

int WINAPI XUserMuteListQuery(DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

int WINAPI XInviteGetAcceptedInfo(DWORD, DWORD)
{
	return 1; 
}

int WINAPI XInviteSend(DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

DWORD WINAPI XSessionWriteStats(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

int WINAPI XSessionStart(DWORD, DWORD, DWORD)
{
	return 0;
}

DWORD WINAPI XSessionSearchEx(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

DWORD WINAPI XSessionModify(DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

DWORD WINAPI XSessionMigrateHost(DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

int WINAPI XOnlineGetNatType()
{
	return 0; 
}

DWORD WINAPI XSessionLeaveLocal(DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

DWORD WINAPI XSessionJoinRemote(DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

DWORD WINAPI XSessionJoinLocal(DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

DWORD WINAPI XSessionGetDetails(DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

int WINAPI XSessionFlushStats(DWORD, DWORD)
{
	return 0; 
}

DWORD WINAPI XSessionDelete(DWORD, DWORD)
{
	return 0; 
}

DWORD WINAPI XUserReadProfileSettings(DWORD dwTitleId, DWORD dwUserIndex, DWORD dwNumSettingIds, DWORD * pdwSettingIds, DWORD * pcbResults, XUSER_READ_PROFILE_SETTINGS * pResults, DWORD pOverlapped)
{
	if(*pcbResults < 1036) 
	{
		// TODO: make correct calculation by IDs.
		*pcbResults = 1036;
		return ERROR_INSUFFICIENT_BUFFER;
	}

	memset(pResults, 0, *pcbResults);
	pResults->dwLength = *pcbResults - sizeof(XUSER_READ_PROFILE_SETTINGS);
	pResults->pSettings =(BYTE *)pResults + sizeof(XUSER_READ_PROFILE_SETTINGS);
	return 0;
}

int WINAPI XSessionEnd(DWORD, DWORD)
{
	return 0;
}

DWORD WINAPI XSessionArbitrationRegister(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD) 
{ 
	return 0; 
}

DWORD WINAPI XTitleServerCreateEnumerator(DWORD, DWORD, DWORD, PHANDLE phEnum) 
{
	*phEnum = INVALID_HANDLE_VALUE;
	return 0;
}

DWORD WINAPI XSessionLeaveRemote(DWORD, DWORD, DWORD, DWORD)
{ 
	return 0; 
}

DWORD WINAPI XUserWriteProfileSettings(DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

DWORD WINAPI XStorageBuildServerPath(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

DWORD WINAPI XStorageDownloadToMemory(DWORD dwUserIndex, DWORD, DWORD, DWORD, DWORD, DWORD, void *)
{
	return 0; 
}

DWORD WINAPI XLiveProtectedVerifyFile(HANDLE hContentAccess, VOID * pvReserved, PCWSTR pszFilePath)
{
	return 0;
}

DWORD WINAPI XLiveContentCreateAccessHandle(DWORD dwTitleId, void * pContentInfo, DWORD dwLicenseInfoVersion, void * xebBuffer, DWORD dwOffset, HANDLE * phAccess, void * pOverlapped)
{
	if(phAccess)
		*phAccess = INVALID_HANDLE_VALUE;

	// TODO: Fix it
	return E_OUTOFMEMORY;
}

DWORD WINAPI XLiveContentUninstall(void * pContentInfo, void * pxuidFor, void * pInstallCallbackParams)
{
	return 0;
}

DWORD WINAPI XLiveContentGetPath(DWORD dwUserIndex, void * pContentInfo, wchar_t * pszPath, DWORD * pcchPath)
{
	if(pcchPath)
		*pcchPath = 0;

	if(pszPath)
		*pszPath = 0;

	return 0;
}

DWORD WINAPI XLiveContentCreateEnumerator(DWORD, void *, DWORD *pchBuffer, HANDLE * phContent)
{
	if(phContent)
		*phContent = INVALID_HANDLE_VALUE;

	return 0;
}

DWORD WINAPI XLiveContentRetrieveOffersByDate(DWORD dwUserIndex, DWORD dwOffserInfoVersion, SYSTEMTIME * pstStartDate, void * pOffserInfoArray, DWORD * pcOfferInfo, void * pOverlapped)
{
	if(pcOfferInfo)
		*pcOfferInfo = 0;

	return 0;
} 

DWORD WINAPI XShowMarketplaceUI(DWORD dwUserIndex, DWORD dwEntryPoint, ULONGLONG dwOfferId, DWORD dwContentCategories)
{
	return 1;
}

DWORD WINAPI xlive_5367(HANDLE, DWORD, DWORD, BYTE *, DWORD)
{
	return 1;
}

DWORD WINAPI xlive_5372(HANDLE, DWORD, DWORD, DWORD, BYTE *, HANDLE)
{
	return 1;
}

void CXLiveHook::Install()
{
	// Detour XWSAStartup (xlive_1)
	CPatcher::InstallDetourPatch("xlive.dll", 1, (DWORD)XWSAStartup);
	// Detour XWSACleanup (xlive_2)
	CPatcher::InstallDetourPatch("xlive.dll", 2, (DWORD)XWSACleanup);
	// Detour XSocketCreate (xlive_3)
	CPatcher::InstallDetourPatch("xlive.dll", 3, (DWORD)XSocketCreate);
	// Detour XSocketClose (xlive_4)
	CPatcher::InstallDetourPatch("xlive.dll", 4, (DWORD)XSocketClose);
	// Detour XSocketShutdown (xlive_5)
	CPatcher::InstallDetourPatch("xlive.dll", 5, (DWORD)XSocketShutdown);
	// Detour XSocketIOCTLSocket (xlive_6)
	CPatcher::InstallDetourPatch("xlive.dll", 6, (DWORD)XSocketIOCTLSocket);
	// Detour XSocketSetSockOpt (xlive_7)
	CPatcher::InstallDetourPatch("xlive.dll", 7, (DWORD)XSocketSetSockOpt);
	// Detour XSocketGetSockName (xlive_9)
	CPatcher::InstallDetourPatch("xlive.dll", 9, (DWORD)XSocketGetSockName);
	// Detour XSocketBind (xlive_11)
	CPatcher::InstallDetourPatch("xlive.dll", 11, (DWORD)XSocketBind);
	// Detour XSocketConnect (xlive_12)
	CPatcher::InstallDetourPatch("xlive.dll", 12, (DWORD)XSocketConnect);
	// Detour XSocketListen (xlive_13)
	CPatcher::InstallDetourPatch("xlive.dll", 13, (DWORD)XSocketListen);
	// Detour XSocketAccept (xlive_14)
	CPatcher::InstallDetourPatch("xlive.dll", 14, (DWORD)XSocketAccept);
	// Detour XSocketSelect (xlive_15)
	CPatcher::InstallDetourPatch("xlive.dll", 15, (DWORD)XSocketSelect);
	// Detour XSocketRecv (xlive_18)
	CPatcher::InstallDetourPatch("xlive.dll", 18, (DWORD)XSocketRecv);
	// Detour XSocketRecvFrom (xlive_20)
	CPatcher::InstallDetourPatch("xlive.dll", 20, (DWORD)XSocketRecvFrom);
	// Detour XSocketSend (xlive_22)
	CPatcher::InstallDetourPatch("xlive.dll", 22, (DWORD)XSocketSend);
	// Detour XSocketSendTo (xlive_24)
	CPatcher::InstallDetourPatch("xlive.dll", 24, (DWORD)XSocketSendTo);
	// Detour XSocketInet_Addr (xlive_26)
	CPatcher::InstallDetourPatch("xlive.dll", 26, (DWORD)XSocketInet_Addr);
	// Detour XWSAGetLastError (xlive_27)
	CPatcher::InstallDetourPatch("xlive.dll", 27, (DWORD)XWSAGetLastError);
	// Detour XSocketNTOHS (xlive_38)
	CPatcher::InstallDetourPatch("xlive.dll", 38, (DWORD)XSocketNTOHS);
	// Detour XSocketNTOHL (xlive_39)
	CPatcher::InstallDetourPatch("xlive.dll", 39, (DWORD)XSocketNTOHL);
	// Detour XNetStartup (xlive_51)
	CPatcher::InstallDetourPatch("xlive.dll", 51, (DWORD)XNetStartup);
	// Detour XNetCleanup (xlive_52)
	CPatcher::InstallDetourPatch("xlive.dll", 52, (DWORD)XNetCleanup);
	// Detour XNetXnAddrToInAddr (xlive_57)
	CPatcher::InstallDetourPatch("xlive.dll", 57, (DWORD)XNetXnAddrToInAddr);
	// Detour XNetServerToInAddr (xlive_58)
	CPatcher::InstallDetourPatch("xlive.dll", 58, (DWORD)XNetServerToInAddr);
	// Detour XNetUnregisterInAddr (xlive_63)
	CPatcher::InstallDetourPatch("xlive.dll", 63, (DWORD)XNetUnregisterInAddr);
	// Detour XNetGetConnectStatus (xlive_66)
	CPatcher::InstallDetourPatch("xlive.dll", 66, (DWORD)XNetGetConnectStatus);
	// Detour XNetQosListen (xlive_69)
	CPatcher::InstallDetourPatch("xlive.dll", 69, (DWORD)XNetQosListen);
	// Detour XNetQosLookup (xlive_70)
	CPatcher::InstallDetourPatch("xlive.dll", 70, (DWORD)XNetQosLookup);
	// Detour XNetQosRelease (xlive_72)
	CPatcher::InstallDetourPatch("xlive.dll", 72, (DWORD)XNetQosRelease);
	// Detour XNetGetTitleXnAddr (xlive_73)
	CPatcher::InstallDetourPatch("xlive.dll", 73, (DWORD)XNetGetTitleXnAddr);
	// Detour XNetGetEthernetLinkStatus (xlive_75)
	CPatcher::InstallDetourPatch("xlive.dll", 75, (DWORD)XNetGetEthernetLinkStatus);
	// Detour XNetSetSystemLinkPort (xlive_84)
	CPatcher::InstallDetourPatch("xlive.dll", 84, (DWORD)XNetSetSystemLinkPort);
	// Detour XNotifyGetNext (xlive_651)
	CPatcher::InstallDetourPatch("xlive.dll", 651, (DWORD)XNotifyGetNext);
	// Detour XNotifyPositionUI (xlive_652)
	CPatcher::InstallDetourPatch("xlive.dll", 652, (DWORD)XNotifyPositionUI);
	// Detour XGetOverlappedExtendedError (xlive_1082)
	CPatcher::InstallDetourPatch("xlive.dll", 1082, (DWORD)XGetOverlappedExtendedError);
	// Detour XGetOverlappedResult (xlive_1083)
	CPatcher::InstallDetourPatch("xlive.dll", 1083, (DWORD)XGetOverlappedResult);
	// Detour XLiveInitialize (xlive_5000)
	CPatcher::InstallDetourPatch("xlive.dll", 5000, (DWORD)XLiveInitialize);
	// Detour XLiveInput (xlive_5001)
	CPatcher::InstallDetourPatch("xlive.dll", 5001, (DWORD)XLiveInput);
	// Detour XLiveRender (xlive_5002)
	CPatcher::InstallDetourPatch("xlive.dll", 5002, (DWORD)XLiveRender);
	// Detour XLiveUninitialize (xlive_5003)
	CPatcher::InstallDetourPatch("xlive.dll", 5003, (DWORD)XLiveUninitialize);
	// Detour XLiveOnCreateDevice (xlive_5005)
	CPatcher::InstallDetourPatch("xlive.dll", 5005, (DWORD)XLiveOnCreateDevice);
	// Detour XLiveOnResetDevice (xlive_5007)
	CPatcher::InstallDetourPatch("xlive.dll", 5007, (DWORD)XLiveOnResetDevice);
	// Detour XHVCreateEngine (xlive_5008)
	CPatcher::InstallDetourPatch("xlive.dll", 5008, (DWORD)XHVCreateEngine);
	// Detour XLivePBufferAllocate (xlive_5016)
	CPatcher::InstallDetourPatch("xlive.dll", 5016, (DWORD)XLivePBufferAllocate);
	// Detour XLivePBufferFree (xlive_5017)
	CPatcher::InstallDetourPatch("xlive.dll", 5017, (DWORD)XLivePBufferFree);
	// Detour XLivePBufferGetByte (xlive_5018)
	CPatcher::InstallDetourPatch("xlive.dll", 5018, (DWORD)XLivePBufferGetByte);
	// Detour XLivePBufferSetByte (xlive_5019)
	CPatcher::InstallDetourPatch("xlive.dll", 5019, (DWORD)XLivePBufferSetByte);
	// Detour XLivePBufferGetDWORD (xlive_5020)
	CPatcher::InstallDetourPatch("xlive.dll", 5020, (DWORD)XLivePBufferGetDWORD);
	// Detour XLivePBufferSetDWORD (xlive_5021)
	CPatcher::InstallDetourPatch("xlive.dll", 5021, (DWORD)XLivePBufferSetDWORD);
	// Detour XLiveGetUpdateInformation (xlive_5022)
	CPatcher::InstallDetourPatch("xlive.dll", 5022, (DWORD)XLiveGetUpdateInformation);
	// Detour XLiveUpdateSystem (xlive_5024)
	CPatcher::InstallDetourPatch("xlive.dll", 5024, (DWORD)XLiveUpdateSystem);
	// Detour XLivePreTranslateMessage (xlive_5030)
	CPatcher::InstallDetourPatch("xlive.dll", 5030, (DWORD)XLivePreTranslateMessage);
	// Detour XLiveProtectData (xlive_5034)
	CPatcher::InstallDetourPatch("xlive.dll", 5034, (DWORD)XLiveProtectData);
	// Detour XLiveUnprotectData (xlive_5035)
	CPatcher::InstallDetourPatch("xlive.dll", 5035, (DWORD)XLiveUnprotectData);
	// Detour XLiveCreateProtectedDataContext (xlive_5036)
	CPatcher::InstallDetourPatch("xlive.dll", 5036, (DWORD)XLiveCreateProtectedDataContext);
	// Detour XLiveQueryProtectedDataInformation (xlive_5037)
	CPatcher::InstallDetourPatch("xlive.dll", 5037, (DWORD)XLiveQueryProtectedDataInformation);
	// Detour XLiveCloseProtectedDataContext (xlive_5038)
	CPatcher::InstallDetourPatch("xlive.dll", 5038, (DWORD)XLiveCloseProtectedDataContext);
	// Detour XShowPlayerReviewUI (xlive_5214)
	CPatcher::InstallDetourPatch("xlive.dll", 5214, (DWORD)XShowPlayerReviewUI);
	// Detour XShowGuideUI (xlive_5215)
	CPatcher::InstallDetourPatch("xlive.dll", 5215, (DWORD)XShowGuideUI);
	// Detour XCloseHandle (xlive_5251)
	CPatcher::InstallDetourPatch("xlive.dll", 5251, (DWORD)XCloseHandle);
	// Detour XShowGamerCardUI (xlive_5252)
	CPatcher::InstallDetourPatch("xlive.dll", 5252, (DWORD)XShowGamerCardUI);
	// Detour XCancelOverlapped (xlive_5254)
	CPatcher::InstallDetourPatch("xlive.dll", 5254, (DWORD)XCancelOverlapped);
	// Detour XEnumerate (xlive_5256)
	CPatcher::InstallDetourPatch("xlive.dll", 5256, (DWORD)XEnumerate);
	// Detour XShowSigninUI (xlive_5260)
	CPatcher::InstallDetourPatch("xlive.dll", 5260, (DWORD)XShowSigninUI);
	// Detour XUserGetXUID (xlive_5261)
	CPatcher::InstallDetourPatch("xlive.dll", 5261, (DWORD)XUserGetXUID);
	// Detour XUserGetSigninState (xlive_5262)
	CPatcher::InstallDetourPatch("xlive.dll", 5262, (DWORD)XUserGetSigninState);
	// Detour XUserGetName (xlive_5263)
	CPatcher::InstallDetourPatch("xlive.dll", 5263, (DWORD)XUserGetName);
	// Detour XUserAreUsersFriends (xlive_5264)
	CPatcher::InstallDetourPatch("xlive.dll", 5264, (DWORD)XUserAreUsersFriends);
	// Detour XUserCheckPrivilege (xlive_5265)
	CPatcher::InstallDetourPatch("xlive.dll", 5265, (DWORD)XUserCheckPrivilege);
	// Detour XUserGetSigninInfo (xlive_5267)
	CPatcher::InstallDetourPatch("xlive.dll", 5267, (DWORD)XUserGetSigninInfo);
	// Detour XNotifyCreateListener (xlive_5270)
	CPatcher::InstallDetourPatch("xlive.dll", 5270, (DWORD)XNotifyCreateListener);
	// Detour XUserSetProperty (xlive_5276)
	CPatcher::InstallDetourPatch("xlive.dll", 5276, (DWORD)XUserSetProperty);
	// Detour XUserSetContext (xlive_5277)
	CPatcher::InstallDetourPatch("xlive.dll", 5277, (DWORD)XUserSetContext);
	// Detour XUserWriteAchievements (xlive_5278)
	CPatcher::InstallDetourPatch("xlive.dll", 5278, (DWORD)XUserWriteAchievements);
	// Detour XUserCreateAchievementEnumerator (xlive_5280)
	CPatcher::InstallDetourPatch("xlive.dll", 5280, (DWORD)XUserCreateAchievementEnumerator);
	// Detour XUserReadStats (xlive_5281)
	CPatcher::InstallDetourPatch("xlive.dll", 5281, (DWORD)XUserReadStats);
	// Detour XUserCreateStatsEnumeratorByRank (xlive_5284)
	CPatcher::InstallDetourPatch("xlive.dll", 5284, (DWORD)XUserCreateStatsEnumeratorByRank);
	// Detour XUserCreateStatsEnumeratorByXuid (xlive_5286)
	CPatcher::InstallDetourPatch("xlive.dll", 5286, (DWORD)XUserCreateStatsEnumeratorByXuid);
	// Detour XUserSetContextEx (xlive_5292)
	CPatcher::InstallDetourPatch("xlive.dll", 5292, (DWORD)XUserSetContextEx);
	// Detour XLivePBufferGetByteArray (xlive_5294)
	CPatcher::InstallDetourPatch("xlive.dll", 5294, (DWORD)XLivePBufferGetByteArray);
	// Detour XLivePBufferSetByteArray (xlive_5295)
	CPatcher::InstallDetourPatch("xlive.dll", 5295, (DWORD)XLivePBufferSetByteArray);
	// Detour XLiveInitializeEx (xlive_5297)
	CPatcher::InstallDetourPatch("xlive.dll", 5297, (DWORD)XLiveInitializeEx);
	// Detour XSessionCreate (xlive_5300)
	CPatcher::InstallDetourPatch("xlive.dll", 5300, (DWORD)XSessionCreate);
	// Detour XStringVerify (xlive_5303)
	CPatcher::InstallDetourPatch("xlive.dll", 5303, (DWORD)XStringVerify);
	// Detour XStorageUploadFromMemory (xlive_5305)
	CPatcher::InstallDetourPatch("xlive.dll", 5305, (DWORD)XStorageUploadFromMemory);
	// Detour XOnlineStartup (xlive_5310)
	CPatcher::InstallDetourPatch("xlive.dll", 5310, (DWORD)XOnlineStartup);
	// Detour XOnlineCleanup (xlive_5311)
	CPatcher::InstallDetourPatch("xlive.dll", 5311, (DWORD)XOnlineCleanup);
	// Detour XFriendsCreateEnumerator (xlive_5312)
	CPatcher::InstallDetourPatch("xlive.dll", 5312, (DWORD)XFriendsCreateEnumerator);
	// Detour XUserMuteListQuery (xlive_5314)
	CPatcher::InstallDetourPatch("xlive.dll", 5314, (DWORD)XUserMuteListQuery);
	// Detour XInviteGetAcceptedInfo (xlive_5315)
	CPatcher::InstallDetourPatch("xlive.dll", 5315, (DWORD)XInviteGetAcceptedInfo);
	// Detour XInviteSend (xlive_5316)
	CPatcher::InstallDetourPatch("xlive.dll", 5316, (DWORD)XInviteSend);
	// Detour XSessionWriteStats (xlive_5317)
	CPatcher::InstallDetourPatch("xlive.dll", 5317, (DWORD)XSessionWriteStats);
	// Detour XSessionStart (xlive_5318)
	CPatcher::InstallDetourPatch("xlive.dll", 5318, (DWORD)XSessionStart);
	// Detour XSessionSearchEx (xlive_5319)
	CPatcher::InstallDetourPatch("xlive.dll", 5319, (DWORD)XSessionSearchEx);
	// Detour XSessionModify (xlive_5322)
	CPatcher::InstallDetourPatch("xlive.dll", 5322, (DWORD)XSessionModify);
	// Detour XSessionMigrateHost (xlive_5323)
	CPatcher::InstallDetourPatch("xlive.dll", 5323, (DWORD)XSessionMigrateHost);
	// Detour XOnlineGetNatType (xlive_5324)
	CPatcher::InstallDetourPatch("xlive.dll", 5324, (DWORD)XOnlineGetNatType);
	// Detour XSessionLeaveLocal (xlive_5325)
	CPatcher::InstallDetourPatch("xlive.dll", 5325, (DWORD)XSessionLeaveLocal);
	// Detour XSessionJoinRemote (xlive_5326)
	CPatcher::InstallDetourPatch("xlive.dll", 5326, (DWORD)XSessionJoinRemote);
	// Detour XSessionJoinLocal (xlive_5327)
	CPatcher::InstallDetourPatch("xlive.dll", 5327, (DWORD)XSessionJoinLocal);
	// Detour XSessionGetDetails (xlive_5328)
	CPatcher::InstallDetourPatch("xlive.dll", 5328, (DWORD)XSessionGetDetails);
	// Detour XSessionFlushStats (xlive_5329)
	CPatcher::InstallDetourPatch("xlive.dll", 5329, (DWORD)XSessionFlushStats);
	// Detour XSessionDelete (xlive_5330)
	CPatcher::InstallDetourPatch("xlive.dll", 5330, (DWORD)XSessionDelete);
	// Detour XUserReadProfileSettings (xlive_5331)
	CPatcher::InstallDetourPatch("xlive.dll", 5331, (DWORD)XUserReadProfileSettings);
	// Detour XSessionEnd (xlive_5332)
	CPatcher::InstallDetourPatch("xlive.dll", 5332, (DWORD)XSessionEnd);
	// Detour XSessionArbitrationRegister (xlive_5333)
	CPatcher::InstallDetourPatch("xlive.dll", 5333, (DWORD)XSessionArbitrationRegister);
	// Detour XTitleServerCreateEnumerator (xlive_5335)
	CPatcher::InstallDetourPatch("xlive.dll", 5335, (DWORD)XTitleServerCreateEnumerator);
	// Detour XSessionLeaveRemote (xlive_5336)
	CPatcher::InstallDetourPatch("xlive.dll", 5336, (DWORD)XSessionLeaveRemote);
	// Detour XUserWriteProfileSettings (xlive_5337)
	CPatcher::InstallDetourPatch("xlive.dll", 5337, (DWORD)XUserWriteProfileSettings);
	// Detour XStorageBuildServerPath (xlive_5344)
	CPatcher::InstallDetourPatch("xlive.dll", 5344, (DWORD)XStorageBuildServerPath);
	// Detour XStorageDownloadToMemory (xlive_5345)
	CPatcher::InstallDetourPatch("xlive.dll", 5345, (DWORD)XStorageDownloadToMemory);
	// Detour XLiveProtectedVerifyFile (xlive_5349)
	CPatcher::InstallDetourPatch("xlive.dll", 5349, (DWORD)XLiveProtectedVerifyFile);
	// Detour XLiveContentCreateAccessHandle (xlive_5350)
	CPatcher::InstallDetourPatch("xlive.dll", 5350, (DWORD)XLiveContentCreateAccessHandle);
	// Detour XLiveContentUninstall (xlive_5352)
	CPatcher::InstallDetourPatch("xlive.dll", 5352, (DWORD)XLiveContentUninstall);
	// Detour XLiveContentGetPath (xlive_5355)
	CPatcher::InstallDetourPatch("xlive.dll", 5355, (DWORD)XLiveContentGetPath);
	// Detour XLiveContentCreateEnumerator (xlive_5360)
	CPatcher::InstallDetourPatch("xlive.dll", 5360, (DWORD)XLiveContentCreateEnumerator);
	// Detour XLiveContentRetrieveOffersByDate (xlive_5361)
	CPatcher::InstallDetourPatch("xlive.dll", 5361, (DWORD)XLiveContentRetrieveOffersByDate);
	// Detour XShowMarketplaceUI (xlive_5365)
	CPatcher::InstallDetourPatch("xlive.dll", 5365, (DWORD)XShowMarketplaceUI);
	// Detour xlive_5367 (xlive_5367)
	CPatcher::InstallDetourPatch("xlive.dll", 5367, (DWORD)xlive_5367);
	// Detour xlive_5372 (xlive_5372)
	CPatcher::InstallDetourPatch("xlive.dll", 5372, (DWORD)xlive_5372);
}
