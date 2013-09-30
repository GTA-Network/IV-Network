//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: IVCommon.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

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