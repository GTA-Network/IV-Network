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

#ifndef IVCommon_h
#define IVCommon_h

#include <Common.h>
#include <Math\CMaths.h>

template <typename T>
struct CSimpleCollection {
	T           ** pData;
	unsigned short usCount;
	unsigned short usSize;
};

// For gta structures
class Vector3 {
public:
	float fX;
	float fY;
	float fZ;

	Vector3()
	{
		fX = fY = fZ = 0.0f;
	}

	void ToVector3(CVector3 &vec3) const
	{
		vec3.fX = fX;
		vec3.fY = fY;
		vec3.fZ = fZ;
	}

	void FromVector3(const CVector3 &vec3)
	{
		fX = vec3.fX;
		fY = vec3.fY;
		fZ = vec3.fZ;
	}
};

// For gta structures
class Vector3_Pad {
public:
	float fX;
	float fY;
	float fZ;
	float f4;

	Vector3_Pad()
	{
		fX = fY = fZ = f4 = 0.0f;
	}

	void ToVector3(CVector3 &vec3) const
	{
		vec3.fX = fX;
		vec3.fY = fY;
		vec3.fZ = fZ;
	}

	void FromVector3(const CVector3 &vec3)
	{
		fX = vec3.fX;
		fY = vec3.fY;
		fZ = vec3.fZ;
	}
};

// For gta structures
class Matrix34 {
public:
	Vector3_Pad vecRight;    // 00-10
	Vector3_Pad vecForward;  // 10-20
	Vector3_Pad vecUp;       // 20-30
	Vector3_Pad vecPosition; // 30-40

	Matrix34()
	{
		memset(this, 0, sizeof(Matrix34));
	}

	void ToMatrix(Matrix * matMatrix) const
	{
		memcpy(&matMatrix->vecRight, &vecRight, sizeof(CVector3));
		memcpy(&matMatrix->vecForward, &vecForward, sizeof(CVector3));
		memcpy(&matMatrix->vecUp, &vecUp, sizeof(CVector3));
		memcpy(&matMatrix->vecPosition, &vecPosition, sizeof(CVector3));
	}

	void FromMatrix(Matrix * matMatrix)
	{
		memcpy(&vecRight, &matMatrix->vecRight, sizeof(CVector3));
		memcpy(&vecForward, &matMatrix->vecForward, sizeof(CVector3));
		memcpy(&vecUp, &matMatrix->vecUp, sizeof(CVector3));
		memcpy(&vecPosition, &matMatrix->vecPosition, sizeof(CVector3));
	}
};

#endif // IVCommon_h