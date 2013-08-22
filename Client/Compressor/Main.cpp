//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
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

// HAX, 
#include "../../Libraries/zlib-1.2.5/zlib.h"
#pragma comment(lib,"../../Libraries/zlib-1.2.5/projects/Debug/zlib_d.lib")

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
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
	CompressFile("multiplayer\\original\\carcols.dat", "multiplayer\\datafiles\\1.ivmp");
	CompressFile("multiplayer\\original\\cargrp.dat", "multiplayer\\datafiles\\2.ivmp");
	CompressFile("multiplayer\\original\\default.dat", "multiplayer\\datafiles\\3.ivmp");
	CompressFile("multiplayer\\original\\gta.dat", "multiplayer\\datafiles\\4.ivmp");
	CompressFile("multiplayer\\original\\handling.dat", "multiplayer\\datafiles\\5.ivmp");
	CompressFile("multiplayer\\original\\handlingeflc.dat", "multiplayer\\datafiles\\6.ivmp");
	CompressFile("multiplayer\\original\\hud.dat", "multiplayer\\datafiles\\7.ivmp");
	CompressFile("multiplayer\\original\\hudColor.dat", "multiplayer\\datafiles\\8.ivmp");
	CompressFile("multiplayer\\original\\images.txt", "multiplayer\\datafiles\\9.ivmp");
	CompressFile("multiplayer\\original\\vehicles.ide", "multiplayer\\datafiles\\10.ivmp");
	CompressFile("multiplayer\\original\\vehicleseflc.ide", "multiplayer\\datafiles\\11.ivmp");
	CompressFile("multiplayer\\original\\gta_ep2.wpfl", "multiplayer\\datafiles\\12.ivmp");
	CompressFile("multiplayer\\original\\ivmp.dat", "multiplayer\\datafiles\\13.ivmp");
	CompressFile("multiplayer\\original\\vehicleseflc.ide", "multiplayer\\datafiles\\14.ivmp");
	CompressFile("multiplayer\\original\\ped.dat", "multiplayer\\datafiles\\15.ivmp");
	CompressFile("multiplayer\\original\\pedgrp.dat", "multiplayer\\datafiles\\16.ivmp");
	CompressFile("multiplayer\\original\\pedpersonality.dat", "multiplayer\\datafiles\\17.ivmp");
	CompressFile("multiplayer\\original\\pedpopulation.dat", "multiplayer\\datafiles\\18.ivmp");
	CompressFile("multiplayer\\original\\pedProps.dat", "multiplayer\\datafiles\\19.ivmp");
	CompressFile("multiplayer\\original\\peds.ide", "multiplayer\\datafiles\\20.ivmp");
	CompressFile("multiplayer\\original\\pedVariations.dat", "multiplayer\\datafiles\\21.ivmp");

	// copy to gtaiv/pc/data/eflc
	CompressFile("multiplayer\\original\\animgrp_eflc.dat", "multiplayer\\datafiles\\22.ivmp");
	CompressFile("multiplayer\\original\\default_eflc.ide", "multiplayer\\datafiles\\23.ivmp"); 
	CompressFile("multiplayer\\original\\e2_xref.ide", "multiplayer\\datafiles\\24.ivmp");
	CompressFile("multiplayer\\original\\explosionFx.dat", "multiplayer\\datafiles\\25.ivmp");
	CompressFile("multiplayer\\original\\loadingscreens_eflc.dat", "multiplayer\\datafiles\\26.ivmp");
	CompressFile("multiplayer\\original\\loadingscreens_eflc.wtd", "multiplayer\\datafiles\\28.ivmp");
	CompressFile("multiplayer\\original\\peds_eflc.ide", "multiplayer\\datafiles\\29.ivmp");
	CompressFile("multiplayer\\original\\playerped_eflc.rpf", "multiplayer\\datafiles\\30.ivmp");

	// copy to gtaiv/common/data
	CompressFile("multiplayer\\original\\default.ide", "multiplayer\\datafiles\\31.ivmp");
	CompressFile("multiplayer\\original\\default_eflc.ide", "multiplayer\\datafiles\\32.ivmp");
	CompressFile("multiplayer\\original\\hudColor.dat", "multiplayer\\datafiles\\33.ivmp");
	CompressFile("multiplayer\\original\\loadingscreens_eflc.dat", "multiplayer\\datafiles\\34.ivmp");
	CompressFile("multiplayer\\original\\loadingscreens_eflc_pc.dat", "multiplayer\\datafiles\\35.ivmp");
	CompressFile("multiplayer\\original\\radiohud.dat", "multiplayer\\datafiles\\36.ivmp");
	CompressFile("multiplayer\\original\\RadioLogo.dat", "multiplayer\\datafiles\\37.ivmp");
	CompressFile("multiplayer\\original\\vehOff.csv", "multiplayer\\datafiles\\38.ivmp");
	CompressFile("multiplayer\\original\\WeaponInfo.xml", "multiplayer\\datafiles\\39.ivmp");
	CompressFile("multiplayer\\original\\WeaponInfo_EFLC.xml", "multiplayer\\datafiles\\40.ivmp");
	CompressFile("multiplayer\\original\\WeaponInfo_EFLC_C.xml", "multiplayer\\datafiles\\41.ivmp");
	CompressFile("multiplayer\\pc\\textures\\radio_hud_noncolored.wtd", "multiplayer\\datafiles\\42.ivmp");
	
	printf("FINISHED, type any key to exit...");
	getchar();
	return 1;
}