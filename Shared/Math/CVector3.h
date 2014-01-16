/*
* Copyright C GTA-Network Team
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

#ifndef CVector3_h
#define CVector3_h

#include <math.h>

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

		bool operator == (const CVector3& vecRight) const
		{
			return ((!memcmp(this, &vecRight, sizeof(CVector3))) != 0);
		}
};
#endif // CVector3_h