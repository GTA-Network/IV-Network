//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CVector3.h
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#pragma once

class CVector3
{
public:
        float fX;
        float fY;
        float fZ;

        CVector3()
        {
                fX = fY = fZ = 0.0f;
        }

        CVector3(float _fX, float _fY, float _fZ)
        {
                fX = _fX; fY = _fY; fZ = _fZ;
        }

        bool IsEmpty() const
        {
                return (fX == 0 && fY == 0 && fZ == 0);
        }

        float Length() const
        {
                return sqrt((fX * fX) + (fY * fY) + (fZ * fZ));
        }

        CVector3 operator+ (const CVector3& vecRight) const
        {
                return CVector3(fX + vecRight.fX, fY + vecRight.fY, fZ + vecRight.fZ);
        }

        CVector3 operator+ (float fRight) const
        {
                return CVector3(fX + fRight, fY + fRight, fZ + fRight);
        }

        CVector3 operator- (const CVector3& vecRight) const
        {
                return CVector3(fX - vecRight.fX, fY - vecRight.fY, fZ - vecRight.fZ);
        }

        CVector3 operator- (float fRight) const
        {
                return CVector3(fX - fRight, fY - fRight, fZ - fRight);
        }

        CVector3 operator* (const CVector3& vecRight) const
        {
                return CVector3(fX * vecRight.fX, fY * vecRight.fY, fZ * vecRight.fZ);
        }

        CVector3 operator* (float fRight) const
        {
                return CVector3(fX * fRight, fY * fRight, fZ * fRight);
        }

        CVector3 operator/ (const CVector3& vecRight) const
        {
                return CVector3(fX / vecRight.fX, fY / vecRight.fY, fZ / vecRight.fZ);
        }

        CVector3 operator/ (float fRight) const
        {
                return CVector3(fX / fRight, fY / fRight, fZ / fRight);
        }

        CVector3 operator - () const
        {
                return CVector3(-fX, -fY, -fZ);
        }

        void operator += (float fRight)
        {
                fX += fRight;
                fY += fRight;
                fZ += fRight;
        }

        void operator -= (float fRight)
        {
                fX -= fRight;
                fY -= fRight;
                fZ -= fRight;
        }

        void operator *= (float fRight)
        {
                fX *= fRight;
                fY *= fRight;
                fZ *= fRight;
        }

        void operator /= (float fRight)
        {
                fX /= fRight;
                fY /= fRight;
                fZ /= fRight;
        }
};