//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CEntityManager.h
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CEntityManager_h
#define CEntityManager_h

#include <Common.h>

template<class T, EntityId max>
class CEntityManager
{
private:
	T* m_pEntities[max];

public:
	CEntityManager();
	~CEntityManager();

	T*			GetAt(EntityId entityId);
	bool		Add(EntityId entityId, T* pEntity);
	EntityId	Add(T* pEntity);
	bool		Delete(T* pEntity);
	bool		Delete(EntityId entityId);
	bool		DoesExists(EntityId entityId);
	bool		Exists(EntityId entityId);
	EntityId	GetCount();
	void		Reset();
	EntityId	GetMax();
	void		Pulse();
};

#endif // CEntityManager_h