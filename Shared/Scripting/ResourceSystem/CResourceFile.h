//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CResourceFile.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

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

	virtual bool				Start() = 0;
	virtual bool				Stop() = 0;
};

#endif // CResourceFile_h