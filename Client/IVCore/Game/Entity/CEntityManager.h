//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CEntityManager.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CEntityManager_h
#define CEntityManager_h

#include <Common.h>

template<class T, EntityId max>
class CEntityManager {
private:
	T* m_pEntities[max];

public:
	CEntityManager()
	{
		// Set all entities invalid
		memset(&m_pEntities, 0, sizeof(m_pEntities));
	}
	~CEntityManager()
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

	inline T*			GetAt(EntityId entityId)
	{
		if(Exists(entityId))
			return m_pEntities[entityId];

		return 0;
	}

	inline bool		Add(EntityId entityId, T* pEntity)
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

	inline EntityId	Add(T* pEntity)
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

	inline bool		Delete(T* pEntity)
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

	inline bool		Delete(EntityId entityId)
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

	inline bool		DoesExists(EntityId entityId)
	{
		return Exists(entityId);
	}

	inline bool		Exists(EntityId entityId)
	{
		return (entityId < max && m_pEntities[entityId] != 0);
	}

	inline EntityId	FindFreeSlot()
	{
		for(EntityId i = 0; i < max; i++)
		{
			if(!DoesExists(i))
				return i;
		}

		return INVALID_ENTITY_ID;
	}

	inline EntityId	GetCount()
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

	inline void		Reset()
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

	inline EntityId	GetMax()
	{
		return max;
	}

	inline void		Pulse()
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

	inline void SetNull(EntityId id)
	{
		if (id < max)
			m_pEntities[id] = nullptr;
	}
};

#endif // CEntityManager_h