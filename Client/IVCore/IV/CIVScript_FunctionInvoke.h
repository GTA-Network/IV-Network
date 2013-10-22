//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVScript_FunctionInvoke.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: Contains zlib licensed code from ScriptHook by aru
//
//==============================================================================

#ifndef CIVScript_FunctionInvoke_h
#define CIVScript_FunctionInvoke_h

#include <Common.h>
#include "CIVScript_FunctionContext.h"

#ifdef _CLIENT
#include <CCore.h>
#include <CLogFile.h>
#endif

// Log native calls(detect crash scripting functions)
//#define NATIVE_LOG 1

class CIVScript_NativeInvoke
{
#ifndef _CLIENT
public:
	static void				InitialiseOffset(DWORD dwOffset2) { dwInvokeOffset = dwOffset2; }
#endif
private:
#ifndef _CLIENT
	DWORD			dwInvokeOffset;
#endif

	typedef void (_cdecl * NativeCall)(IVNativeCallContext * pNativeContext);

	static inline void Invoke(unsigned int uiHash, NativeContext * pNativeContext)
	{
		NativeCall ncNativeCall = NULL;
		_asm
		{
			pushad
			mov esi, uiHash
#ifdef _CLIENT
			call COffsets::FUNC_ScrVM__FindNativeAddress
#else
			call dwInvokeOffset;
#endif
			mov ncNativeCall, eax
			popad
		}

		if (ncNativeCall != NULL)
			ncNativeCall(pNativeContext);
		else
		{
#ifdef _CLIENT
			CLogFile::PrintDebugf("Failed to find native address of hash 0x%p", uiHash);
#endif
		}
		#ifdef NATIVE_LOG
				CLogFile::PrintDebugf("Finished invoke native %x/%p",uiHash,uiHash);
				CLogFile::PrintDebugf(" ");
		#endif
	}

public:
	template <typename R>
	static inline R Invoke(unsigned int hash)
	{
		NativeContext cxt;
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1>
	static inline R Invoke(unsigned int hash, T1 p1)
	{
		NativeContext cxt;
		cxt.Push(p1);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d",p1);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2>
	static inline R Invoke(unsigned int hash, T1 p1, T2 p2)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d",p1,p2);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3>
	static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d",p1,p2,p3);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4>
	static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d",p1,p2,p3,p4);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d",p1,p2,p3,p4,p5);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
		cxt.Push(p6);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d,%d",p1,p2,p3,p4,p5,p6);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
		cxt.Push(p6);
		cxt.Push(p7);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d,%d,%d",p1,p2,p3,p4,p5,p6,p7);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
		cxt.Push(p6);
		cxt.Push(p7);
		cxt.Push(p8);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d,%d,%d,%d",p1,p2,p3,p4,p5,p6,p7,p8);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
		cxt.Push(p6);
		cxt.Push(p7);
		cxt.Push(p8);
		cxt.Push(p9);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d,%d,%d,%d,%d",p1,p2,p3,p4,p5,p6,p7,p8,p9);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
		cxt.Push(p6);
		cxt.Push(p7);
		cxt.Push(p8);
		cxt.Push(p9);
		cxt.Push(p10);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d",p1,p2,p3,p4,p5,p6,p7,p8,p9,p10);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
		cxt.Push(p6);
		cxt.Push(p7);
		cxt.Push(p8);
		cxt.Push(p9);
		cxt.Push(p10);
		cxt.Push(p11);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11, typename T12>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11, T12 p12)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
		cxt.Push(p6);
		cxt.Push(p7);
		cxt.Push(p8);
		cxt.Push(p9);
		cxt.Push(p10);
		cxt.Push(p11);
		cxt.Push(p12);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11, typename T12, typename T13>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11, T12 p12, T13 p13)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
		cxt.Push(p6);
		cxt.Push(p7);
		cxt.Push(p8);
		cxt.Push(p9);
		cxt.Push(p10);
		cxt.Push(p11);
		cxt.Push(p12);
		cxt.Push(p13);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11, typename T12, typename T13, typename T14>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
		cxt.Push(p6);
		cxt.Push(p7);
		cxt.Push(p8);
		cxt.Push(p9);
		cxt.Push(p10);
		cxt.Push(p11);
		cxt.Push(p12);
		cxt.Push(p13);
		cxt.Push(p14);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11, typename T12, typename T13, typename T14,
		typename T15>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
		cxt.Push(p6);
		cxt.Push(p7);
		cxt.Push(p8);
		cxt.Push(p9);
		cxt.Push(p10);
		cxt.Push(p11);
		cxt.Push(p12);
		cxt.Push(p13);
		cxt.Push(p14);
		cxt.Push(p15);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}


	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11, typename T12, typename T13, typename T14,
		typename T15, typename T16>
		static inline R Invoke(unsigned int hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16)
	{
		NativeContext cxt;
		cxt.Push(p1);
		cxt.Push(p2);
		cxt.Push(p3);
		cxt.Push(p4);
		cxt.Push(p5);
		cxt.Push(p6);
		cxt.Push(p7);
		cxt.Push(p8);
		cxt.Push(p9);
		cxt.Push(p10);
		cxt.Push(p11);
		cxt.Push(p12);
		cxt.Push(p13);
		cxt.Push(p14);
		cxt.Push(p15);
		cxt.Push(p16);
#ifdef NATIVE_LOG
		CLogFile::PrintDebugf("");
		CLogFile::PrintDebugf("Start invoking native hash %x/%p",hash,hash);
		//CLogFile::PrintDebugf("Params: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16);
#endif
		Invoke(hash, &cxt);
		return cxt.GetResult<R>();
	}
};

#endif // CIVScript_FunctionInvoke_h