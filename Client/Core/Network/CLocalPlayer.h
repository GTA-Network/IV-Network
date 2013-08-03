//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CLocalPlayer.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CLocalPlayer_h
#define CLocalPlayer_h

#include <winsock2.h>
#include <windows.h>
#include <Game\Entity\CPlayerEntity.h>

class CLocalPlayer : public CPlayerEntity
{
private:
        bool                            m_bIsDead;
        CVector3                        m_vecSpawnPosition;
        float                           m_fSpawnAngle;
        bool                            m_bToggleControl;
        unsigned long					m_ulLastPureSyncTime;
        unsigned int					m_uiLastInterior;
        bool                            m_bDisableVehicleInfo;
        bool                            m_bFirstSpawn;
        bool                            m_bSpawnMarked;
        bool                            m_bFinishedInitialize;
        unsigned short					m_uiPing;
        bool                            m_bRadarVisible;

public:
        CLocalPlayer();
        ~CLocalPlayer();

        void			Respawn();
        void			HandleSpawn();
		bool			IsDead();
        void			DoDeathCheck();
        void			Pulse();
        void			SetSpawnLocation(CVector3 vecPosition, float fHeading);
        void			SetPlayerControlAdvanced(bool bControl, bool bCamera);
        void			SendOnFootSync();
        void			SendInVehicleSync();
        void			SendPassengerSync();
        void			SendSmallSync();
        bool			IsPureSyncNeeded();
        bool			IsSmallSyncNeeded();
        unsigned short	GetPing();
        void			GetSpawnPosition(CVector3 * vecPosition) { memcpy(vecPosition, &m_vecSpawnPosition, sizeof(CVector3)); }
        float			GetSpawnRotation() { return m_fSpawnAngle; }
        void            SetControl(bool control);
        bool            GetControl();
        bool            GetFirstSpawn() { return m_bFirstSpawn; }
        void            SetRadarVisible(bool bVis) { m_bRadarVisible = bVis; }
        bool            IsRadarVisible() { return m_bRadarVisible; }

        void            Reset();
};

#endif // CLocalPlayer_h