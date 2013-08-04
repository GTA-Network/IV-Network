//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CCamera.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CCamera_h
#define CCamera_h

#include <Game/IVEngine/CIVCam.h>
#include <Common.h>

class IVCamera // (size = 0x140)
{
public:
	PAD(IVCamera, pad1, 0x140); // 0x0 - 0x140 (size = 0x140)
};

class IVCamPool // (size = 0x1C)
{
public:
	PAD(IVCamPool, pad1, 0x1C); // 0x0 - 0x1C (size = 0x1C)
};

class CCamera
{
private:
	unsigned int		m_uiGameCamIndex;
	unsigned int		m_uiScriptingIndex;
	bool				m_bUsingScriptingCam;	
	CIVCam				*m_pGameCam;
	CIVCam				*m_pScriptCam;

	CVector3			m_vecLookAtPosition; //Own look at pos for hook.
public:
	CCamera();
	~CCamera();

	void				SetCameraPosition(CVector3 &vecPosition);
	void				SetLookAtPosition(CVector3 &vecPosition);

	unsigned int		GetScriptingIndex() { return m_uiScriptingIndex; }

	void				GetCameraPosition(CVector3 &vecPosition);
	
	/*void				GetLookAtPosition(CVector3D &vecPosition);
	void				SetLookAtPositionEx(CVector3D &vecPosition); //For hook*/

	void				GetAimPosition(CVector3 *vecPosition);

	// Attach functions - TODO
	void				AttachToPed(unsigned int uiPed) {};
	void				AttachToVehicle(unsigned int uiVehicle) {};
	void				AttachToObject(unsigned int uiObject) {};
	void				Dettach() {};

	void				SetCamBehindPed(unsigned int uiPed);
};

#endif // CCamera_h