//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CString.h
// Project: (Shared)
// Author:	jenksta
//			CrackHD
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CString_h
#define CString_h

#include <string>

// Represents a wrap for std string
class CString {

private:
	std::string m_stdStr;
	size_t m_sLimit;

	void Init();

public:
	static const unsigned int Limit;

	CString() { Init(); }
	CString(const char * szFormat, ...);
	~CString() { Free(); } // Dunno is this needed or not

	operator const char * () const;
	CString& operator = (const char * szString);
	CString& operator = (const CString strString);
	CString& operator = (const unsigned char ucChar);
	CString& operator += (const char * szString);
	CString& operator += (const CString strString);
	CString& operator += (const unsigned char ucChar);
	CString operator + (const char * szString) const;
	CString operator + (const CString strString) const;
	CString operator + (const unsigned char ucChar) const;
	unsigned char operator [] (size_t sOffset) const;
	bool operator == (const char * szString) const;
	bool operator == (const CString strString) const;
	bool operator != (const char * szString) const;
	bool operator != (const CString strString) const;
	bool operator > (const char * szString) const;
	bool operator > (const CString strString) const;
	bool operator >= (const char * szString) const;
	bool operator >= (const CString strString) const;
	bool operator < (const char * szString) const;
	bool operator < (const CString strString) const;
	bool operator <= (const char * szString) const;
	bool operator <= (const CString strString) const;

	bool		  EndsWith(const CString strSuffix) const;
	bool          Contains(const char * szString, size_t sPos = 0) const;
	bool          Contains(const unsigned char ucChar, size_t sPos = 0) const;
	bool          Contains(const CString strString, size_t sPos = 0) const;
	bool          IsNumeric() const;
	bool          IsAllocated() const;
	bool          IsEmpty() const;
	bool          IsNotEmpty() const;
	CString&      ToLower();
	bool          IsLower() const;
	CString&      ToUpper();
	bool          IsUpper() const;
	int           ToInteger() const;
	float         ToFloat() const;
	size_t        GetLength() const;
	size_t        GetDataSize() const;
	char *        GetData() const;
	char *        CopyData() const;
	size_t        GetLimit() const;
	const char *  Get() const;
	const char *  C_String() const;

	void          Set(const char * szString);
	void          Set(const char * szString, unsigned int uiLength);
	void          Set(const CString strString);
	void          Set(const CString strString, unsigned int uiLength);
	void          Format(const char * szFormat, ...);
	void          Truncate(size_t sOffset);
	void          Erase(size_t sOffset, size_t sCount);
	void          Clear();
	int           StrCmp(const char * szString) const { return Compare(szString); }
	int           StrCmp(const CString &strString) const { return Compare(strString); }
	int           Compare(const char * szString) const;
	int           Compare(const CString strString) const;
	int           ICompare(const char * szString) const;
	int           ICompare(const CString strString) const;
	int           StrICmp(const char * szString) const { return ICompare(szString); }
	int           StrICmp(const CString &strString) const { return ICompare(strString); }
	bool          ToBoolean() const;
	void          FromBoolean(bool bValue);
	void          FromInteger(int iValue);
	void          FromFloat(float fValue);
	void          SetChar(size_t sOffset, unsigned char cChar);
	unsigned char GetChar(size_t sOffset) const;
	CString       Substring(size_t sOffset, size_t sCount = Limit) const;
	void          Replace(size_t sOffset, const char * szString);
	void          Replace(size_t sOffset, CString strString);
	void          Append(const char * szString);
	void          Append(const char * szString, unsigned int uiLength);
	void          Append(const CString strString);
	void          Append(const CString strString, unsigned int uiLength);
	void          AppendF(const char * szFormat, ...);
	void          Append(const unsigned char ucChar);
	void          Insert(size_t sOffset, const char * szString);
	size_t        Find(const char * szString, size_t sPos = 0) const;
	size_t        Find(const unsigned char ucChar, size_t sPos = 0) const;
	size_t        Find(const CString strString, size_t sPos = 0) const;
	size_t        ReverseFind(const char * szString, size_t sPos = Limit) const;
	size_t        ReverseFind(const unsigned char ucChar, size_t sPos = Limit) const;
	size_t        ReverseFind(const CString strString, size_t sPos = Limit) const;
	size_t        Substitute(const char * szString, const CString strSubstitute);
	size_t        Substitute(const unsigned char ucChar, const CString strSubstitute);
	size_t        Substitute(const CString strString, const CString strSubstitute);
	bool          SetLimit(size_t sLimit);
	bool          LimitTruncate();
	void          Allocate(size_t sSize);
	void          Resize(size_t sSize);
	void          Free();
	static CString		DecimalToString( unsigned int uiDecimal )
	{
		CString strReturn( "%p", uiDecimal );
		strReturn.Erase( (strReturn.GetLength() - 2), 2 );
		return strReturn;
	}

	static CString		DecimalToStringNoErase( unsigned int uiDecimal )
	{
		return CString( "%p", uiDecimal );
	}

	static unsigned long	HexToInt( CString hex )
	{
		/*std::stringstream ss( hex.Get() );
		unsigned long ulResult = 0;
		ss >> std::hex >> ulResult;
		return ulResult;*/
		return 0;
	}

	int convertFromHex()
    {
		int value = 0;

        int a = 0;
		int b = (m_stdStr.length() - 1);

		for( ; b >= 0; a++, b-- )
        {
			if( m_stdStr[b] >= '0' && m_stdStr[b] <= '9' )
			{
				value += (m_stdStr[b] - '0') * (1 << (a * 4));
            }
            else
            {
				switch( m_stdStr[b] )
				{
                case 'A':
                case 'a':
                    value += 10 * (1 << (a * 4));
                    break;
                    
                case 'B':
                case 'b':
                    value += 11 * (1 << (a * 4));
                    break;

                case 'C':
                case 'c':
                    value += 12 * (1 << (a * 4));
                    break;
                    
                case 'D':
                case 'd':
                    value += 13 * (1 << (a * 4));
                    break;
                    
                case 'E':
                case 'e':
                    value += 14 * (1 << (a * 4));
                    break;
                    
                case 'F':
                case 'f':
                    value += 15 * (1 << (a * 4));
                    break;
				}
			}
		}
					
		return value;
	}
};

#endif // CString_h