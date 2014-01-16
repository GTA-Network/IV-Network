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

#ifndef CIVModelInfo_h
#define CIVModelInfo_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include <IV/IVData.h>

class IVBaseModelInfo
{
public:
	virtual DWORD ScalarDeletingDestructor() = 0;
	virtual DWORD F_m4() = 0;
	virtual DWORD F_m8() = 0;
	virtual byte __thiscall GetType() = 0;
	virtual DWORD F_m10() = 0;
	virtual DWORD F_m14() = 0;
	virtual DWORD F_m18() = 0;
	virtual DWORD F_m1C() = 0;
	virtual DWORD F_m20() = 0;
	virtual DWORD F_m24() = 0;
	virtual DWORD F_m28() = 0;
	virtual DWORD F_m2C() = 0;
	virtual DWORD F_m30() = 0;
	virtual DWORD F_m34() = 0;
	virtual DWORD F_m38() = 0;
	PAD(IVBaseModelInfo, pad0, 0x38);
	DWORD dwHash;
	PAD(IVBaseModelInfo, pad1, 0x4);
	DWORD dwRefCount;
	PAD(IVBaseModelInfo, pad2, 0xE);
	WORD wAnimIndex;
	PAD(IVBaseModelInfo, pad3, 0x14);
	DWORD dwVehicleType;
	PAD(IVBaseModelInfo, pad4, 0x52);
	BYTE byteTextureVariationCount;
};

class CIVModelInfo
{
private:
	int			m_iModelIndex;
	DWORD		m_dwReferenceCount;

public:
	CIVModelInfo();
	CIVModelInfo(int iModelIndex);
	~CIVModelInfo();

	IVBaseModelInfo		* GetModelInfo();

	void				SetIndex(int iModelIndex) { m_iModelIndex = iModelIndex; }
	int					GetIndex() { return m_iModelIndex; }

	BYTE				GetType();

	bool				IsBase() { return (GetType() == MODEL_TYPE_BASE); }
	bool				IsInstance() { return (GetType() == MODEL_TYPE_BASE); }
	bool				IsMlo() { return (GetType() == MODEL_TYPE_MLO); }
	bool				IsTime() { return (GetType() == MODEL_TYPE_TIME); }
	bool				IsWeapon() { return (GetType() == MODEL_TYPE_WEAPON); }
	bool				IsVehicle() { return (GetType() == MODEL_TYPE_VEHICLE); }
	bool				IsPed() { return (GetType() == MODEL_TYPE_PED); }
	bool				IsValid() { return (GetModelInfo() != NULL); }
	
	void				Load(bool bWaitForLoad = true);
	bool				IsLoaded();

	DWORD				GetHash();
	DWORD				GetReferenceCount();
	WORD				GetAnimIndex();

	void				AddReference(bool bWaitForLoad);
	void				RemoveReference();
};

#endif // CIVModelInfo_h