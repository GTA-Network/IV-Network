//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CColor.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

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