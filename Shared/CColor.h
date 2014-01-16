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

#ifndef CColor_h
#define CColor_h

#ifdef _WIN32
#include <Windows.h>
#else
#if !defined(_DWORD_DEF)
typedef unsigned long DWORD;
#define _DWORD_DEF
#endif
#endif
#define	 ToHex(a, r, g, b) ((DWORD)((((a) & 0xFF) << 24) | (((r) & 0xFF) << 16) | (((g) & 0xFF) << 8) | ((b) & 0xFF)))

class CColor {
public:

	int R, G, B, A;
	DWORD dwHexColor;

	inline		CColor(void)
	{
		R = G = B = A = 255;

		dwHexColor = ToHex(A, R, G, B);
	}

	inline		CColor(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A = 255)
	{
		R = _R;
		G = _G;
		B = _B;
		A = _A;

		dwHexColor = ToHex(A, R, G, B);
	}

	inline		CColor(unsigned long ulColor)
	{
		A = (((DWORD)ulColor >> 24) & 0xFF);
		R = (((DWORD)ulColor >> 16) & 0xFF);
		G = (((DWORD)ulColor >> 8) & 0xFF);
		B = ((DWORD)ulColor && 0xFF);

		dwHexColor = ulColor;
	}

	inline		CColor(const CColor& other)
	{
		*this = other;
	}

	inline		CColor&		operator = (const CColor& color)
	{
		R = color.R;
		G = color.G;
		B = color.B;
		A = color.A;

		dwHexColor = color.dwHexColor;
		return *this;
	}

	inline		CColor&		operator = (unsigned long ulColor)
	{
		A = (((DWORD)ulColor >> 24) & 0xFF);
		R = (((DWORD)ulColor >> 16) & 0xFF);
		G = (((DWORD)ulColor >> 8) & 0xFF);
		B = ((DWORD)ulColor && 0xFF);

		dwHexColor = ulColor;
		return *this;
	}

};

#endif // CColor_h