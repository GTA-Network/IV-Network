//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CBitStream.h
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CBitStream_h
#define CBitStream_h

#include <Common.h>
#include <Math/CVector3.h>

/// Given a number of bits, return how many bytes are needed to represent that.
#define BITS_TO_BYTES(x) (((x)+7)>>3)
#define BYTES_TO_BITS(x) ((x)<<3)

// From RakNet
// Threshold at which to do a malloc / free rather than pushing data onto a fixed stack
// Arbitrary size, just picking something likely to be larger than most packets
#define BUFFER_STACK_ALLOCATION_SIZE 256

#define MUL_OF_8(x) (((x) & 7) == 0)

#define READ_TEMPLATE(size, out) \
	/* Read from the buffer */ \
	return ReadBits((unsigned char *)&out, (size * 8));

#define READ_COMPRESSED_TEMPLATE(size, out) \
	/* Read from the buffer */ \
	return ReadCompressed((unsigned char *)&out, (size * 8), true);

#define WRITE_TEMPLATE(size, in) \
	/* Write to the buffer */ \
	WriteBits((unsigned char *)&in, (size * 8), true);

#define WRITE_COMPRESSED_TEMPLATE(size, in) \
	/* Write to the buffer */ \
	WriteCompressed((unsigned char *)&in, (size * 8), true);

// Based on RakNet's BitStream class (With permission)
// Used to construct network packets
class CBitStream
{
private:
	
	unsigned char * m_pData;				// Pointer to data	
	unsigned int    m_uiBufferSizeInBits;	// Amount of memory allocated (In bits)	
	unsigned int    m_uiWriteOffsetInBits;	// Current write offset (In bits)	
	unsigned int    m_uiReadOffsetInBits;	// Current read offset (In bits)	
	bool            m_bCopyData;			// True if the internal buffer is a copy of data. False if it is a reference to a pointer
	
	// BitStreams that use less than BUFFER_STACK_ALLOCATION_SIZE use the stack,
	// rather than the heap to store data.  It switches over if BUFFER_STACK_ALLOCATION_SIZE is exceeded
	unsigned char   m_stackData[BUFFER_STACK_ALLOCATION_SIZE];

public:
	CBitStream();
	CBitStream(const unsigned int uiSizeInBytes);
	CBitStream(unsigned char * pBuffer, unsigned int uiSizeInBytes, bool bCopyData = false);
	~CBitStream();

	// Reset the BitStream for reuse.
	void                     Reset(void);

	// Reallocates (if necessary) in preparation of writing uiSizeInBits
	void                     AddBitsAndReallocate(unsigned int uiSizeInBits);

	// Reset the BitStream read pointer for reuse.
	void                     ResetReadPointer(void);

	// Reset the BitStream write pointer for reuse.
	void                     ResetWritePointer(void);

	// Write any integral type to the BitStream.
	void                     Write(const bool &bIn) { WRITE_TEMPLATE(sizeof(bool), bIn); }
	void                     Write(const char &cIn) { WRITE_TEMPLATE(sizeof(char), cIn); }
	void                     Write(const unsigned char &ucIn) { WRITE_TEMPLATE(sizeof(unsigned char), ucIn); }
	void                     Write(const short &sIn) { WRITE_TEMPLATE(sizeof(short), sIn); }
	void                     Write(const unsigned short &usIn) { WRITE_TEMPLATE(sizeof(unsigned short), usIn); }
	void                     Write(const int &iIn) { WRITE_TEMPLATE(sizeof(int), iIn); }
	void                     Write(const unsigned int &uiIn) { WRITE_TEMPLATE(sizeof(unsigned int), uiIn); }
	void                     Write(const long &lIn) { WRITE_TEMPLATE(sizeof(long), lIn); }
	void                     Write(const unsigned long &ulIn) { WRITE_TEMPLATE(sizeof(unsigned long), ulIn); }
	void                     Write(const float &fIn) { WRITE_TEMPLATE(sizeof(float), fIn); }
	void                     Write(const double &dIn) { WRITE_TEMPLATE(sizeof(double), dIn); }
	void                     Write(const CString &strIn);
	void                     Write(const CVector3 &vecIn);
	//void                     Write(const CControlState &in);

	// Write any integral type compressed to the BitStream.
	void                     WriteCompressed(const bool &bIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(bool), bIn); }
	void                     WriteCompressed(const char &cIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(char), cIn); }
	void                     WriteCompressed(const unsigned char &ucIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(unsigned char), ucIn); }
	void                     WriteCompressed(const short &sIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(short), sIn); }
	void                     WriteCompressed(const unsigned short &usIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(unsigned short), usIn); }
	void                     WriteCompressed(const int &iIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(int), iIn); }
	void                     WriteCompressed(const unsigned int &uiIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(unsigned int), uiIn); }
	void                     WriteCompressed(const long &lIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(long), lIn); }
	void                     WriteCompressed(const unsigned long &ulIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(unsigned long), ulIn); }
	void                     WriteCompressed(const float &fIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(float), fIn); }
	void                     WriteCompressed(const double &dIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(double), dIn); }

	// Read any integral type from the BitStream.
	bool                     Read(bool& bOut) { READ_TEMPLATE(sizeof(bool), bOut); }
	bool                     Read(char& cOut) { READ_TEMPLATE(sizeof(char), cOut); }
	bool                     Read(unsigned char& ucOut) { READ_TEMPLATE(sizeof(unsigned char), ucOut); }
	bool                     Read(short& sOut) { READ_TEMPLATE(sizeof(short), sOut); }
	bool                     Read(unsigned short& usOut) { READ_TEMPLATE(sizeof(unsigned short), usOut); }
	bool                     Read(int& iOut) { READ_TEMPLATE(sizeof(int), iOut); }
	bool                     Read(unsigned int& uiOut) { READ_TEMPLATE(sizeof(unsigned int), uiOut); }
	bool                     Read(long& lOut) { READ_TEMPLATE(sizeof(long), lOut); }
	bool                     Read(unsigned long& ulOut) { READ_TEMPLATE(sizeof(unsigned long), ulOut); }
	bool                     Read(float& fOut) { READ_TEMPLATE(sizeof(float), fOut); }
	bool                     Read(double& dOut) { READ_TEMPLATE(sizeof(double), dOut); }
	bool                     Read(CString &strOut);
	bool                     Read(CVector3 &vecOut);
	//bool                     Read(CControlState &out);

	// Read any compressed integral type from the BitStream.
	bool                     ReadCompressed(bool &bOut) { READ_COMPRESSED_TEMPLATE(sizeof(bool), bOut); }
	bool                     ReadCompressed(char &cOut) { READ_COMPRESSED_TEMPLATE(sizeof(char), cOut); }
	bool                     ReadCompressed(unsigned char &ucOut) { READ_COMPRESSED_TEMPLATE(sizeof(unsigned char), ucOut); }
	bool                     ReadCompressed(short &sOut) { READ_COMPRESSED_TEMPLATE(sizeof(short), sOut); }
	bool                     ReadCompressed(unsigned short &usOut) { READ_COMPRESSED_TEMPLATE(sizeof(unsigned short), usOut); }
	bool                     ReadCompressed(int &iOut) { READ_COMPRESSED_TEMPLATE(sizeof(int), iOut); }
	bool                     ReadCompressed(unsigned int &uiOut) { READ_COMPRESSED_TEMPLATE(sizeof(unsigned int), uiOut); }
	bool                     ReadCompressed(long &lOut) { READ_COMPRESSED_TEMPLATE(sizeof(long), lOut); }
	bool                     ReadCompressed(unsigned long &ulOut) { READ_COMPRESSED_TEMPLATE(sizeof(unsigned long), ulOut); }
	bool                     ReadCompressed(float &fOut) { READ_COMPRESSED_TEMPLATE(sizeof(float), fOut); }
	bool                     ReadCompressed(double &dOut) { READ_COMPRESSED_TEMPLATE(sizeof(double), dOut); }

	// Write an array or casted stream or raw data to the BitStream.
	void                     Write(const char * inputByteArray, const unsigned int numberOfBytes);

	// Read an array or casted stream or raw data from the BitStream.
	bool                     Read(char * outputByteArray, const unsigned int numberOfBytes);

private:
	// Assume the input source points to a native type, Compress and write it
	void                     WriteCompressed(const unsigned char * inByteArray, const unsigned int size, const bool unsignedData);

	// Assume the input source points to a compressed native type. Decompress and read it.
	bool                     ReadCompressed(unsigned char* inOutByteArray,	const unsigned int size, const bool unsignedData);

public:
	// Write a sequence of bits to the BitStream.
	void                     WriteBits(const unsigned char * inByteArray, unsigned int numberOfBitsToWrite, bool bAlignBitsToRight = true);

	// Read a sequence of bits from the BitStream.
	bool                     ReadBits(unsigned char * inOutByteArray, unsigned int numberOfBitsToRead, bool bAlignBitsToRight = true);

	// Write a 0 or 1 to the BitStream.
	void                     WriteBit(bool bState);

	// Write a 0 to the BitStream.
	void                     Write0(void);

	// Write a 1 to the BitStream.
	void                     Write1(void);

	// Returns true if the next data read is a 1, false if it is a 0.
	bool                     ReadBit(void);

	// Returns a pointer to the data in the BitStream.
	unsigned char *          GetData() const { return m_pData; }

	// Returns the number of bits used in the BitStream.
	unsigned int             GetNumberOfBitsUsed() const { return m_uiWriteOffsetInBits; }

	// Returns the number of bytes used in the BitStream.
	unsigned int             GetNumberOfBytesUsed() const { return BITS_TO_BYTES(m_uiWriteOffsetInBits); }

	// Returns the number of unread bits left in the BitStream.
	unsigned int             GetNumberOfUnreadBits() const { return (m_uiWriteOffsetInBits - m_uiReadOffsetInBits); }

	// Returns the number of unread bytes left in the BitStream.
	unsigned int             GetNumberOfUnreadBytes() const { return BITS_TO_BYTES(m_uiWriteOffsetInBits - m_uiReadOffsetInBits); }

	// Ignore data we don't intend to read.
	void                     IgnoreBits(const unsigned int uiSizeInBits) { m_uiReadOffsetInBits += uiSizeInBits; }

	// Ignore data we don't intend to read.
	void                     IgnoreBytes(const unsigned int uiSizeInBytes) { m_uiReadOffsetInBits += BYTES_TO_BITS(uiSizeInBytes); }

	// Write zeros until the BitStream is filled up to uiSizeInBytes.
	void                     PadWithZeroToByteLength(unsigned int uiSizeInBytes);

	// Align the write offset to a byte boundary.
	void                     AlignWriteToByteBoundary() { m_uiWriteOffsetInBits += 8 - (((m_uiWriteOffsetInBits - 1) & 7) + 1); }

	// Align the read offset to a byte boundary.
	void                     AlignReadToByteBoundary() { m_uiReadOffsetInBits += 8 - (((m_uiReadOffsetInBits - 1) & 7) + 1);}
};

#endif // CBitStream_h