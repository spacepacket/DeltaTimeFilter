// ============================================================================
//	MemUtil.h
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#ifndef MEMUTIL_H
#define MEMUTIL_H

#include "WPTypes.h"

#ifdef _WIN32

// Set up __BYTE_ORDER
#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN	1234
#endif
#ifndef __BIG_ENDIAN
#define __BIG_ENDIAN	4321
#endif
#ifndef __PDP_ENDIAN
#define __PDP_ENDIAN	3412
#endif
#define __BYTE_ORDER	__LITTLE_ENDIAN

// Set up bswap_16, bswap_32 and bswap_64
#include <stdlib.h>
#ifndef bswap_16
#define bswap_16(x)		_byteswap_ushort(x)
#endif
#ifndef bswap_32
#define bswap_32(x)		_byteswap_ulong(x)
#endif
#ifndef bswap_64
#define bswap_64(x)		_byteswap_uint64(x)
#endif

#pragma intrinsic(_byteswap_ushort,_byteswap_ulong,_byteswap_uint64)

#else

#include <endian.h>		// For __BYTE_ORDER
#include <byteswap.h>	// For bswap_16, bswap_32 and bswap_64

#endif

namespace MemUtil
{

inline UInt16 Swap16( UInt16 x )
{
	return bswap_16( x );
}

inline SInt16 Swap16( SInt16 x )
{
	return bswap_16( x );
}

inline UInt32 Swap32( UInt32 x )
{
	return bswap_32( x );
}

inline SInt32 Swap32( SInt32 x )
{
	return bswap_32( x );
}

inline UInt64 Swap64( UInt64 x )
{
	return bswap_64( x );
}

inline SInt64 Swap64( SInt64 x )
{
	return bswap_64( x );
}

inline UInt8 Reverse8( UInt8 x )
{
	UInt8	r = 0;
#define S(n)	if ( x & (1 << n ) ) { r |= 0x80 >> n; }
	S(0); S(1); S(2); S(3);
	S(4); S(5); S(6); S(7);
#undef S
	return r;
}

inline UInt16 GetShort( const UInt8* pData, int bo = __BYTE_ORDER )
{
	if ( bo == __BIG_ENDIAN )
	{
		return ((pData[0] << 8) | pData[1]);
	}
	else
	{
		return ((pData[1] << 8) | pData[0]);
	}
}

inline UInt32 GetLong( const UInt8* pData, int bo = __BYTE_ORDER )
{
	if ( bo == __BIG_ENDIAN )
	{
		return ((pData[0] << 24) | (pData[1] << 16) | (pData[2] << 8) | pData[3]);
	}
	else
	{
		return ((pData[3] << 24) | (pData[2] << 16) | (pData[1] << 8) | pData[0]);
	}
}

inline UInt64 GetLongLong( const UInt8* pData, int bo = __BYTE_ORDER )
{
	if ( bo == __BIG_ENDIAN )
	{
		UInt64	t;
		UInt64	v = 0;
		t = pData[0]; v |= (t << 56);
		t = pData[1]; v |= (t << 48);
		t = pData[2]; v |= (t << 40);
		t = pData[3]; v |= (t << 32);
		t = pData[4]; v |= (t << 24);
		t = pData[5]; v |= (t << 16);
		t = pData[6]; v |= (t << 8);
		t = pData[7]; v |= t;
		return v;
	}
	else
	{
		UInt64	t;
		UInt64	v = 0;
		t = pData[7]; v |= (t << 56);
		t = pData[6]; v |= (t << 48);
		t = pData[5]; v |= (t << 40);
		t = pData[4]; v |= (t << 32);
		t = pData[3]; v |= (t << 24);
		t = pData[2]; v |= (t << 16);
		t = pData[1]; v |= (t << 8);
		t = pData[0]; v |= t;
		return v;
	}
}

} /* namespace MemUtil */

#if __BYTE_ORDER == __BIG_ENDIAN
#define BIGTOHOST16(x)		(x)
#define HOSTTOBIG16(x)		(x)
#define BIGTOHOST32(x)		(x)
#define HOSTTOBIG32(x)		(x)
#define BIGTOHOST64(x)		(x)
#define HOSTTOBIG64(x)		(x)
#define LITTLETOHOST16(x)	(MemUtil::Swap16(x))
#define HOSTTOLITTLE16(x)	(MemUtil::Swap16(x))
#define LITTLETOHOST32(x)	(MemUtil::Swap32(x))
#define HOSTTOLITTLE32(x)	(MemUtil::Swap32(x))
#define LITTLETOHOST64(x)	(MemUtil::Swap64(x))
#define HOSTTOLITTLE64(x)	(MemUtil::Swap64(x))
#elif __BYTE_ORDER == __LITTLE_ENDIAN
#define BIGTOHOST16(x)		(MemUtil::Swap16(x))
#define HOSTTOBIG16(x)		(MemUtil::Swap16(x))
#define BIGTOHOST32(x)		(MemUtil::Swap32(x))
#define HOSTTOBIG32(x)		(MemUtil::Swap32(x))
#define BIGTOHOST64(x)		(MemUtil::Swap64(x))
#define HOSTTOBIG64(x)		(MemUtil::Swap64(x))
#define LITTLETOHOST16(x)	(x)
#define HOSTTOLITTLE16(x)	(x)
#define LITTLETOHOST32(x)	(x)
#define HOSTTOLITTLE32(x)	(x)
#define LITTLETOHOST64(x)	(x)
#define HOSTTOLITTLE64(x)	(x)
#endif

#define NETWORKTOHOST16(x)	BIGTOHOST16(x)
#define HOSTTONETWORK16(x)	HOSTTOBIG16(x)
#define NETWORKTOHOST32(x)	BIGTOHOST32(x)
#define HOSTTONETWORK32(x)	HOSTTOBIG32(x)
#define NETWORKTOHOST64(x)	BIGTOHOST64(x)
#define HOSTTONETWORK64(x)	HOSTTOBIG64(x)

// Conversions for bytes to/from KB/MB/GB.
#define BYTES_PER_KILOBYTE	1024
#define BYTES_PER_MEGABYTE	1048576			// 1024 * 1024
#define BYTES_PER_GIGABYTE	1073741824		// 1024 * 1024 * 1024

#endif
