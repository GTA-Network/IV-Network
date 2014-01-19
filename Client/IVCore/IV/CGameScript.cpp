#include "CGameScript.h"
#include "../Game/CGameFuncs.h"
#include <CCore.h>

extern CCore * g_pCore;

#define GetScriptName (*(char* (__thiscall *)(GtaThread *)) ((g_pCore->GetBase() + 0x4CF650)))
#define sub_7D50B0 (*(bool (*)()) ((g_pCore->GetBase() + 0x7D50B0)))
#define sub_C2B530 (*(void (__thiscall *)(GtaThread *)) ((g_pCore->GetBase() + 0xC2B530)))
#define sub_4CE060 (*(eThreadState (__thiscall *)(GtaThread *, unsigned int)) ((g_pCore->GetBase() + 0x4CE060)))
#define dword_10A53B0 *(DWORD *) ((g_pCore->GetBase() + 0x10A53B0))
#define dword_105A014 *(DWORD *) ((g_pCore->GetBase() + 0x105A014))
#define dword_10B415C *(DWORD *) ((g_pCore->GetBase() + 0x10B415C))
#define byte_10B418C *(BYTE *) ((g_pCore->GetBase() + 0x10B418C))

#define GtaThread__Kill (*(void(__thiscall*)(GtaThread*))(((g_pCore->GetBase() + 0xC2B900))))

namespace EFLC
{

	GtaThread::GtaThread()
	{
		m_pStack = 0;
		_f5C = 0;

		m_pXLiveBuffer = 0;
		_f64 = 0;
		_f68 = 0;
		m_pszExitMessage = "Normal exit.";

		_f68 = CGameFunction::Alloc(8192);

		memset(&m_Context, 0, 0x54u);
		m_Context._f28 = -1;
		m_Context._f2C = -1;
		m_Context._f50 = -1;
		m_Context.State = ThreadStateIdle;
		m_Context._f40 = 0;

		m_nFlags &= 0xFFFFFFFC;
		m_szProgramName[0] = 0;
		_f88 = 0;
		_f8C = 0;
		_f90 = 0;
		_f94 = 0;
		_f95 = 0;
		m_bThisScriptShouldBeSaved = 0;
		m_bPlayerControlOnInMissionCleanup = 1;
		m_bClearHelpInMissionCleanup = 1;
		_f99 = 0;
		m_bAllowNonMinigameTextMessages = 0;
		_f9B = 0;
		_f9C = 0;
		m_bCanBePaused = 1;
		_f9E = -1;
		poolHandle = 0;
		_fA7 = 0;

		_fA8 = 0;
	}

	GtaThread::~GtaThread()
	{
		//TODO...
	}

	eThreadState GtaThread::Reset(unsigned int scriptHash, void* pArgs, unsigned int argCount)
	{
		m_Context.IP = 0;
		m_Context.SP = 0;
		m_Context.FrameSP = 0;
		m_Context.TimerA = 0;
		m_Context.TimerB = 0;
		m_Context.TimerC = 0;
		m_Context.ExIP = 0;
		m_Context.ExFrameSP = 0;
		m_Context.ExSP = 0;
		m_Context._f50 = 0;
		m_Context.State = ThreadStateIdle;
		m_Context.ScriptHash = scriptHash;
		m_pszExitMessage = "Normal exit";
		m_bCanBePaused = 1;

		return m_Context.State;
	}


	eThreadState GtaThread::Run(unsigned int opsToExecute)
	{
		return eThreadState::ThreadStateRunning;
	}


	eThreadState GtaThread::Tick(unsigned int opsToExecute)
	{
		memcpy(m_szProgramName, GetScriptName(this), 24); //Get name by m_Context.ScriptHash, if not found return with "ERROR!!! Unknown script name ERROR!!!"
		m_szProgramName[23] = '\0';

		if (_f9C != 0 || sub_7D50B0())
		{
			return m_Context.State;
		}
		else
		{
			sub_C2B530(this);
			dword_10A53B0 = *(DWORD *)(dword_105A014 + 1344);
			dword_10B415C = 0;
			byte_10B418C = 0;
			return sub_4CE060(this, opsToExecute); //increase timer and call NativeThread::Run
		}
	}


	void GtaThread::Kill()
	{
		GtaThread__Kill(this);
		m_Context.State = ThreadStateKilled;
		m_Context.ThreadId = 0;
	}

#define ThreadCount *(DWORD*) ((g_pCore->GetBase()  + 0x16EAD4C))
#define ThreadPool (CSimpleCollection<scrThread> *) ((g_pCore->GetBase() + 0x186595C))

	void AddScriptToThreadCollection(GtaThread * pThread)
	{
		static CSimpleCollection<scrThread> * ThreadCollection = ThreadPool;
		if (ThreadCollection && ThreadCollection->pData)
		{
			int threadId = 0;
			while (ThreadCollection->pData[threadId]->m_Context.ThreadId)   // Get free id
			{
				++threadId;
				if (threadId >= ThreadCollection->usCount)
					return;
			}

			++ThreadCount;
			pThread->m_Context.ThreadId = ThreadCount;
			ThreadCollection->pData[threadId] = pThread;
			pThread->m_Context.State = ThreadStateRunning;
		}
	}
};