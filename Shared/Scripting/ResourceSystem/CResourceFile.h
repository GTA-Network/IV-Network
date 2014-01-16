/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CResourceFile_h
#define CResourceFile_h

#include <Common.h>

class CResource;

class CResourceFile {
public:
	enum eResourceType
	{
		RESOURCE_FILE_TYPE_MAP,
		RESOURCE_FILE_TYPE_SERVER_SCRIPT,
		RESOURCE_FILE_TYPE_CLIENT_SCRIPT,
		RESOURCE_FILE_TYPE_CONFIG,
		RESOURCE_FILE_TYPE_CLIENT_CONFIG,
		RESOURCE_FILE_TYPE_HTML,
		RESOURCE_FILE_TYPE_CLIENT_FILE,
		RESOURCE_FILE_TYPE_NONE,
	};
protected:
	class CResource *			m_resource;
	CString						m_strResourceFileName;  // full path
	CString						m_strShortName;         // just the filename
	CString						m_strWindowsName;       // the name with backwards slashes
	eResourceType				m_type;
public:
	CResourceFile(CResource * resource, const char * szShortName, const char * szResourceFileName);
	~CResourceFile();

	inline eResourceType		GetType() { return m_type; }
	inline const char *			GetName() { return m_strShortName.Get(); }
	CString						GetFileName() { return m_strResourceFileName; }

	virtual bool				Start() = 0;
	virtual bool				Stop() = 0;
};

#endif // CResourceFile_h