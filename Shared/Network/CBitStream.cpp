//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CBitStream.cpp
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//          Contains code from RakNet
//
//==============================================================================

#include "CBitStream.h"
#ifdef _LINUX
#include <string.h>
#endif
#include <assert.h>

CBitStream::CBitStream() :
	m_pData(m_stackData),
	m_uiBufferSizeInBits((BUFFER_STACK_ALLOCATION_SIZE * 8)),
	m_uiWriteOffsetInBits(0),
	m_uiReadOffsetInBits(0),
	m_bCopyData(true)

{
}

CBitStream::CBitStream(const unsigned int uiSizeInBytes)
	: 	m_uiWriteOffsetInBits(0),
	m_uiReadOffsetInBits(0),
	m_bCopyData(true)
{
	if(uiSizeInBytes <= BUFFER_STACK_ALLOCATION_SIZE)
	{
		m_pData = (unsigned char *)m_stackData;
		m_uiBufferSizeInBits = (BUFFER_STACK_ALLOCATION_SIZE * 8);
	}
	else
	{
		m_pData = (unsigned char *)malloc(uiSizeInBytes);
		m_uiBufferSizeInBits = (uiSizeInBytes << 3);
	}
}

CBitStream::CBitStream(unsigned char * pBuffer, unsigned int uiSizeInBytes, bool bCopyData)
	: 	m_uiReadOffsetInBits(0),
		m_bCopyData(bCopyData)
{
	if(bCopyData)
	{
		if(uiSizeInBytes > 0)
		{
			if(uiSizeInBytes < BUFFER_STACK_ALLOCATION_SIZE)
			{
				m_pData = (unsigned char *)m_stackData;
				m_uiBufferSizeInBits = (BUFFER_STACK_ALLOCATION_SIZE << 3);
			}
			else
				m_pData = (unsigned char *)malloc(uiSizeInBytes);

			memcpy(m_pData, pBuffer, uiSizeInBytes);
		}
		else
			m_pData = NULL;
	}
	else
		m_pData = (unsigned char *)pBuffer;

	m_uiWriteOffsetInBits = (uiSizeInBytes << 3);
	m_uiBufferSizeInBits = (uiSizeInBytes << 3);
}

CBitStream::~CBitStream()
{
	if(m_bCopyData && (m_uiBufferSizeInBits > (BUFFER_STACK_ALLOCATION_SIZE << 3)))
		free(m_pData);
}

void CBitStream::Reset(void)
{
	m_uiWriteOffsetInBits = 0;
	m_uiReadOffsetInBits = 0;
}

void CBitStream::AddBitsAndReallocate(unsigned int uiSizeInBits)
{
	unsigned int uiNewNumberOfBitsAllocated = uiSizeInBits + m_uiWriteOffsetInBits;

	// If we need to allocate 1 or more new bytes
	if(uiSizeInBits + m_uiWriteOffsetInBits > 0 && ((m_uiBufferSizeInBits - 1) >> 3) < ((uiNewNumberOfBitsAllocated - 1) >> 3))
	{
		assert(m_bCopyData == true);

		// Cap to 1 megabyte buffer to save on huge allocations
		uiNewNumberOfBitsAllocated = (uiSizeInBits + m_uiWriteOffsetInBits) * 2;

		if(uiNewNumberOfBitsAllocated - (uiSizeInBits + m_uiWriteOffsetInBits) > 1048576)
			uiNewNumberOfBitsAllocated = uiSizeInBits + m_uiWriteOffsetInBits + 1048576;

		unsigned int uiAmountToAllocate = BITS_TO_BYTES(uiNewNumberOfBitsAllocated);

		if(m_pData == (unsigned char *)m_stackData)
		{
			if (uiAmountToAllocate > BUFFER_STACK_ALLOCATION_SIZE)
			{
				m_pData = (unsigned char *)malloc(uiAmountToAllocate);

				// need to copy the stack data over to our new memory area too
				memcpy(m_pData, (void *)m_stackData, BITS_TO_BYTES(m_uiBufferSizeInBits)); 
			}
		}
		else
			m_pData = (unsigned char *)realloc(m_pData, uiAmountToAllocate);
	}

	if(uiNewNumberOfBitsAllocated > m_uiBufferSizeInBits)
		m_uiBufferSizeInBits = uiNewNumberOfBitsAllocated;
}

void CBitStream::ResetReadPointer(void)
{
	m_uiReadOffsetInBits = 0;
}

void CBitStream::ResetWritePointer(void)
{
	m_uiWriteOffsetInBits = 0;
}

void CBitStream::Write(const CString &strIn)
{
	size_t sLength = strIn.GetLength();
	Write(sLength);
	Write(strIn.Get(), sLength);
}

void CBitStream::Write(const CVector3 &vecIn)
{
	Write((char *)&vecIn, sizeof(CVector3));
}

bool CBitStream::Read(CString &strOut)
{
	strOut.Clear();
	size_t sLength = 0;
	bool bReturn = Read(sLength);

	if(bReturn && (sLength > 0))
	{
		strOut.Resize(sLength);
		char * szString = strOut.GetData();
		bReturn = Read(szString, sLength);

		if(bReturn && (szString != NULL))
			strOut.Truncate(sLength);
	}

	return bReturn;
}

bool CBitStream::Read(CVector3 &vecOut)
{
	return Read((char *)&vecOut, sizeof(CVector3));
}

void CBitStream::Write(const char * pIn, const unsigned int uiSizeInBytes)
{
	// Is the size we need to write 0?
	if(uiSizeInBytes == 0)
		return;

	// Is the current write offset a multiple of 8?
	if(MUL_OF_8(m_uiWriteOffsetInBits))
	{
		// Resize the buffer so we have enough bytes to write (If needed)
		AddBitsAndReallocate(BYTES_TO_BITS(uiSizeInBytes));

		// Write the data
		memcpy((m_pData + BITS_TO_BYTES(m_uiWriteOffsetInBits)), pIn, uiSizeInBytes);

		// Increment the write offset
		m_uiWriteOffsetInBits += BYTES_TO_BITS(uiSizeInBytes);
	}
	else
		WriteBits((unsigned char *)pIn, (uiSizeInBytes * 8));
}

bool CBitStream::Read(char * pOut, const unsigned int uiSizeInBytes)
{
	// Is the size we need to read 0?
	if(uiSizeInBytes == 0)
		return false;

	// Is the current read offset a multiple of 8?
	if(MUL_OF_8(m_uiReadOffsetInBits))
	{
		// Do we have enough bytes to read?
		if(m_uiReadOffsetInBits + (uiSizeInBytes << 3) > m_uiWriteOffsetInBits)
			return false;

		// Read the data
		memcpy(pOut, (m_pData + (m_uiReadOffsetInBits >> 3)), uiSizeInBytes);

		// Increment the read offset
		m_uiReadOffsetInBits += (uiSizeInBytes << 3);
		return true;
	}
	else
		return ReadBits((unsigned char *)pOut, (uiSizeInBytes * 8));
}

void CBitStream::WriteCompressed(const unsigned char * inByteArray, const unsigned int size, const bool unsignedData)
{
	unsigned int currentByte = (size >> 3) - 1; // PCs
	unsigned char byteMatch;

	if(unsignedData)
		byteMatch = 0;
	else
		byteMatch = 0xFF;

	// Write upper bytes with a single 1
	// From high byte to low byte, if high byte is a byteMatch then write a 1 bit. Otherwise write a 0 bit and then write the remaining bytes
	while(currentByte > 0)
	{
		if(inByteArray[currentByte] == byteMatch)   // If high byte is byteMatch (0 of 0xff) then it would have the same value shifted
		{
			bool b = true;
			Write(b);
		}
		else
		{
			// Write the remainder of the data after writing 0
			bool b = false;
			Write(b);
			WriteBits(inByteArray, (currentByte + 1) << 3, true);
			//  currentByte--;
			return ;
		}

		currentByte--;
	}

	// If the upper half of the last byte is a 0 (positive) or 16 (negative) then write a 1 and the remaining 4 bits.  Otherwise write a 0 and the 8 bites.
	if ( ( unsignedData && ( ( *( inByteArray + currentByte ) ) & 0xF0 ) == 0x00 ) ||
		( unsignedData == false && ( ( *( inByteArray + currentByte ) ) & 0xF0 ) == 0xF0 ) )
	{
		bool b = true;
		Write( b );
		WriteBits( inByteArray + currentByte, 4, true );
	}

	else
	{
		bool b = false;
		Write( b );
		WriteBits( inByteArray + currentByte, 8, true );
	}
}

bool CBitStream::ReadCompressed(unsigned char* inOutByteArray, const unsigned int size, const bool unsignedData)
{
	unsigned int currentByte = (size >> 3) - 1;
	unsigned char byteMatch, halfByteMatch;

	if(unsignedData)
	{
		byteMatch = 0;
		halfByteMatch = 0;
	}
	else
	{
		byteMatch = 0xFF;
		halfByteMatch = 0xF0;
	}

	// Upper bytes are specified with a single 1 if they match byteMatch
	// From high byte to low byte, if high byte is a byteMatch then write a 1 bit. Otherwise write a 0 bit and then write the remaining bytes
	while ( currentByte > 0 )
	{
		// If we read a 1 then the data is byteMatch.

		bool b;

		if ( Read( b ) == false )
			return false;

		if ( b )   // Check that bit
		{
			inOutByteArray[ currentByte ] = byteMatch;
			currentByte--;
		}
		else
		{
			// Read the rest of the bytes

			if ( ReadBits( inOutByteArray, ( currentByte + 1 ) << 3 ) == false )
				return false;

			return true;
		}
	}

	// All but the first bytes are byteMatch.  If the upper half of the last byte is a 0 (positive) or 16 (negative) then what we read will be a 1 and the remaining 4 bits.
	// Otherwise we read a 0 and the 8 bytes
	//RakAssert(readOffset+1 <=numberOfBitsUsed); // If this assert is hit the stream wasn't long enough to read from
	if ( m_uiReadOffsetInBits + 1 > m_uiWriteOffsetInBits )
		return false;

	bool b;

	if ( Read( b ) == false )
		return false;

	if ( b )   // Check that bit
	{

		if ( ReadBits( inOutByteArray + currentByte, 4 ) == false )
			return false;

		inOutByteArray[ currentByte ] |= halfByteMatch; // We have to set the high 4 bits since these are set to 0 by ReadBits
	}
	else
	{
		if ( ReadBits( inOutByteArray + currentByte, 8 ) == false )
			return false;
	}

	return true;
}

void CBitStream::WriteBits(const unsigned char * pIn, unsigned int uiSizeInBits, bool bAlignBitsToRight)
{
	// Is the size we need to write 0?
	if(uiSizeInBits == 0)
		return;

	// Resize the buffer so we have enough bytes to write (If needed)
	AddBitsAndReallocate(uiSizeInBits);

	// If currently aligned and numberOfBits is a multiple of 8, just memcpy for speed
	if(MUL_OF_8(m_uiWriteOffsetInBits) && MUL_OF_8(uiSizeInBits))
	{
		memcpy(m_pData + (m_uiWriteOffsetInBits >> 3), pIn, (uiSizeInBits >> 3));
		m_uiWriteOffsetInBits += uiSizeInBits;
		return;
	}

	const unsigned int uiWriteOffsetMod8 = m_uiWriteOffsetInBits & 7;
	unsigned char dataByte;
	const unsigned char * inputPtr = pIn;

	// Faster to put the while at the top surprisingly enough
	while(uiSizeInBits > 0)
	{
		dataByte = *(inputPtr++);

		if(uiSizeInBits < 8 && bAlignBitsToRight)   // rightAlignedBits means in the case of a partial byte, the bits are aligned from the right (bit 0) rather than the left (as in the normal internal representation)
			dataByte <<= 8 - uiSizeInBits;  // shift left to get the bits on the left, as in our internal representation

		// Writing to a new byte each time
		if(uiWriteOffsetMod8 == 0)
			*(m_pData + (m_uiWriteOffsetInBits >> 3)) = dataByte;
		else
		{
			// Copy over the new data.
			*(m_pData + (m_uiWriteOffsetInBits >> 3)) |= dataByte >> (uiWriteOffsetMod8); // First half

			if(8 - (uiWriteOffsetMod8) < 8 && 8 - (uiWriteOffsetMod8) < uiSizeInBits)   // If we didn't write it all out in the first half (8 - (m_uiWriteOffsetInBits%8) is the number we wrote in the first half)
			{
				*(m_pData + (m_uiWriteOffsetInBits >> 3) + 1) = (unsigned char)(dataByte << (8 - (uiWriteOffsetMod8))); // Second half (overlaps byte boundary)
			}
		}

		if(uiSizeInBits >= 8)
		{
			m_uiWriteOffsetInBits += 8;
			uiSizeInBits -= 8;
		}
		else
		{
			m_uiWriteOffsetInBits += uiSizeInBits;
			uiSizeInBits = 0;
		}
	}
}

bool CBitStream::ReadBits(unsigned char * pOut, unsigned int uiSizeInBits, bool bAlignBitsToRight)
{
	// Is the size we need to read 0?
	if(uiSizeInBits == 0)
		return false;

	// Do we have enough bits to read?
	if((m_uiReadOffsetInBits + uiSizeInBits) > m_uiWriteOffsetInBits)
		return false;

	// If currently aligned and numberOfBits is a multiple of 8, just memcpy for speed
	if(MUL_OF_8(m_uiReadOffsetInBits) && MUL_OF_8(uiSizeInBits))
	{
		memcpy(pOut, (m_pData + (m_uiReadOffsetInBits >> 3)), (uiSizeInBits >> 3));
		m_uiReadOffsetInBits += uiSizeInBits;
		return true;
	}

	const unsigned int uiReadOffsetMod8 = (m_uiReadOffsetInBits & 7);
	unsigned int uiOffset = 0;
	memset(pOut, 0, (size_t)BITS_TO_BYTES(uiSizeInBits));

	while(uiSizeInBits > 0)
	{
		*(pOut + uiOffset) |= *(m_pData + (m_uiReadOffsetInBits >> 3)) << (uiReadOffsetMod8); // First half

		if(uiReadOffsetMod8 > 0 && uiSizeInBits > 8 - (uiReadOffsetMod8))   // If we have a second half, we didn't read enough bytes in the first half
			*(pOut + uiOffset) |= *(m_pData + (m_uiReadOffsetInBits >> 3) + 1) >> (8 - (uiReadOffsetMod8)); // Second half (overlaps byte boundary)

		if(uiSizeInBits >= 8)
		{
			uiSizeInBits -= 8;
			m_uiReadOffsetInBits += 8;
			uiOffset++;
		}
		else
		{
			int neg = (int)(uiSizeInBits - 8);

			if(neg < 0) // Reading a partial byte for the last byte, shift right so the data is aligned on the right
			{
				if(bAlignBitsToRight)
					*(pOut + uiOffset) >>= -neg;

				m_uiReadOffsetInBits += 8 + neg;
			}
			else
				m_uiReadOffsetInBits += 8;

			uiOffset++;
			uiSizeInBits = 0;
		}		
	}

	return true;
}

void CBitStream::WriteBit(bool bState)
{
	if(bState)
		Write1();
	else
		Write0();
}

void CBitStream::Write0(void)
{
	AddBitsAndReallocate(1);

	if(MUL_OF_8(m_uiWriteOffsetInBits))
		m_pData[m_uiWriteOffsetInBits >> 3] = 0;

	m_uiWriteOffsetInBits++;
}

void CBitStream::Write1(void)
{
	AddBitsAndReallocate(1);

	unsigned int uiWriteOffsetMod8 = m_uiWriteOffsetInBits & 7;

	if(uiWriteOffsetMod8 == 0)
		m_pData[m_uiWriteOffsetInBits >> 3] = 0x80;
	else
		m_pData[m_uiWriteOffsetInBits >> 3] |= 0x80 >> (uiWriteOffsetMod8); // Set the bit to 1

	m_uiWriteOffsetInBits++;
}

bool CBitStream::ReadBit(void)
{
	bool bResult = (m_pData[m_uiReadOffsetInBits >> 3] & (0x80 >> (m_uiReadOffsetInBits & 7))) != 0;
	m_uiReadOffsetInBits++;
	return bResult;
}

void CBitStream::PadWithZeroToByteLength(unsigned int uiSizeInBytes)
{
	if(GetNumberOfBytesUsed() < uiSizeInBytes)
	{
		AlignWriteToByteBoundary();
		unsigned int numToWrite = (uiSizeInBytes - GetNumberOfBytesUsed());
		AddBitsAndReallocate(BYTES_TO_BITS(numToWrite));
		memset(m_pData + BITS_TO_BYTES(m_uiWriteOffsetInBits), 0, (size_t)numToWrite);
		m_uiWriteOffsetInBits += BYTES_TO_BITS(numToWrite);
	}
}
