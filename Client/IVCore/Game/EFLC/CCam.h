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

#ifndef CCam_h
#define CCam_h

#include <Common.h>
#include "../GameCommon.h"

_GAME_BEGIN

class ICamData
{
public:
        Matrix34 m_matMatrix;      // 00-40
        CVector3 m_vecUnknown;     // 40-4C
        float    m_fUnknown;       // 4C-50
        float    m_fFOV;           // 50-54
        float    m_fNear;          // 54-58
        float    m_fFar;           // 58-5C
        float    m_fNearDOF;       // 5C-60
        float    m_fFarDOF;        // 60-64
        float    m_fMotionBlur;    // 64-68
        float    m_fUnknown2;      // 68-6C
        float    m_fUnknown3;      // 6C-70
        BYTE     m_byteUnknown;    // 70-71
        PAD(IVCamData, pad0, 0x3); // 71-74
};

class ICam
{
public:
        PAD(IVCam, pad0, 0x10); // 000-010
        ICamData m_data1;      // 010-084
        PAD(IVCam, pad1, 0xC);  // 084-090
        ICamData m_data2;      // 090-104
		PAD(IVCam, pad2, 0xC);  // 104-110
		ICamData m_data3;      // 110-124
        PAD(IVCam, pad3, 0x10); // 124-140
};

class CCam
{
private:
        ICam * m_pCam;

public:
        CCam();
        CCam(ICam * pCam);
        ~CCam();

        void    SetCam(ICam * pCam) { m_pCam = pCam; }
        ICam * GetCam() { return m_pCam; }

        void    SetPosition(const CVector3& vecPosition);
        void    GetPosition(CVector3& vecPosition);
};

_GAME_END

#endif // CCam_h
