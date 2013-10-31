//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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
        float                           m_fSpawnAngle;
        bool                            m_bToggleControl;
        unsigned long					m_ulLastPureSyncTime;
        unsigned 						m_uiLastInterior;
        bool                            m_bDisableVehicleInfo;
        bool                            m_bFirstSpawn;
        bool                            m_bFinishedInitialize;
        unsigned short					m_uiPing;
        bool                            m_bRadarVisible;
		int								m_iRespawnTime[2];
		bool							m_bDead;
		bool							m_bAdvancedControlState;
		bool							m_bAdvancedCameraState;
		unsigned						m_pObj;


public:
										CLocalPlayer();
										~CLocalPlayer() { };

		friend class					CPlayerEntity;

        void							Respawn();
        void							Reset();
        void							Pulse();
        void							HandleSpawn();

        void							DoDeathCheck();

		bool							IsFullSyncNeeded();

        inline bool						GetFirstSpawn() { return m_bFirstSpawn; }
        void							SetRadarVisible(bool bVis) { m_bRadarVisible = bVis; }
        inline bool						IsRadarVisible() { return m_bRadarVisible; }

		void							SetControl(bool bControl) { m_bToggleControl = bControl; }
		inline bool						GetControl() { return m_bToggleControl; }
		void							SetPlayerControlAdvanced(bool bControl, bool bCamera, bool bForce = false);
		inline bool						GetAdvancedControlState() { return m_bAdvancedControlState; }
		inline bool						GetAdvancedCameraState() { return m_bAdvancedCameraState; }

		unsigned short					GetPing();
};

#endif // CLocalPlayer_h