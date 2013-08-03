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

// include
#include "CString.h"

// typedef
typedef CString string;							// CString class defined is in /Shared/CString.h
typedef unsigned short EntityId;

// define
#define MOD_NAME "IV:Multiplayer"

// Operating system string
#ifdef WIN32
#define OS_STRING "Windows"
#else
#define OS_STRING "Linux"
#endif

// Library debug suffix
#ifdef _DEBUG
#define DEBUG_SUFFIX ".Debug"
#else
#define DEBUG_SUFFIX
#endif

// Library extension
#ifdef WIN32
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
#ifdef WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C"
#endif

// Warning disable
#pragma warning(disable:4996)

#endif // Common_h