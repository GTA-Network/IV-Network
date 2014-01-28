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

		void	CheckVehicleEnterExit();
		void	ProcessVehicleEnterExit();
};

#endif // CLocalPlayer_h