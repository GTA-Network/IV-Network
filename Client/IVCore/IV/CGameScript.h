
#ifndef CGameScript_h
#define CGameScript_h

#include "Common.h"

namespace EFLC
{

	enum eThreadState
	{
		ThreadStateIdle,
		ThreadStateRunning,
		ThreadStateKilled,
		ThreadState3,
		ThreadState4,                   // Sets opsToExecute to 1100000, and state to Idle in CallNative
	};

	struct scrThreadContext
	{
		unsigned int ThreadId;          // 00-04 m_nThreadId dd ?
		unsigned int ScriptHash;        // 04-08 m_dwScriptHash dd ?
		eThreadState State;     // 08-0C m_eThreadState dd ?
		unsigned int IP;                        // 0C-10 m_nIP       dd ?
		unsigned int FrameSP;           // 10-14 m_nFrameSP  dd ?
		unsigned int SP;                        // 14-18 m_nSP       dd ?
		unsigned int TimerA;            // 18-1C m_nTimerA   dd ?
		unsigned int TimerB;            // 1C-20 m_nTimerB   dd ?
		unsigned int TimerC;            // 20-24 m_nTimerC   dd ?
		float WaitTime;                         // 24-28 m_fWaitTime dd ?
		unsigned int _f28;                      // 28-2C field_28    dd ?
		unsigned int _f2C;                      // 2C-30 field_2C    dd ?
		unsigned int _f30;                      // 30-34 field_30    dd ?
		unsigned int _f34;                      // 34-38 field_34    dd ?
		unsigned int _f38;                      // 38-3C field_38    dd ?
		unsigned int _f3C;                      // 3C-40 field_3C    dd ?
		unsigned int _f40;                      // 40-44 field_40    dd ?
		unsigned int ExIP;                      // 44-48 ExIP        dd ?
		unsigned int ExFrameSP;         // 48-4C ExFrameSP   dd ?
		unsigned int ExSP;                      // 4C-50 ExSP        dd ?
		unsigned int _f50;                      // 50-54 field_50    dd ?
	};

	class scrThread
	{
	public:
		virtual ~scrThread() { }
		virtual eThreadState Reset(unsigned int scriptHash, void* pArgs, unsigned int argCount) = 0;
		virtual eThreadState Run(unsigned int opsToExecute) = 0;
		virtual eThreadState Tick(unsigned int opsToExecute) = 0;
		virtual void Kill() = 0;

		scrThreadContext m_Context;             // 04-58 m_Context   scrThreadContext ?
		void * m_pStack;                                        // 58-5C m_pStack    dd ?
		unsigned int _f5C;                              // 5C-60 field_5C    dd ?
		void * m_pXLiveBuffer;                          // 60-64 m_pXLiveBuffer dd ?
		unsigned int _f64;                              // 64-68 field_64    dd ?
		void* _f68;                              // 68-6C field_68    dd ?
		char *m_pszExitMessage;                 // 6C-70 m_pszExitMessage dd ?
	};

	class GtaThread : public scrThread
	{
	public:
		char m_szProgramName[24];                                       // 70-88 m_szProgramName db 24 dup(?)
		unsigned int _f88;                                                      // 88-8C field_88    dd ?
		unsigned int _f8C;                                                      // 8C-90 field_8C    dd ?
		unsigned int _f90;                                                      // 90-94 field_90    dd ?
		bool _f94;                                                                      // 94-95 field_94    db ?
		bool _f95;                                                                      // 95-96 --- db ?                                                                       // Check IDA
		bool m_bThisScriptShouldBeSaved;                        // 96-97 m_bThisScriptShouldBeSaved db ?
		bool m_bPlayerControlOnInMissionCleanup;        // 97-98 m_bPlayerControlOnInMissionCleanup db ?
		bool m_bClearHelpInMissionCleanup;                      // 98-99 m_bClearHelpInMissionCleanup db ?
		bool _f99;                                                                      // 99-9A field_99    db ?
		bool m_bAllowNonMinigameTextMessages;           // 9A-9B m_bAllowNonMinigameTextMessages db ?
		bool _f9B;                                                                      // 9B-9C field_9B    db ?
		bool _f9C;                                                                      // 9C-9D --- db ?                                                                       // Check IDA
		bool m_bCanBePaused;                                            // 9D-9E m_bCanBePaused db ?
		BYTE _f9E;                                                                      // 9E-9F field_9E    db ?
		bool _f9F;                                                                      // 9F-A0 field_9F    db ?
		BYTE poolHandle;                                                                      // A0-A4 field_A0    dd ?
		bool m_bCanRemoveBlipsCreatedByAnyScript;       // A4-A5 m_bCanRemoveBlipsCreatedByAnyScript db ?
		bool _fA5;                                                                      // A5-A6             db ? ; undefined
		bool _fA6;                                                                      // A6-A7             db ? ; undefined
		bool _fA7;                                                                      // A7-A8             db ? ; undefined
		unsigned int _fA8;                                                      // A8-AC field_A8    dd ?
		unsigned int m_nFlags;                                          // AC-B0 m_nFlags    dd ?

		GtaThread();
		virtual ~GtaThread();

		virtual eThreadState Reset(unsigned int scriptHash, void* pArgs, unsigned int argCount);
		virtual eThreadState Run(unsigned int opsToExecute);
		virtual eThreadState Tick(unsigned int opsToExecute);
		virtual void Kill();
	};

	void AddScriptToThreadCollection(GtaThread * pThread);

};

#endif // CGameScript_h