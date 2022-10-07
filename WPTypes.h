// =============================================================================
//	WPTypes.h
// =============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#ifndef WPTYPES_H
#define WPTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

// Types for ISO Standard C (ISO/IEC 9899:1999).
typedef unsigned char UInt8;
typedef signed char SInt8;
typedef unsigned short UInt16;
typedef signed short SInt16;
typedef unsigned long UInt32;
typedef signed long SInt32;
typedef signed long long SInt64;
typedef unsigned long long UInt64;

// TODO: this should not be here
#if defined(_WPDLL)
	#define DECLSPEC __declspec(dllexport)
#else
	#define DECLSPEC
#endif

#ifdef __cplusplus
}
#endif

#endif
