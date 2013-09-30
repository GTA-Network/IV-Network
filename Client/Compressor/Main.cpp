//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: Main.cpp
// Project: Client.Compressor
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../../Libraries/zlib-1.2.5/zlib.h"

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) _setmode(_fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384

int def(FILE * src, FILE * dest, int level)
{
	int ret, flush;
	unsigned have;
	z_stream stream;
	unsigned char in[CHUNK];
	unsigned char out[CHUNK];

	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;
	ret = deflateInit(&stream, level);

	if (ret != Z_OK)
		return ret;

	do
	{
		stream.avail_in = fread(in, 1, CHUNK, src);
		if (ferror(src))
		{
			(void) deflateEnd(&stream);
			return Z_ERRNO;
		}

		flush = feof(src) ? Z_FINISH : Z_NO_FLUSH;
		stream.next_in = in;

		do
		{
			stream.avail_out = CHUNK;
			stream.next_out = out;
			ret = deflate(&stream, flush);
			assert(ret != Z_STREAM_ERROR);
			have = CHUNK - stream.avail_out;
			if (fwrite(out, 1, have, dest) != have || ferror(dest))
			{
				(void) deflateEnd(&stream);
				return Z_ERRNO;
			}
		} while (stream.avail_out == 0);

		assert(stream.avail_in == 0);
	} while (flush != Z_FINISH);

	assert(ret == Z_STREAM_END);

	(void) deflateEnd(&stream);
	return Z_OK;
}

int inf(FILE *source, FILE *dest)
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
		strm.avail_in = fread(in, 1, CHUNK, source);

		if (ferror(source))
		{
			(void) inflateEnd(&strm);
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
				(void) inflateEnd(&strm);
				return ret;
			}

			have = CHUNK - strm.avail_out;

			if (fwrite(out, 1, have, dest) != have || ferror(dest))
			{
				(void) inflateEnd(&strm);
				return Z_ERRNO;
			}
		} while (strm.avail_out == 0);

	} while (ret != Z_STREAM_END);

	(void) inflateEnd(&strm);
	return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

void zerr(int ret)
{
	fputs("Error: ", stderr);
	switch (ret) {
	case Z_ERRNO:
		if (ferror(stdin))
			fputs("error reading stdin\n", stderr);
		if (ferror(stdout))
			fputs("error writing stdout\n", stderr);
		break;
	case Z_STREAM_ERROR:
		fputs("invalid compression level\n", stderr);
		break;
	case Z_DATA_ERROR:
		fputs("invalid or incomplete deflate data\n", stderr);
		break;
	case Z_MEM_ERROR:
		fputs("out of memory\n", stderr);
		break;
	case Z_VERSION_ERROR:
		fputs("zlib version mismatch!\n", stderr);
	}
}

void CompressFile(const char * szFileName, const char * szOutputName)
{
	printf("Compressing file %s...\n", szFileName);

	// Open the files
	FILE * in = fopen(szFileName, "r");
	FILE * out = fopen(szOutputName, "w+");

	// Enable binary mode
	SET_BINARY_MODE(in);
	SET_BINARY_MODE(out);

	// Deflate the file
	def(in, out, Z_DEFAULT_COMPRESSION);

	// Close the files
	fclose(in);
	fclose(out);
}

void DecompressFile(const char * szFileName, const char * szOutputName)
{
	printf("Decompressing file %s...\n", szFileName);

	// Open the files
	FILE * in = fopen(szFileName, "r");
	FILE * out = fopen(szOutputName, "w+");

	// Enable binary mode
	SET_BINARY_MODE(in);
	SET_BINARY_MODE(out);

	// Inflate the file
	inf(in, out);

	// Close the files
	fclose(in);
	fclose(out);
}

int main(int argc, char **argv)
{
	// Compress
	//CompressFile("multiplayer\\original\\loadingscreens.wtd", "multiplayer\\datafiles\\1.ivn");
	//CompressFile("multiplayer\\original\\loadingscreens_pc_eflc_v2.dat", "multiplayer\\datafiles\\2.ivn");
	//CompressFile("multiplayer\\original\\radio_hud_noncolored.wtd", "multiplayer\\datafiles\\3.ivn");
	CompressFile("multiplayer\\original\\hud_eflc.dat", "multiplayer\\datafiles\\4.ivn");

	printf("FINISHED, type any key to exit...");
	getchar();
	return 1;
}