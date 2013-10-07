//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CLibrary.cpp
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CLibrary.h"
#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#include <stdio.h>
#endif

CLibrary::CLibrary() :
	m_pLibrary(NULL)
{
}

CLibrary::~CLibrary()
{
	if(m_pLibrary)
		Unload();
}

bool CLibrary::Load(const char * szPath)
{
	if(!m_pLibrary)
	{
#ifdef WIN32
		m_pLibrary = LoadLibrary(szPath);
#else
		m_pLibrary = dlopen(szPath, RTLD_LAZY);
#endif


		if(!m_pLibrary)
		{
                      char * szErrorMessage = NULL;
#ifdef WIN32
                        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, 
                                GetLastError(), 0, (char *)&szErrorMessage, 0, NULL);
                        szErrorMessage[strlen(szErrorMessage) - 3] = '\0';
#else
                        szErrorMessage = dlerror();
#endif
                        char * szName = (char *)szPath;


                        for(size_t i = strlen(szPath); i > 0; --i)
                        {
#ifdef WIN32
                                if(szPath[i] == '\\')
#else
                                if(szPath[i] == '/')
#endif
                                {
                                        szName = (char *)(szPath + (i + 1));
                                        break;
                                }
                        }

			printf("error: %s\n", szErrorMessage);
#ifdef WIN32
                        LocalFree(szErrorMessage);
#endif
			return false;
		}

		return true;
	}

	return false;
}

bool CLibrary::Unload()
{
	if(m_pLibrary)
	{
#ifdef WIN32
		FreeLibrary((HMODULE)m_pLibrary);
#else
		dlclose(m_pLibrary);
#endif
		m_pLibrary = NULL;
		return true;
	}

	return false;
}

void * CLibrary::GetProcedureAddress(const char * szProcedureName)
{
	if(m_pLibrary)
	{
		void * pProcedureAddress = NULL;
#ifdef WIN32
		pProcedureAddress = (void *)GetProcAddress((HMODULE)m_pLibrary, szProcedureName);
#else
		pProcedureAddress = dlsym(m_pLibrary, szProcedureName);
#endif
		return pProcedureAddress;
	}

	return NULL;
}

void * CLibrary::GetProcedureAddress(unsigned int uiOrdinal)
{
	// TODO FOR MULTIPLATFORM
	return NULL;
}
