//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CEntityManager.cpp
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#include "CEntityManager.h"

template<class T, EntityId max>
CEntityManager<T, max>::CEntityManager()
{
	// Set all entities invalid
	memset(&m_pEntities, 0, sizeof(m_pEntities));
}

template<class T, EntityId max>
CEntityManager<T, max>::~CEntityManager()
{
	// Loop through all entities
	for(EntityId id = 0; id < max; ++id)
	{
		// Check if ID exists
		if(DoesExists(id))
		{
			// we could call Delete() here, but there's no need to get this done in a clean way as we're about to be deleted
			delete m_pEntities[id];
		}
	}
}

template<class T, EntityId max>
T* CEntityManager<T, max>::GetAt(EntityId entityId)
{
	if(Exists(entityId))
		return m_pEntities[entityId];

	return 0;
}

template<class T, EntityId max>
bool CEntityManager<T, max>::Add(EntityId entityId, T* pEntity)
{
	// Check if the Entity didn't exist yet
	if(Exists(entityId))
	{
		// Delete it if it did
		Delete(entityId);
	}

	// save it
	m_pEntities[entityId] = pEntity;

	return true;
}

template<class T, EntityId max>
EntityId CEntityManager<T, max>::Add(T* pEntity)
{
	for(EntityId id = 0; id < max; ++id)
	{
		if(!Exists(id))
		{
			m_pEntities[id] = pEntity;
			return id;
		}
	}

	return INVALID_ENTITY_ID;
}

template<class T, EntityId max>
bool CEntityManager<T, max>::Delete(T* pEntity)
{
	for(EntityId id = 0; id < max; ++id)
	{
		// Check if ID exists
		if(Exists(id) && m_pEntities[id] == pEntity)
		{
			// we could call Delete() here, but there's no need to get this done in a clean way as we're about to be deleted
			delete m_pEntities[id];
			return true;
		}
	}
	return false;
}

template<class T, EntityId max>
bool CEntityManager<T, max>::Delete(EntityId entityId)
{
	// Check if the entity already existed
	if(!Exists(entityId))
		return false;

	// Delete the entity
	delete m_pEntities[entityId];

	// mark the slot as free
	m_pEntities[entityId] = 0;

	return true;
}

template<class T, EntityId max>
bool CEntityManager<T, max>::DoesExists(EntityId entityId)
{
	return Exists(entityId);
}

template<class T, EntityId max>
bool CEntityManager<T, max>::Exists(EntityId entityId)
{
	return (entityId < max && m_pEntities[entityId] != 0);
}

template<class T, EntityId max>
EntityId CEntityManager<T, max>::GetCount()
{
	EntityId count = 0;

	// Loop through all entities
	for(EntityId id = 0; id < max; ++id)
	{
		// Check if ID exists
		if(Exists(id))
		{
			// Increment the count
			count++;
		}
	}

	return count;
}

template<class T, EntityId max>
void CEntityManager<T, max>::Reset()
{
	// Loop through all entities
	for(EntityId id = 0; id < max; ++id)
	{
		// Check if ID exists
		if(DoesExists(id))
		{
			// we could call Delete() here, but there's no need to get this done in a clean way as we're about to be deleted
			delete m_pEntities[id];
		}
	}
}

template<class T, EntityId max>
EntityId CEntityManager<T, max>::GetMax()
{
	return max;
}

template<class T, EntityId max>
void CEntityManager<T, max>::Pulse()
{
	// Loop through all entities
	for(EntityId id = 0; id < max; ++id)
	{
		// Check if ID exists
		if(DoesExists(id))
		{
			m_pEntities[id]->Pulse();
		}
	}
}