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

#ifndef CCamera_h
#define CCamera_h

#include <Game/IVEngine/CIVCam.h>
#include <Common.h>

class IVCamera { // (size = 0x140)
public:
	PAD(IVCamera, pad1, 0x140); // 0x0 - 0x140 (size = 0x140)
};

class IVCamPool { // (size = 0x1C)
public:
	PAD(IVCamPool, pad1, 0x1C); // 0x0 - 0x1C (size = 0x1C)
};

class CCamera {
private:
	unsigned int		m_uiGameCamIndex;
	unsigned int		m_uiScriptingIndex;
	bool				m_bUsingScriptingCam;	
	CIVCam				*m_pGameCam;
	CIVCam				*m_pScriptCam;
	CVector3			m_vecLookAtPosition; 

public:
	CCamera();
	~CCamera();

	void				SetCameraPosition(CVector3 &vecPosition);
	void				SetLookAtPosition(CVector3 &vecPosition);

	unsigned int		GetScriptingIndex() { return m_uiScriptingIndex; }

	void				GetCameraPosition(CVector3 &vecPosition);

	void				GetLookAt(CVector3& vecLookAt);
	
	/*void				GetLookAtPosition(CVector3D &vecPosition);
	void				SetLookAtPositionEx(CVector3D &vecPosition); //For hook*/

	void				GetAimPosition(CVector3 *vecPosition);

	void				AttachToPed(unsigned int uiPed) {};
	void				AttachToVehicle(unsigned int uiVehicle) {};
	void				AttachToObject(unsigned int uiObject) {};
	void				Dettach() {};

	bool				IsOnScreen(const CVector3& vecPosition);

	void				SetCamBehindPed(unsigned int uiPed);

	CIVCam				*GetGameCam() { return m_pGameCam; }
	CIVCam				*GetScriptCam() { return m_pScriptCam; }
};

#endif // CCamera_h