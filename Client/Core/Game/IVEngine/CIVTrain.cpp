//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CIVTrain.cpp
// Project: Client.Core
// Author(s): DMA, FRi
// License: See LICENSE in root directory
//
//==============================================================================

// NOTE: WORK IN PROGRESS; DO NOT CHANGE THIS FILE!!
// Question: do we get the scripting handle or the ivtrain class pointer back?

#include "CIVTrain.h"
#include "../Scripting.h"

// Disable C4748 warning...
#pragma warning( disable : 4748 )

CIVTrain::CIVTrain(EntityId trainId, DWORD dwTrainPointer, String strTrainName)
{
	// Reset our train stuff
	m_dwPointer = NULL;
	m_pTrain = NULL;
	m_trainId = INVALID_ENTITY_ID;
	m_strTrainName = "none";

	// Set initial stuff
	m_trainId = trainId;
	m_dwPointer = dwTrainPointer;
	m_strTrainName = strTrainName;
}

CIVTrain::~CIVTrain()
{
	// Just delete our data and remove the train
	unsigned int uiScriptingHandle = m_pTrain->dwHandle;
	Scripting::DeleteMissionTrain(&uiScriptingHandle);

	// Delete our train instance
	SAFE_DELETE(m_pTrain);
}

unsigned int CIVTrain::GetTrainHandle()
{
	IVTrain * pTrain = m_pTrain;
	if(pTrain)
		return ((unsigned int)(pTrain->dwHandle) != NULL);
	else
		return -1;
}

DWORD CIVTrain::GetTrainPointer()
{
	IVTrain * pTrain = m_pTrain;
	if(pTrain)
		return m_dwPointer;
	else
		return 0xFFFFFF;
}
void CIVTrain::SetTrainOffsetsAndCreate(EntityId trainRegisterId)
{
	//		Size				1		   1(or 4)	 1(or 4)	1(or 4)  (int *)4		 4	   (BYTE *)0x13	   0x4F     0x4F
	//		Train			(DWORD)Pointer  DWORD     DWORD      DWORD      DWORD       DWORD      BYTE		  DWORD     DWORD		// some unk are in there...
	DWORD dwTrainQueens1[] = { 0x15BE4BC, 0x15BE48C, 0x15BD4D8, 0x15BD908, 0x15BE4F0, 0x15BDD00, 0x15BD3E8, 0x15BE0C8, 0x15BD940};
	DWORD dwTrainQueens2[] = { 0x15BE4C0, 0x15BE490, 0x15BD4DC, 0x15BD90C, 0x15BE630, 0x15BDD50, 0x15BD3FC, 0x15BE118, 0x15BD990};
	DWORD dwTrainBronx1[] = { 0x15BE4C4, 0x15BE494, 0x15BD4E0, 0x15BD910, 0x15BE770, 0x15BDDA0, 0x15BD410, 0x15BE168, 0x15BD9E0};
	DWORD dwTrainBronx2[] = { 0x15BE4C8, 0x15BE498, 0x15BD4E4, 0x15BD914, 0x15BE8B0, 0x15BDDF0, 0x15BD424, 0x15BE1B8, 0x15BDA30};

	// Create our vars
	DWORD dwAddress1,dwAddress2,dwAddress3,dwAddress4,dwAddress5,dwAddress6,dwAddress7;
	BYTE byteAddress1;
	DWORD dwPointer;

	// Define our call address
	DWORD FUNC_CTrain__CreateTrain = (CGame::GetBase() + 0x94A240);

	if(trainRegisterId == 1)
	{
		char *szRoute = "common:/data/paths/TracksQueens.dat";
		dwPointer = dwTrainQueens1[0];

		dwAddress1 = dwTrainQueens1[1];
		dwAddress2 = dwTrainQueens1[2];
		dwAddress3 = dwTrainQueens1[3];
		dwAddress4 = dwTrainQueens1[4];
		dwAddress5 = dwTrainQueens1[5];
		dwAddress6 = dwTrainQueens1[7];
		dwAddress7 = dwTrainQueens1[8];

		byteAddress1 = (BYTE)dwTrainQueens1[6];
		unsigned int wHandle = NULL;

		// Check if our train already exists
		BYTE dwCheck = *(BYTE *)(CGame::GetBase() + 0x015BE4BC);
		if(dwCheck != NULL)
			return;

		// Create our train
		//NOTE: Assembler VS 2010 doesn't recognize jnz and jn... 
		WORD dwTemp;
		short unkownLoc = (CGame::GetBase() + 0x94A743);
		_asm
		{
			pushf
			pop ax
			and ax, 0x100
			mov [dwTemp], ax
			push ax
			popf
		}
		if(!dwTemp) 
		{
			_asm
			{
				jmp unkownLoc
				push szRoute
				push dwPointer
				push dwAddress7
				push dwAddress6
				push byteAddress1
				push dwAddress5
				push dwAddress4
				push dwAddress3
				push dwAddress2
				push dwAddress1
				call FUNC_CTrain__CreateTrain
				add esp, 28h
			}
		}
		else
		{
			_asm
			{
				push szRoute
				push dwPointer
				push dwAddress7
				push dwAddress6
				push byteAddress1
				push dwAddress5
				push dwAddress4
				push dwAddress3
				push dwAddress2
				push dwAddress1
				call FUNC_CTrain__CreateTrain
				add esp, 28h
			}
		}
		// Todo: Get result (mov wHandle, al)
	}
	else if(trainRegisterId == 2)
	{
		// Create our Train
		char *szRoute = "common:/data/paths/TracksQueens2.dat";
		dwPointer = dwTrainQueens2[0];

		dwAddress1 = dwTrainQueens2[1];
		dwAddress2 = dwTrainQueens2[2];
		dwAddress3 = dwTrainQueens2[3];
		dwAddress4 = dwTrainQueens2[4];
		dwAddress5 = dwTrainQueens2[5];
		dwAddress6 = dwTrainQueens2[7];
		dwAddress7 = dwTrainQueens2[8];

		byteAddress1 = (BYTE)dwTrainQueens2[6];
		unsigned int wHandle = NULL;

		// Check if our train already exists
		BYTE dwCheck = *(BYTE *)(CGame::GetBase() + 0x015BE4C0);
		if(dwCheck != NULL)
			return;
		
		// Create our train
		//NOTE: Assembler VS 2010 doesn't recognize jnz and jn... 
		WORD dwTemp;
		short unkownLoc = (CGame::GetBase() + 0x94A743);
		_asm
		{
			pushf
			pop ax
			and ax, 0x100
			mov [dwTemp], ax
			push ax
			popf
		}
		if(!dwTemp) 
		{
			_asm
			{
				jmp unkownLoc
				push szRoute
				push dwPointer
				push dwAddress7
				push dwAddress6
				push byteAddress1
				push dwAddress5
				push dwAddress4
				push dwAddress3
				push dwAddress2
				push dwAddress1
				call FUNC_CTrain__CreateTrain
				add esp, 28h
			}
		}
		else
		{
			_asm
			{
				push szRoute
				push dwPointer
				push dwAddress7
				push dwAddress6
				push byteAddress1
				push dwAddress5
				push dwAddress4
				push dwAddress3
				push dwAddress2
				push dwAddress1
				call FUNC_CTrain__CreateTrain
				add esp, 28h
			}
		}
		// Todo: Get result (mov wHandle, al)
	}
	else if(trainRegisterId == 3)
	{
		char *szRoute = "common:/data/paths/TracksBronx.dat";
		dwPointer = dwTrainBronx1[0];

		dwAddress1 = dwTrainBronx1[1];
		dwAddress2 = dwTrainBronx1[2];
		dwAddress3 = dwTrainBronx1[3];
		dwAddress4 = dwTrainBronx1[4];
		dwAddress5 = dwTrainBronx1[5];
		dwAddress6 = dwTrainBronx1[7];
		dwAddress7 = dwTrainBronx1[8];

		byteAddress1 = (BYTE)dwTrainBronx1[6];
		unsigned int wHandle = NULL;

		// Check if our train already exists
		BYTE dwCheck = *(BYTE *)(CGame::GetBase() + 0x015BE4C4);
		if(dwCheck != NULL)
			return;

		// Create our train
		//NOTE: Assembler VS 2010 doesn't recognize jnz and jn... 
		WORD dwTemp;
		short unkownLoc = (CGame::GetBase() + 0x94A743);
		_asm
		{
			pushf
			pop ax
			and ax, 0x100
			mov [dwTemp], ax
			push ax
			popf
		}
		if(!dwTemp) 
		{
			_asm
			{
				jmp unkownLoc
				push szRoute
				push dwPointer
				push dwAddress7
				push dwAddress6
				push byteAddress1
				push dwAddress5
				push dwAddress4
				push dwAddress3
				push dwAddress2
				push dwAddress1
				call FUNC_CTrain__CreateTrain
				add esp, 28h
			}
		}
		else
		{
			_asm
			{
				push szRoute
				push dwPointer
				push dwAddress7
				push dwAddress6
				push byteAddress1
				push dwAddress5
				push dwAddress4
				push dwAddress3
				push dwAddress2
				push dwAddress1
				call FUNC_CTrain__CreateTrain
				add esp, 28h
			}
		}
		// Todo: Get result (mov wHandle, al)
	}
	else if(trainRegisterId == 4)
	{
		char *szRoute = "common:/data/paths/TracksBronx.dat";
		dwPointer = dwTrainBronx2[0];

		dwAddress1 = dwTrainBronx2[1];
		dwAddress2 = dwTrainBronx2[2];
		dwAddress3 = dwTrainBronx2[3];
		dwAddress4 = dwTrainBronx2[4];
		dwAddress5 = dwTrainBronx2[5];
		dwAddress6 = dwTrainBronx2[7];
		dwAddress7 = dwTrainBronx2[8];

		byteAddress1 = (BYTE)dwTrainBronx2[6];
		unsigned int wHandle = NULL;

		// Check if our train already exists
		BYTE dwCheck = *(BYTE*)(CGame::GetBase() + 0x015BE4C8);
		if(dwCheck != NULL)
			return;

		// Create our train
		//NOTE: Assembler VS 2010 doesn't recognize jnz and jn... 
		WORD dwTemp;
		short unkownLoc = (CGame::GetBase() + 0x94A743);
		_asm
		{
			pushf
			pop ax
			and ax, 0x100
			mov [dwTemp], ax
			push ax
			popf
		}
		if(!dwTemp) 
		{
			_asm
			{
				jmp unkownLoc
				push szRoute
				push dwPointer
				push dwAddress7
				push dwAddress6
				push byteAddress1
				push dwAddress5
				push dwAddress4
				push dwAddress3
				push dwAddress2
				push dwAddress1
				call FUNC_CTrain__CreateTrain
				add esp, 28h
			}
		}
		else
		{
			_asm
			{
				push szRoute
				push dwPointer
				push dwAddress7
				push dwAddress6
				push byteAddress1
				push dwAddress5
				push dwAddress4
				push dwAddress3
				push dwAddress2
				push dwAddress1
				call FUNC_CTrain__CreateTrain
				add esp, 28h
			}
		}
		// Todo: Get result (mov wHandle, al)
	}
} 
/* DEVELOPMENT NOTES

	if ( !trainQueens[0] )
	result = Func_CreateAutomaticTrains(
            "common:/data/paths/TracksQueens.dat",
            trainQueens,
            dword_15BE48C,
            &dword_15BD4D8,
            dword_15BD908,
            (int *)&unk_15BE4F0,
            (_BYTE *)dword_15BDD00,
            (int)&byte_15BD3E8,
            (int)dword_15BE0C8,
            (int)&unk_15BD940);
	if ( !trainQueens2 )
	result = Func_CreateAutomaticTrains(
				"common:/data/paths/TracksQueens2.dat",
				&trainQueens2,
				(int *)&unk_15BE490,
				(int *)&unk_15BD4DC,
				(int *)&unk_15BD90C,
				(int *)&unk_15BE630,
				&unk_15BDD50,
				(int)&unk_15BD3FC,
				(int)&unk_15BE118,
				(int)&unk_15BD990);

*/