//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVCam.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVCam_h
#define CIVCam_h

#include <Common.h>
#include <Math\CMaths.h>
#include <IV\IVCommon.h>

class IVCamData
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

class IVCam
{
public:
        PAD(IVCam, pad0, 0x10); // 000-010
        IVCamData m_data1;      // 010-084
        PAD(IVCam, pad1, 0xC);  // 084-090
        IVCamData m_data2;      // 090-104
		PAD(IVCam, pad2, 0xC);  // 104-110
		IVCamData m_data3;      // 110-124
        PAD(IVCam, pad3, 0x10); // 124-140
};

class CIVCam
{
private:
        IVCam * m_pCam;

public:
        CIVCam();
        CIVCam(IVCam * pCam);
        ~CIVCam();

        void    SetCam(IVCam * pCam) { m_pCam = pCam; }
        IVCam * GetCam() { return m_pCam; }

        void    SetPosition(const CVector3& vecPosition);
        void    GetPosition(CVector3& vecPosition);
};


#endif // CIVCam_h