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

#ifndef CRectangle_h
#define CRectangle_h

template<class T = int>
class CRectangle
{
private:
	T m_X = 0;
	T m_Y = 0;
	T m_Width = 0;
	T m_Height = 0;

public:
	CRectangle(decltype(m_X) x, decltype(m_Y) y, decltype(m_Width) w, decltype(m_Height) h)
		: m_X(x),
		m_Y(y),
		m_Width(w),
		m_Height(h)
	{

	}

	decltype(m_X) GetX()
	{
		return m_X;
	};

	decltype(m_Y) GetY()
	{
		return m_Y;
	};

	decltype(m_Width) GetWidth()
	{
		return m_Width;
	};

	decltype(m_Height) GetHeight()
	{
		return m_Height;
	};

	bool operator==(const CRectangle<T> &other)
	{
		return(other.GetX() == GetX()
			   && other.GetY() == GetY()
			   && other.GetWidth() == GetWidth()
			   && other.GetHeight() == GetHeight());
	}
};


#endif // CRectangle_h