//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CResourceManager.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CResourceManager_h
#define CResourceManager_h

#include "CResource.h"

class CResourceManager {
public:
	enum eResourceQueueType
	{
		QUEUE_STOP,
		QUEUE_RESTART,
		QUEUE_UNLOAD
	};

	struct sResourceQueue
	{
		CResource* pResource;
		eResourceQueueType eType;
	};

private:
	CString						m_strResourceDirectory;
	std::list<CResource*>		m_pResources;
	std::list<sResourceQueue>	m_pResourceQueue;

public:
	CResourceManager();
	CResourceManager(CString strResourceDirectory);
	~CResourceManager();

	CResource*	Get(CString name);
	CResource*	Get(SQVM* pVM);

	bool		Load(CString strName, bool bStart = true);
	bool		Start(CResource* pResource);
	bool		Stop(CResource* pResource);
	bool		Restart(CResource* pResource);

	void		Process(unsigned long ulTime);
};

#endif // CResourceManager_h