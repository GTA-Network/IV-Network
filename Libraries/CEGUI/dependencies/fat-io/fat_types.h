#ifndef __FAT_TYPES_H__
#define __FAT_TYPES_H__

//-------------------------------------------------------------
// System specific types
//-------------------------------------------------------------
#ifndef DEF_BYTE
#define DEF_BYTE
	typedef unsigned char BYTE;
#endif

#ifndef DEF_UINT16
#define DEF_UINT16
	typedef unsigned short UINT16;
#endif

#ifndef DEF_UINT32
#define DEF_UINT32
	typedef unsigned long UINT32;
#endif

#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

#ifndef NULL
	#define NULL 0
#endif

//-------------------------------------------------------------
// Endian Macros
//-------------------------------------------------------------
// FAT is little endian so big endian systems need to swap words

// Little Endian - No swap required
#if FATFS_IS_LITTLE_ENDIAN == 1
	
	#define FAT_HTONS(n) (n)
	#define FAT_HTONL(n) (n)

// Big Endian - Swap required
#else

	#define FAT_HTONS(n) ((((unsigned short)((n) & 0xff)) << 8) | (((n) & 0xff00) >> 8))
	#define FAT_HTONL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
					((((unsigned long)(n) & 0xFF00)) << 8) | \
					((((unsigned long)(n) & 0xFF0000)) >> 8) | \
					((((unsigned long)(n) & 0xFF000000)) >> 24))

#endif

//-------------------------------------------------------------
// Structure Packing Compile Options
//-------------------------------------------------------------
#define STRUCT_PACK	
#define STRUCT_PACK_BEGIN	
#define STRUCT_PACK_END		
#define STRUCT_PACKED

#endif
