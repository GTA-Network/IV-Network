//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CLocalPlayer.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CLocalPlayer_h
#define CLocalPlayer_h

#include <Common.h>

#include "Game/Entity/CPlayerEntity.h"
#include "Game/Entity/CNetworkEntity.h"

class CLocalPlayer : public CPlayerEntity {
private:
        bool                            m_bIsDead;
        CVector3                        m_vecSpawnPosition;
        float                           m_fSpawnAngle;
        bool                            m_bToggleControl;
        unsigned long					m_ulLastPureSyncTime;
        unsigned 						m_uiLastInterior;
        bool                            m_bDisableVehicleInfo;
        bool                            m_bFirstSpawn;
        bool                            m_bSpawnMarked;
        bool                            m_bFinishedInitialize;
        unsigned short					m_uiPing;
        bool                            m_bRadarVisible;

public:
										CLocalPlayer();
										~CLocalPlayer() { };

        virtual void					Respawn();
        virtual void					Reset();
        virtual void					Pulse();
        virtual void					HandleSpawn();

		bool							IsDead();
        void							DoDeathCheck();

        virtual void					SetSpawnLocation(CVector3 vecPosition, float fHeading);
        void							GetSpawnPosition(CVector3 * vecPosition) { memcpy(vecPosition, &m_vecSpawnPosition, sizeof(CVector3)); }
        float							GetSpawnRotation() { return m_fSpawnAngle; }

        bool							GetFirstSpawn() { return m_bFirstSpawn; }
        void							SetRadarVisible(bool bVis) { m_bRadarVisible = bVis; }
        bool							IsRadarVisible() { return m_bRadarVisible; }

		virtual void					SetControl(bool bControl) { m_bToggleControl = bControl; }
		virtual bool					GetControl() { return m_bToggleControl; }
		virtual void					SetPlayerControlAdvanced(bool bControl, bool bCamera);

		unsigned short					GetPing();
};

#endif // CLocalPlayer_h