//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
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
	Matrix34 m_matMatrix;
	CVector3 m_vecUnknown;
	float m_fUnknown;
	float m_fFOV;
	float m_fNear;
	float m_fFar;
	float m_fNearDOF;
	float m_fFarDOF;
	float m_fMotionBlur;
	float m_fUnknown2;
	float m_fUnknown3;
	BYTE m_byteUnknown;
	PAD(IVCamData, pad0, 0x3);
};

class IVCam
{
public:
	PAD(IVCam, pad0, 0x10);
	IVCamData m_CamData1;
	PAD(IVCam, pad1, 0xC);
	IVCamData m_CamData2;
	PAD(IVCam, pad2, 0x3C);
};

class CIVCam
{

private:

	IVCam				* m_pCam;

public:

	CIVCam( );
	CIVCam( IVCam * pCam );
	~CIVCam( );

	void				SetCam( IVCam * pCam ) { m_pCam = pCam; }
	IVCam				* GetCam( ) { return m_pCam; }

};

#endif // CIVCam_h