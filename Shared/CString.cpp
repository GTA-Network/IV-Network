//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CString.cpp
// Project: (Shared)
// Author:	CrackHD
//			jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CString.h"
#include <sstream>

#ifdef _WIN32
	#define stricmp _stricmp
	#include <stdarg.h>     // va_list, va_start, va_arg, va_end
#else
#define stricmp strcasecmp
#define vsprintf_s vsprintf
#define vsnprintf_s vsnprintf
#define sprintf_s sprintf
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#endif

#define BUFFER_SIZE 8192
#define NPOS std::string::npos // 77777? CrackHD: Find() and some other things will return actually std::string::npos, so 7777 will be incorrect ..

const unsigned int CString::Limit = std::string::npos;

CString::CString(const char * szFormat, ...)
{
	Init();

	if(szFormat)
	{
		char szString[BUFFER_SIZE];
		va_list vaArgs;
		va_start(vaArgs, szFormat);
		vsnprintf_s(szString, sizeof(szString), szFormat, vaArgs);
		va_end(vaArgs);
		Set(szString);
	}
}

CString::operator const char * () const
{
	return m_stdStr.c_str();
}

CString& CString::operator = (const char * szString)
{
	Set(szString);
	return *this;
}

CString& CString::operator = (const CString strString)
{
	Set(strString.Get());
	return *this;
}

CString& CString::operator = (const unsigned char ucChar)
{
	char szString[2];
	szString[0] = ucChar;
	szString[1] = '\0';
	Set(szString);
	return *this;
}

CString& CString::operator += (const char * szString)
{
	Append(szString);
	return *this;
}

CString& CString::operator += (const CString strString)
{
	Append(strString.Get());
	return *this;
}

CString& CString::operator += (const unsigned char ucChar)
{
	Append(ucChar);
	return *this;
}

CString CString::operator + (const char * szString) const
{
	CString strNewString(*this);
	strNewString.Append(szString);
	return strNewString;
}

CString CString::operator + (const CString strString) const
{
	CString strNewString(*this);
	strNewString.Append(strString.Get());
	return strNewString;
}

CString CString::operator + (const unsigned char ucChar) const
{
	CString strNewString(*this);
	strNewString.Append(ucChar);
	return strNewString;
}

unsigned char CString::operator [] (size_t sOffset) const
{
	return GetChar(sOffset);
}

bool CString::operator == (const char * szString) const
{
	return (Compare(szString) == 0);
}

bool CString::operator == (const CString strString) const
{
	return (Compare(strString.Get()) == 0);
}

bool CString::operator != (const char * szString) const
{
	return (Compare(szString) != 0);
}

bool CString::operator != (const CString strString) const
{
	return (Compare(strString.Get()) != 0);
}

bool CString::operator > (const char * szString) const
{
	return (Compare(szString) > 0);
}

bool CString::operator > (const CString strString) const
{
	return (Compare(strString.Get()) > 0);
}

bool CString::operator >= (const char * szString) const
{
	return (Compare(szString) >= 0);
}

bool CString::operator >= (const CString strString) const
{
	return (Compare(strString.Get()) >= 0);
}

bool CString::operator < (const char * szString) const
{
	return (Compare(szString) < 0);
}

bool CString::operator < (const CString strString) const
{
	return (Compare(strString.Get()) < 0);
}

bool CString::operator <= (const char * szString) const
{
	return (Compare(szString) <= 0);
}

bool CString::operator <= (const CString strString) const
{
	return (Compare(strString.Get()) <= 0);
}

void CString::Init()
{
	// TODO: Change no limit to 0?
	m_sLimit = Limit;
}

const char * CString::Get() const
{
	return m_stdStr.c_str();
}

const char * CString::C_String() const
{
	return m_stdStr.c_str();
}

void CString::Set(const char * szString)
{
	// Make sure the string is valid
	if(szString)
	{
		// Set the string
		m_stdStr.assign(szString);

		// Ensure we haven't passed the string limit
		LimitTruncate();
	}
}

void CString::Set(const char * szString, unsigned int uiLength)
{
	// Make sure the string is valid
	if(szString)
	{
		// Ensure the length is valid
		unsigned int uiStringLength = strlen(szString);

		if(uiLength > uiStringLength)
			uiLength = uiStringLength;

		// Set the string
		m_stdStr.assign(szString, uiLength);

		// Ensure we haven't passed the string limit
		LimitTruncate();
	}
}

void CString::Set(const CString strString)
{
	// Set the string
	m_stdStr.assign(strString.Get());

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

void CString::Set(const CString strString, unsigned int uiLength)
{
	// Ensure the length is valid
	if(uiLength > strString.GetLength())
		uiLength = strString.GetLength();

	// Set the string
	m_stdStr.assign(strString.Get(), uiLength);

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

void CString::Format(const char * szFormat, ...)
{
	char szString[BUFFER_SIZE];
	va_list vaArgs;
	va_start(vaArgs, szFormat);
	vsprintf_s(szString, szFormat, vaArgs);
	va_end(vaArgs);
	Set(szString);
}

size_t CString::GetLength() const
{
	return m_stdStr.size();
}

bool CString::IsEmpty() const
{
	return m_stdStr.empty();
}

bool CString::IsNotEmpty() const
{
	return !m_stdStr.empty();
}

CString& CString::ToLower()
{
	for(size_t i = 0; i < GetLength(); i++)
		m_stdStr[i] = tolower(m_stdStr[i]);

	return *this;
}

bool CString::IsLower() const
{
	for(size_t i = 0; i < GetLength(); i++)
	{
		unsigned char cChar = m_stdStr[i];

		if(((cChar >= 'a' && cChar <= 'Z') || (cChar >= 'A' && cChar <= 'Z')) && !islower(cChar))
			return false;
	}

	return true;
}

CString& CString::ToUpper()
{
	for(size_t i = 0; i < GetLength(); i++)
		m_stdStr[i] = toupper(m_stdStr[i]);

	return *this;
}

bool CString::IsUpper() const
{
	for(size_t i = 0; i < GetLength(); i++)
	{
		unsigned char cChar = m_stdStr[i];

		if(((cChar >= 'a' && cChar <= 'Z') || (cChar >= 'A' && cChar <= 'Z')) && !isupper(cChar))
			return false;
	}

	return true;
}

void CString::Truncate(size_t sOffset)
{
	if(sOffset < GetLength())
		m_stdStr.resize(sOffset);
}

void CString::Erase(size_t sOffset, size_t sCount)
{
	m_stdStr.erase(sOffset, sCount);
}

void CString::Clear()
{
	m_stdStr.clear();
}

int CString::Compare(const char * szString) const
{
	return strcmp(Get(), szString);
}

int CString::Compare(const CString strString) const
{
	return strcmp(Get(), strString.Get());
}

int CString::ICompare(const char * szString) const
{
	return stricmp(Get(), szString);
}

int CString::ICompare(const CString strString) const
{
	return stricmp(Get(), strString.Get());
}

bool CString::ToBoolean() const
{
	if(ToInteger() == 1 || !ICompare("true"))
		return true;

	return false;
}

void CString::FromBoolean(bool bValue)
{
	if(bValue)
		Set("true");
	else
		Set("false");
}

int CString::ToInteger() const
{
	return atoi(Get());
}

void CString::FromInteger(int iValue)
{
	char szBuffer[64];
	sprintf_s(szBuffer, "%i", iValue);
	Set(szBuffer);
}

float CString::ToFloat() const
{
	return (float)atof(Get());
}

void CString::FromFloat(float fValue)
{
	std::ostringstream ss;
	ss << fValue;
	Set(ss.str().c_str());
}

void CString::SetChar(size_t sOffset, unsigned char cChar)
{
	// TODO: Use allocated size instead of/aswell as the string length?
	if(sOffset < GetLength())
		m_stdStr[sOffset] = cChar;
}

unsigned char CString::GetChar(size_t sOffset) const
{
	// TODO: Use allocated size instead of/aswell as the string length?
	if(sOffset < GetLength())
		return m_stdStr[sOffset];

	return 0;
}

// Returns substring of this string by start index and count of symbols to copy
CString CString::Substring(size_t sOffset, size_t sCount) const
{
	return CString(m_stdStr.substr(sOffset, sCount).c_str());
}

void CString::Replace(size_t sOffset, const char * szString)
{
	// TODO:
	//m_stdStr.replace(sOffset, szString);
}

void CString::Replace(size_t sOffset, CString strString)
{
	// TODO:
	//m_stdStr.replace(sOffset, strString.Get());
}

// Appends current string with specified value
void CString::Append(const char * szString)
{
	// Make sure the string is valid
	if(szString)
	{
		// Copy the string to the end of our string
		m_stdStr.append(szString);

		// Ensure we haven't passed the string limit
		LimitTruncate();
	}
}

// Appends current string with specified value
void CString::Append(const char * szString, unsigned int uiLength)
{
	// Make sure the string is valid
	if(szString)
	{
		// Ensure the length is valid
		unsigned int uiStringLength = strlen(szString);

		if(uiLength > uiStringLength)
			uiLength = uiStringLength;

		// Copy the string to the end of our string
		m_stdStr.append(szString, uiLength);

		// Ensure we haven't passed the string limit
		LimitTruncate();
	}
}

// Appends current string with specified value
void CString::Append(const CString strString)
{
	// Copy the string to the end of our string
	m_stdStr.append(strString.Get());

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

// Appends current string with specified value
void CString::Append(const CString strString, unsigned int uiLength)
{
	// Ensure the length is valid
	if(uiLength > strString.GetLength())
		uiLength = strString.GetLength();

	// Copy the string to the end of our string
	m_stdStr.append(strString.Get(), uiLength);

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

// Appends current string with specified value
void CString::AppendF(const char * szFormat, ...)
{
	// Make sure the format is valid
	if(szFormat)
	{
		char szString[BUFFER_SIZE];
		va_list vaArgs;
		va_start(vaArgs, szFormat);
		vsprintf_s(szString, szFormat, vaArgs);
		va_end(vaArgs);

		// Copy the string to the end of our string
		m_stdStr.append(szString);

		// Ensure we haven't passed the string limit
		LimitTruncate();
	}
}

// Appends current string with specified value
void CString::Append(const unsigned char ucChar)
{
	// Construct the string to append
	char szString[2];
	szString[0] = ucChar;
	szString[1] = '\0';

	// Copy the string to the end of our string
	m_stdStr.append(szString);

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

// Inserts other string at index of this string
void CString::Insert(size_t sOffset, const char * szString)
{
	m_stdStr.insert(sOffset, szString);

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

// Returns index where specified substring starts, or std::string::npos if substring is not found
size_t CString::Find(const char * szString, size_t sPos) const
{
	return m_stdStr.find(szString, sPos);
}

// Returns index where specified substring starts, or std::string::npos if substring is not found
size_t CString::Find(const unsigned char ucChar, size_t sPos) const
{
	return m_stdStr.find(ucChar, sPos);
}

// Returns index where specified substring starts, or std::string::npos if substring is not found
size_t CString::Find(const CString strString, size_t sPos) const
{
	return m_stdStr.find(strString.Get(), sPos);
}

// Checks if string ends with specified substring
bool CString::EndsWith(const CString strSuffix) const
{
    if (m_stdStr.length() >= strSuffix.GetLength()) {
		return (0 == m_stdStr.compare (m_stdStr.length() - strSuffix.GetLength(), strSuffix.GetLength(), strSuffix.Get()));
	}
	else {
		return false;
	}
}

// Checks if one string contains another
bool CString::Contains(const char * szString, size_t sPos) const
{
	return (Find(szString, sPos) != Limit);
}

// Checks if one string contains another
bool CString::Contains(const unsigned char ucChar, size_t sPos) const
{
	return (Find(ucChar, sPos) != Limit);
}

// Checks if one string contains another
bool CString::Contains(const CString strString, size_t sPos) const
{
	return (Find(strString.Get(), sPos) != Limit);
}

size_t CString::ReverseFind(const char * szString, size_t sPos) const
{
	return m_stdStr.rfind(szString, sPos);
}

size_t CString::ReverseFind(const unsigned char ucChar, size_t sPos) const
{
	return m_stdStr.rfind(ucChar, sPos);
}

size_t CString::ReverseFind(const CString strString, size_t sPos) const
{
	return m_stdStr.rfind(strString.Get(), sPos);
}

size_t CString::Substitute(const char * szString, const CString strSubstitute)
{
	// Reset the find position and the instance count
	unsigned int uiFind = CString::Limit;
	unsigned int uiInstanceCount = 0;

	// Loop until we have no more instances of the sequence left in the string
	while((uiFind = Find(szString)) != CString::Limit)
	{
		// Erase this instance of the sequence
		Erase(uiFind, strlen(szString));

		// Insert the substitute where the instance of the sequence used to be
		Insert(uiFind, strSubstitute);

		// Increment the instance count
		uiInstanceCount++;
	}

	// Return the instance count
	return uiInstanceCount;
}

size_t CString::Substitute(const unsigned char ucChar, const CString strSubstitute)
{
	// Construct the string to substitute
	char szString[2];
	szString[0] = ucChar;
	szString[1] = '\0';

	return Substitute(szString, strSubstitute);
}

size_t CString::Substitute(const CString strString, const CString strSubstitute)
{
	return Substitute(strString.C_String(), strSubstitute);
}

bool CString::IsNumeric() const
{
	for(size_t i = 0; i < GetLength(); i++)
	{
		unsigned char cChar = m_stdStr[i];

		if(!isdigit(cChar))
			return false;
	}

	return true;
}

bool CString::SetLimit(size_t sLimit)
{
	m_sLimit = sLimit;
	return true;
}

size_t CString::GetLimit() const
{
	return m_sLimit;
}

bool CString::LimitTruncate()
{
	if(m_sLimit > Limit && GetLength() > m_sLimit)
	{
		m_stdStr[m_sLimit] = '\0';
		return true;
	}

	return false;
}

// NOTE: If size is less than is allocated this will
// free the extra memory, so allocate is bad naming,
// should be something along the lines of "Reallocate"
void CString::Allocate(size_t sSize)
{
	// If the size is 0 or less free the buffer
	/*if(sSize == 0)
	{
		Free();
		return;
	}*/

	m_stdStr.reserve(sSize);
}

void CString::Resize(size_t sSize)
{
	m_stdStr.resize(sSize);
}

void CString::Free()
{
	m_stdStr.clear();
}

size_t CString::GetDataSize() const
{
	return m_stdStr.capacity();
}

bool CString::IsAllocated() const
{
	//return (m_stdStr->capacity() > 0);
	return true;
}

char * CString::GetData() const
{
	// Better way?
	return (char *)m_stdStr.data();
}

char * CString::CopyData() const
{
	char * c = new char[m_stdStr.length()];
#ifdef _WIN32
	strcpy_s(c, m_stdStr.length(), m_stdStr.c_str());
#else
	strcpy(c, m_stdStr.c_str());
#endif
	return c;
}