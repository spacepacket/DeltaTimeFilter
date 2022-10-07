// =============================================================================
//	PacketHeaders.h
// =============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#ifndef PACKETHEADERS_H
#define PACKETHEADERS_H

#include "WPTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push,1)


// ----------------------------------------------------------------------------
//		Ethernet
// ----------------------------------------------------------------------------

struct EthernetPacketHeader
{
	UInt8		DestAddr[6];		// Destination address.
	UInt8		SrcAddr[6];			// Source address.
	UInt16		Protocol;			// Protocol.
};
typedef struct EthernetPacketHeader EthernetPacketHeader;


// ----------------------------------------------------------------------------
//		TokenRing
// ----------------------------------------------------------------------------

struct TokenRingPacketHeader
{
	UInt8		AccessControl;		// MAC header.
	UInt8		FrameControl;		// MAC header.
	UInt8		DestAddr[6];		// Destination address.
	UInt8		SrcAddr[6];			// Source address.
};
typedef struct TokenRingPacketHeader TokenRingPacketHeader;


// ----------------------------------------------------------------------------
//		Wireless
// ----------------------------------------------------------------------------

struct Wireless80211MacHeader
{
	UInt8		FrameControlType;
	UInt8		FrameControlFlags;
	UInt16		Duration;
	UInt8		Addr1[6];
	UInt8		Addr2[6];
	UInt8		Addr3[6];
	UInt16		Sequence;
	UInt8		Addr4[6];
};
typedef struct Wireless80211MacHeader Wireless80211MacHeader;


// ----------------------------------------------------------------------------
//		Media Specific Info - things not shared between media types
//			IMPORTANT - all of these structures must exactly
//				match the definitions in PeekInterface.h
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
//		Media Specific Header - starts off every media specfic info block
// ----------------------------------------------------------------------------

struct MediaSpecificPrivateHeader
{
	UInt32		nSize;	// size of the whole info block, which is this struct and one of the ones below
	UInt32		nType;
};
typedef struct MediaSpecificPrivateHeader MediaSpecificPrivateHeader;

// Type definitions
#define	kMediaSpecificHdrType_Invalid		0
#define	kMediaSpecificHdrType_Wireless		1	//	obsolete, these should get upgraded to WirelessEx
#define	kMediaSpecificHdrType_WirelessEx	2	//  obsolete, internal use by drivers only
#define	kMediaSpecificHdrType_FullDuplex	3
#define	kMediaSpecificHdrType_Wan			4
#define	kMediaSpecificHdrType_Wireless2		5

// ----------------------------------------------------------------------------
//		Wireless
// ----------------------------------------------------------------------------

// Original wireless header - exactly the same as PEEK_802_11_HDR.
struct Wireless80211PrivateHeaderObs
{
	UInt8		DataRate;			// Data rate in 500 Kbps units.
	UInt8		Channel;			// 802.11b channel 1-14.
	UInt8		SignalStrength;		// Signal strength 0-100%.
	UInt8		Padding;
};
typedef struct Wireless80211PrivateHeaderObs Wireless80211PrivateHeaderObs;

// Wireless header for v5.1.x - exactly the same as PEEK_802_11_HDR_EX.
struct Wireless80211PrivateHeaderExObs
{
	UInt8		DataRate;			// Data rate in 500 Kbps units.
	UInt8		Channel;			// 802.11b channel 1-14.
	UInt8		SignalStrength;		// Signal strength 0-100%.
	UInt8		NoiseStrength;		// Noise strength 0-100%
	SInt16		SignaldBm;			// signal strength dBm
	SInt16		NoisedBm;			// Noise dBm
};
typedef struct Wireless80211PrivateHeaderExObs Wireless80211PrivateHeaderExObs;

// re-defined from PeekInterface.h
#define PEEK_802_11_BAND            1                    // vanilla 802.11 band (2MBit, 2.4GHz)
#define PEEK_802_11_B_BAND          2                   // 802.11b band (11MBit 2.4GHz)
#define PEEK_802_11_A_BAND          3                   // 802.11a band (54MBit 5GHz)
#define PEEK_802_11_G_BAND          4                   // 802.11g band (54MBit 2.4GHz)
#define PEEK_802_11_BG_BAND         PEEK_802_11_G_BAND  // (802.11g band is also 802.11b at the same time)
#define PEEK_802_11_N_BAND          6                   // 802.11n beam forming band 100MBit+ (still not released)
#define PEEK_802_11_A_TURBO_BAND    7                   // 802.11a doubled speed (108 Mbit 5GHz)
#define PEEK_802_11_G_TURBO_BAND    8                   // 802.11g doubled speed (108Mbit 5Ghz)
#define PEEK_802_11_SUPER_G_BAND    9                   // 802.11g dynamic turbo band
#define PEEK_802_11_A_LICENSED_1MHZ_BAND    100         // [La1]"802.11a 1MHz licensed band" (FCC only for now)
#define PEEK_802_11_A_LICENSED_5MHZ_BAND    101         // [La5]"802.11a 5MHz licensed band" (FCC only for now)
#define PEEK_802_11_A_LICENSED_10MHZ_BAND   102         // [La10]"802.11a 10MHz licensed band" (FCC only for now)
#define PEEK_802_11_A_LICENSED_15MHZ_BAND   103         // [La15]"802.11a 15MHz licensed band" (FCC only for now)
#define PEEK_802_11_A_LICENSED_20MHZ_BAND   104         // [La20]"802.11a 20MHz licensed band" (FCC only for now)

// Check for the 4.9GHz broadband public safety band
#define IS_49GHZ_BROADBAND_PUBLIC_SAFETY_BAND(band) \
	( ((band) == PEEK_802_11_A_LICENSED_1MHZ_BAND) || \
	  ((band) == PEEK_802_11_A_LICENSED_5MHZ_BAND) || \
	  ((band) == PEEK_802_11_A_LICENSED_10MHZ_BAND) || \
	  ((band) == PEEK_802_11_A_LICENSED_15MHZ_BAND) || \
	  ((band) == PEEK_802_11_A_LICENSED_20MHZ_BAND) )

// first the detailed channel struct, same as PEEK_802_11_DETAILED_CHANNEL
struct SWirelessChannel
{
    SInt16      Channel;       // Channel number, usually between 0-199
	UInt32		Frequency;     // Frequency in MHz ie. 2346 for 2346MHz
	UInt32		Band;          // Using the 802_11_SPEC...
};
typedef struct SWirelessChannel SWirelessChannel;

// New wireless header - exactly the same as PEEK_802_11_HDR_2.
struct Wireless80211PrivateHeader
{
	UInt8		DataRate;			// Data rate in 500 Kbps units.
	SWirelessChannel       Channel;	// channel, freq, flags to indicate spec
	UInt8		SignalStrength;		// Signal strength 0-100%.
	UInt8		NoiseStrength;		// Noise strength 0-100%
	SInt16		SignaldBm;			// signal strength dBm
	SInt16		NoisedBm;			// Noise dBm
};
typedef struct Wireless80211PrivateHeader Wireless80211PrivateHeader;

#ifndef PEEK_NULL_DBM
#define PEEK_NULL_DBM   -32767   // -32767 dBm is the smallest we can ever have in a SHORT
#endif
#ifndef PEEK_MIN_DBM
#define PEEK_MIN_DBM    -100                    // -100dBm is 0.1pW, the smallest usable frame I saw was 1pW
#endif
#ifndef PEEK_MAX_DBM
#define PEEK_MAX_DBM    -5                      // -5dBm is 320uW the biggest I ever saw was 1uW
#endif


// ----------------------------------------------------------------------------
//		Full Duplex header - exactly the same as PEEK_FULLDUPLEX_HDR
// ----------------------------------------------------------------------------

struct FullDuplexPrivateHeader
{
	UInt32		Channel;			// Channel number
};
typedef struct FullDuplexPrivateHeader FullDuplexPrivateHeader;

// These are in PeekInterface.h, but redefined here
#ifndef	PEEK_INVALID_DUPLEX_CHANNEL
#define	PEEK_INVALID_DUPLEX_CHANNEL		0
#endif


// ----------------------------------------------------------------------------
//		WAN header - exactly the same as PEEK_WAN_HDR
// ----------------------------------------------------------------------------

// Exactly the same as PEEK_WAN_HDR in PeekInteface.h, redefined here.
struct WideAreaNetworkHeader
{
	UInt8		Direction;    // "To DCE" or "To DTE"
	UInt8       Protocol;     // FrameRelay, PPP, ...
};


typedef struct WideAreaNetworkHeader WideAreaNetworkHeader;

//wan traffic direction (same as in PeekInterface.h)
#define PEEK_WAN_DIRECTION_INVALID 0
#define PEEK_WAN_DIRECTION_DTE     1
#define PEEK_WAN_DIRECTION_DCE     2


//wan protocol definitions (same as in PeekInterface.h)
#define PEEK_WAN_PROT_INVALID  0x00        // (Not a valid protocol)
#define PEEK_WAN_PROT_0800     0x08        // TCP/IP
#define PEEK_WAN_PROT_FRLY     0x23        // Frame Relay
#define PEEK_WAN_PROT_PPP      0x10        // PPP/LCP (also used for HDLC)
#define PEEK_WAN_PROT_X25      0x25        // X.25
#define PEEK_WAN_PROT_X25E     0x29        // X.25 mod 128
#define PEEK_WAN_PROT_Q931     0x31        // Q.931
#define PEEK_WAN_PROT_SNA      0x40        // SNA
#define PEEK_WAN_PROT_SS7      0x70        // SS7
#define PEEK_WAN_PROT_IPARS    0x50        // Ipars
#define PEEK_WAN_PROT_U200     0x60        // U200

//X.25 sub protocol definitions (same as in PeekInterface.h)
#define PEEK_WAN_SUB_PROT_CIDIN    0x27    //6927 zsdlc.com
#define PEEK_WAN_SUB_PROT_AX25     0x2A    //692A zsdlc.com






// this typedef defines any possible combination of media specific info
typedef struct MediaSpecificHeaderAll
{
	MediaSpecificPrivateHeader  StdHeader;
	union
	{
		Wireless80211PrivateHeader	wireless;
		FullDuplexPrivateHeader		fullDuplex;
		WideAreaNetworkHeader		wan;
	} MediaInfo;
} MediaSpecificHeaderAll;

#define MAX_MEDIASPECIFICHEADER	sizeof(MediaSpecificHeaderAll)

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif
