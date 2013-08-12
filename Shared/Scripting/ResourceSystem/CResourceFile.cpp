//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CResourceFile.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CResourceFile.h"


CResourceFile::CResourceFile(CResource * resource, const char * szShortName, const char * szResourceFileName)
{
	m_strResourceFileName = szResourceFileName; 

	m_strShortName = szShortName;
	for(size_t i = 0; i < m_strShortName.GetLength(); i++)
	{
		if(m_strShortName[i] == '\\')
		{
			m_strShortName.SetChar(i, '/');
		}
	}

	m_strWindowsName = m_strShortName;

	m_resource = resource;
}

CResourceFile::~CResourceFile()
{

}