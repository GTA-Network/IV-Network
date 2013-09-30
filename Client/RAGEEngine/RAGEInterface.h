//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: RAGEInterface.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef RAGEInterface_h
#define RAGEInterface_h

#include "CString.h"
#include <WinSock2.h>
#include <Windows.h>

#ifndef RAGEENGINE_GAME_VERSION
#define RAGEENGINE_GAME_VERSION 0x7
#endif

#ifdef _CLIENT

struct RAGEOffsetContent {
	// Basic Offset
	unsigned 	iOffsetSlot;
	bool		bInitialised;
	CString		strAddressName;
	CString		strAddressDescription;
	
	// Switch
	bool		bPattern;
	
	// Pattern
	CString		strPattern;
	CString		strPatternContext;
	
	// Address
	unsigned	uiAddress;
};

//RAGEOffsetContent arrRageOffsets[];
enum eRAGEOffsets;
class RAGEOffsets;
class RAGEFunctions;

#else
#include "RAGECommon.h"
#include "RAGE/RAGEOffsets.h"
#include "RAGE/RAGEFunctions.h"
#endif

class RAGEEngineInterface {
private:
	RAGEFunctions	*pFunctions;
	RAGEOffsets		*pOffsets;
public:
#ifdef _CLIENT
	void			Initialise() {};
	void			DeInitialise() {};
	
	unsigned		GetRageFunctions() { return 1; };
	unsigned		GetRageOffset(eRAGEOffsets offset) { return 1; };
#else
	void			Initialise();
	void			DeInitialise();
	
	unsigned		GetRageFunctions();
	unsigned		GetRageOffset(eRAGEOffsets offset);
#endif
};

#endif // RAGEInterface_h