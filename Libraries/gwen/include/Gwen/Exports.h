/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once

#if defined(GWEN_COMPILE_DLL)

	#ifdef __GNUC__
		#define GWEN_EXPORT __attribute__((dllexport))
	#else
		#define GWEN_EXPORT __declspec(dllexport)
	#endif

#elif defined(GWEN_COMPILE_STATIC)

	#define GWEN_EXPORT

#else 

	// GWEN_DLL means that the project that's including us wants
	// to use GWEN as a DLL (or library)
	#ifdef GWEN_DLL

		#ifdef __GNUC__
			#define GWEN_EXPORT __attribute__((dllimport))
		#else
			#define GWEN_EXPORT __declspec(dllimport)
		#endif

		#ifdef _MSC_VER
			#ifndef _DEBUG
				#pragma comment ( lib, "gwen.lib" )
			#else
				#pragma comment ( lib, "gwend.lib" )
			#endif
		#endif

	#else

		#define GWEN_EXPORT

		#ifdef _MSC_VER
			#ifndef _DEBUG
				#pragma comment ( lib, "gwen_static.lib" )
			#else
				#pragma comment ( lib, "gwend_static.lib" )
			#endif
		#endif

	#endif

#endif

#ifdef _MSC_VER

	#define GWEN_FINLINE __forceinline
	#define GWEN_PURE_INTERFACE __declspec(novtable)

#elif defined(__GNUC__)

	#define GWEN_FINLINE __attribute__((always_inline)) inline
	#define GWEN_PUREINTERFACE 

#else

	#define GWEN_FINLINE inline
	#define GWEN_PUREINTERFACE 

#endif