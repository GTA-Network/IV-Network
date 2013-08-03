//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: Common.h
// Project: (Shared)
// Author: CrackHD
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef Common_h
#define Common_h

// Common definitions for both client and server, windows and linux (structs, etc).

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <windowsx.h>
#endif

// include
#include "CString.h"

// typedef
typedef CString string;							// CString class defined is in /Shared/CString.h
typedef unsigned short EntityId;

// If compiling in debug mode force mod debug mode
#ifdef _DEBUG
#undef IVMP_DEBUG
#define IVMP_DEBUG 1
#endif

// Forced debug
#ifdef FORCE_DEBUG
#ifndef IVMP_DEBUG
#define IVMP_DEBUG 1
#endif
#endif

// Forced release
#ifdef FORCE_RELEASE
#ifdef IVMP_DEBUG
#undef IVMP_DEBUG
#endif
#endif

// Version defines
#ifdef IVMP_DEBUG
#define DEBUG_IDENTIFIER " - Debug"
#else
#define DEBUG_IDENTIFIER
#endif

// define
#define MOD_NAME "IV:Multiplayer"
#define INVALID_ENTITY_ID ((EntityId)0xFFFF)

// Mod version string
#define MOD_VERSION_STRING "1.0.0 DEV"

// Version identifiers
#define VERSION_IDENTIFIER MOD_NAME " " MOD_VERSION_STRING DEBUG_IDENTIFIER " [" __DATE__ ", " __TIME__ "]"
#define VERSION_IDENTIFIER_2 MOD_NAME " " MOD_VERSION_STRING DEBUG_IDENTIFIER

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

// Library extension
#ifdef _WIN32
#define LIBRARY_EXTENSION ".dll"
#else
#define LIBRARY_EXTENSION ".so"
#endif

// Library Names
#define CLIENT_CORE_NAME "Client.Core"
#define CLIENT_LAUNCH_HELPER_NAME "Client.LaunchHelper"
#define SERVER_CORE_NAME "Server.Core"
#define NETWORK_MODULE_NAME "Network.Core"
#define VFS_MODULE_NAME "Client.VFS"

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
#pragma warning(disable:4409) // Disable illegal instruction warming(asm)
#pragma warning(disable:4042) // Disable LNK 4042 extra objects

// Macros
#define		ARRAY_LENGTH(array)			(sizeof(array) / sizeof(array[0]))
#define		SAFE_DELETE(memory)			if(memory) { delete memory; memory = NULL; }
#define		SAFE_RELEASE(p)				{ if ( (p) ) { (p)->Release(); (p) = NULL; } }
#define		PAD(prefix, name, size)		BYTE prefix##_##name##[size]

// Bit manipulation macros
#define SET_BIT(a, b) a |= b
#define IS_BIT_SET(a, b) ((a & b) != 0)
#define UNSET_BIT(a, b) a &= ~(b)

#endif // Common_h