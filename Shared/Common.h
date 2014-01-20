/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef Common_h
#define Common_h

#if _WIN64 || __x86_64__ || __ppc64__
#define IS64BIT 1
#else
#define IS64BIT 0
#endif

#if defined(_WIN64) || defined(_WIN32)
#ifdef WIN32
#undef WIN32
#endif
#define WIN32 1
#elif __APPLE__
#define MAC 1
#elif __linux
#define LINUX 1
#elif __unix
#define UNIX 1
#elif __posix
#define POSIX 1
#endif

#if WIN32
#include <yvals.h>
#if __cplusplus <= 199711L && _HAS_CPP0X == 0
#error "Please use at least Visual Studio 2013. This project was developed using VS2013 and/or GCC 4.8."
#else
// Check if all used features are vailable
#if !defined(_CPPLIB_VER) || _CPPLIB_VER < 610
#error "Use at least VS2013."
#endif

#if !defined(_HAS_DECLTYPE) || _HAS_DECLTYPE < 1
#error "Decltype is required. Use at least VS2013."
#endif

#if !defined(_HAS_INITIALIZER_LISTS) || _HAS_INITIALIZER_LISTS < 1
#error "Initialiizer lists is required. Use at least VS2013."
#endif

//#if !defined(_HAS_REF_QUALIFIER) || _HAS_REF_QUALIFIER < 1
//#error "Please use at least VS2013."
//#endif

#if !defined(_HAS_RVALUE_REFERENCES) || _HAS_RVALUE_REFERENCES < 1
#error "Rvalue References is required. Use at least VS2013."
#endif

#if !defined(_HAS_SCOPED_ENUM) || _HAS_SCOPED_ENUM < 1
#error "Scoped enum is required. Use at least VS2013."
#endif

#if !defined(_HAS_TEMPLATE_ALIAS) || _HAS_TEMPLATE_ALIAS < 1
#error "Template alias is required. Use at least VS2013."
#endif

#if !defined(_HAS_VARIADIC_TEMPLATES) || _HAS_VARIADIC_TEMPLATES < 1
#error "Variadic templates is required. Use at least VS2013."
#endif

#endif
#elif LINUX
#if __GNUC__ < 4 || (__GNUC__ < 4 && __GNUC_MINOR__ < 7) || (__GNUC__ < 4 && __GNUC_MINOR__ < 7 && __GNUC_PATCHLEVEL__ < 2)
#error "Use at least GCC 4.7.2"
#endif 

#if __cplusplus <= 199711L
if !defined(__GXX_EXPERIMENTAL_CXX0X__) || __GXX_EXPERIMENTAL_CXX0X__ != 1
#error "C++11 is required. Try --std=c++0x"
#endif
#endif

#if _DEBUG == 1 && !defined(DEBUG)
#define DEBUG
#endif

#pragma warning( disable : 4003)

// at this point we can use C++11

#ifdef WIN32
#include <WinSock2.h> // Just to be sure that there will never be a fucking include guard error
#include <Windows.h>
#include <iostream>
#endif


// IVNetwork crap
// TODO: clean up

// DirectX Input version
#define DIRECTINPUT_VERSION 0x0800

// include
#include "CColor.h"
#include "CString.h"

#ifdef _CLIENT
using namespace std; // Conflicts with string(std::string) in network stuff
#include	<aclapi.h>
#include	<algorithm>
#include	<assert.h>
#include	<ctime>
#include	<d3d9.h>
#include	<list>
#include	<map>
#include	<queue>
#include	<process.h>
#include	<Psapi.h>
#include	<stdio.h>
#include	<stdio.h>
#include	<string>
#include	<tchar.h>
#include	<vector>
#include	"Game\eGame.h"
#include	"Network\CBitStream.h"
#endif


// typedef
//typedef CString string;							// CString class defined is in /Shared/CString.h
typedef unsigned short EntityId;


#include "CNetSync.h"

// Version defines
#ifdef DEBUG
#define DEBUG_IDENTIFIER " - Debug"
#else
#define DEBUG_IDENTIFIER
#endif

#define INVALID_ENTITY_ID ((EntityId)0xFFFF)
#define NETWORK_VERSION 0x1

// Mod version string
#define MOD_VERSION_STRING "1.0.0 DEV EFLC"

// Masterlist Information
#define MASTERLIST_URL 		"www.gta-network.net/masterlist/iv"
#define MASTERLIST_TIMEOUT	50000

// Version identifiers
#define VERSION_IDENTIFIER MOD_VERSION_STRING DEBUG_IDENTIFIER " [" __DATE__ ", " __TIME__ "]"
#define VERSION_IDENTIFIER_2 MOD_VERSION_STRING DEBUG_IDENTIFIER

// Operating system string
#ifdef _WIN32
#define OS_STRING "Windows"
#else
#define OS_STRING "Linux"
#endif

// Library debug suffix
#ifdef _DEBUG
#define DEBUG_SUFFIX // ".Debug"
#else
#define DEBUG_SUFFIX
#endif

// ExitProcess macro for linux
#ifndef _WIN32
#define ExitProcess exit
#endif

// Library extension
#ifdef _WIN32
#define LIBRARY_EXTENSION ".dll"
#else
#define LIBRARY_EXTENSION ".so"
#endif

// Basic Names
#define _DEV
//#define CHEAP_RELEASE
#define MOD_NAME "IV:Network"
#define MOD_SHORT_NAME "IVN"
#define MOD_SHORT_NAME_ILLEGAL "IV:Net"
#define CLIENT_CORE_NAME "IVNetwork"
#define SERVER_CORE_NAME "Server.Core"
#define NETWORK_MODULE_NAME "Network.Core"
#define REGISTRY_AREA "Software\\IVNetwork"
#define GAME_DIRECTORY "GrandTheftAutoDirectory"
#define MP_START_EXECUTABLE "LaunchIVNetwork.exe"
#define GAME_DEFAULT_EXECUTABLE "EFLC.exe"
#define SHORT_URI_LAUNCH_1 "ivn://"
#define SHORT_URI_LAUNCH_2 "ivnetwork://"
#define SHORT_URI_LAUNCH_3 "ivn"
#define SHORT_URI_LAUNCH_4 "ivnetwork"
#define SHORT_COMMANDLINE_LAUNCH_1 "-ivn"
#define DEFAULT_REGISTRY_GAME_DIRECTORY "Software\\Rockstar Games\\EFLC"

// Library Exports
#ifdef EXPORT
#undef EXPORT
#endif
#ifdef _WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C"
#endif

// Include all defines for game limits
#include "GameLimits.h"

// Warning disable
#pragma warning(disable:4996) // Disables _s warning
#pragma warning(disable:4409) // Disable illegal instruction warning(asm)
#pragma warning(disable:4042) // Disable LNK 4042 extra objects
#pragma warning(disable:4099) // Disable PDB not found warnings
#pragma warning(disable:4244) // Disable converstion error warnings

// Macros
#define ARRAY_LENGTH(array)	(sizeof(array) / sizeof(array[0]))
#define	SAFE_DELETE(memory)	{ delete memory; memory = nullptr; }
#define	SAFE_RELEASE(p)	{ if ( (p) ) { (p)->Release(); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(memory) if(memory) { delete [] memory; memory = nullptr; }
#define SAFE_FREE(memory) if(memory) { free(memory); memory = nullptr; }
#define	PAD(prefix, name, size) unsigned char prefix##_##name##[size]

// Bit manipulation macros
#define SET_BIT(a, b) a |= b
#define IS_BIT_SET(a, b) ((a & b) != 0)
#define UNSET_BIT(a, b) a &= ~(b)

// Logfile definitions
#define CLIENT_LOG_FILE "multiplayer//IVN-Client.log"
#define CLIENT_CHATLOG_FILE "multiplayer//IVN-Chat.log"
#define CLIENT_SETTINGS_FILE "multiplayer//IVN-Settings.xml"

// Chat definitions
#define	CHAT_MAX_CHAT_LENGTH 128
#define	CHAT_RENDER_LINES 10
#define	CHAT_MAX_LINES 200

// Spawn position
#define DEFAULT_SPAWN_POSITION -547.40f, -961.30f, 4.84f

// XLive Hook
#define FAKE_MAGIC 0xDEADDEAD

// Camera defs
#define CVEC_TO_D3DVEC(vec) &D3DXVECTOR3(vec.fX, vec.fY, vec.fZ)
#define D3DVEC_TO_CVEC(vec) &CVector3(vec.x, vec.y, vec.z)

// Macros
#define GET_RPC_CODEX(x) CString("IVN0xF%dF", int(x)).Get()
#define CHECK_VALID(x) if(!x) return false;
#define CHECK_VALID_VOID(x) if(!x) return;


#endif // Common_h