//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CZlib.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include	"CZlib.h"
#include	<assert.h>
#include	<zlib-1.2.5/zlib.h>

#if defined(MSDOS) || defined(OS2) || defined(_WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) _setmode(_fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK	16384

int CZlib::Inflate(FILE * pSource, FILE * pDestination)
{
	int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);

    if (ret != Z_OK)
        return ret;

    do
	{
        strm.avail_in = fread(in, 1, CHUNK, pSource);

        if (ferror(pSource))
		{
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }

        if (strm.avail_in == 0)
            break;

        strm.next_in = in;

        do
		{
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);

            switch (ret)
			{
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }

            have = CHUNK - strm.avail_out;

            if (fwrite(out, 1, have, pDestination) != have || ferror(pDestination))
			{
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        }
		while (strm.avail_out == 0);

    }
	while (ret != Z_STREAM_END);

    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int CZlib::Decompress(CString strFileName, CString strOutput)
{
	// Open the files
	FILE * in = fopen(strFileName.Get(), "r");
	FILE * out = fopen(strOutput.Get(), "w+");

	// Enable binary mode
	SET_BINARY_MODE(in);
	SET_BINARY_MODE(out);

	// Deflate the file
	int iReturn = Inflate(in, out);

	// Close the files
	fclose(in);
	fclose(out);

	return iReturn;
}