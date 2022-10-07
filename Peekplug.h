// ============================================================================
//	PeekPlug.h
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#ifndef PEEKPLUG_H
#define PEEKPLUG_H

#include "WPTypes.h"
#include "PacketHeaders.h"

#ifdef __cplusplus
namespace PeekPlugin {
extern "C" {
#endif

#pragma pack(push,1)

// The API version.
#define kPluginAPIVersion			11

// -----------------------------------------------------------------------------
// Type and Constant Definitions
// -----------------------------------------------------------------------------

// Plug-in identifier (same as GUID).
typedef struct PluginID
{
	UInt32	Data1;
	UInt16	Data2;
	UInt16	Data3;
	UInt8	Data4[8];
} PluginID;

// Opaque type used by application to store context.
typedef void* PluginAppContext;

// Opaque type used by application to store context.
typedef void* PluginCaptureContext;

// Opaque type used by plug-ins to store private data.
typedef void* PluginContext;

// Other context data passed with CreateContext.
typedef void* PluginContextData;

// Plug-in context flags.
typedef UInt32	PluginContextFlags;

// Plug-in color type.
typedef COLORREF PluginColor;

// Plug-in attributes.
enum
{
	kPluginAttr_ProcessPackets			= 0x0001,
	kPluginAttr_GetPacketString			= 0x0002,
	kPluginAttr_HandlesSelection		= 0x0004,
	kPluginAttr_HandlesSummaries		= 0x0008,
	kPluginAttr_HasOptions				= 0x0010,
	kPluginAttr_Filters					= 0x0020,
	kPluginAttr_HandlesErrorPackets		= 0x0040,
	//kPluginAttr_ProvidesSummaryDescr  = 0x0080,  <-- unused
	kPluginAttr_HandlesNotify           = 0x0080,
	kPluginAttr_NameTableUpdates		= 0x0100,
	kPluginAttr_ProvidesAnalysis		= 0x0200,
	kPluginAttr_HandlesApply			= 0x0400,
	kPluginAttr_PluginAdapter			= 0x0800,
	kPluginAttr_DecodePackets			= 0x1000,
	kPluginAttr_UserDecode				= 0x2000,
	kPluginAttr_MediaSpecific			= 0x4000,
	kPluginAttr_ProcessPluginMessages	= 0x8000,
};

// Actions supported by plug-ins.
enum
{
	kPluginAction_None				= 0x0000,	// No actions
	kPluginAction_Display			= 0x0001,	// Show info in main list
	kPluginAction_Notify			= 0x0002	// Notify message
};

// Messages passed to the main routine of plug-ins.
enum
{
	kPluginMsg_Load,					//  0 PluginLoadParam
	kPluginMsg_Unload,					//  1 NULL
	kPluginMsg_ReadPrefs,				//  2 NULL
	kPluginMsg_WritePrefs,				//  3 NULL
	kPluginMsg_CreateContext,			//  4 PluginCreateContextParam
	kPluginMsg_DisposeContext,			//  5 PluginDisposeContextParam
	kPluginMsg_ProcessPacket,			//  6 PluginProcessPacketParam
	kPluginMsg_GetPacketString,			//  7 PluginGetPacketStringParam
	kPluginMsg_Apply,					//  8 PluginApplyParam
	kPluginMsg_Select,					//  9 PluginSelectParam
	kPluginMsg_Reset,					// 10 PluginResetParam
	kPluginMsg_StartCapture,			// 11 PluginStartCaptureParam
	kPluginMsg_StopCapture,				// 12 PluginStopCaptureParam
	kPluginMsg_PacketsLoaded,			// 13 PluginPacketsLoadedParam
	kPluginMsg_About,					// 14 NULL
	kPluginMsg_Options,					// 15 NULL
	kPluginMsg_Summary,					// 16 PluginSummaryParam
	kPluginMsg_Filter,					// 17 PluginFilterParam
	kPluginMsg_FilterOptions,			// 18 NULL
	kPluginMsg_SummaryDescr,			// 19 NULL
	kPluginMsg_NameTableUpdate,			// 20 PluginNameTableUpdateParam
	kPluginMsg_GetPacketAnalysis,		// 21 PluginGetPacketStringParam
	kPluginMsg_CreateNewAdapter,		// 22 PluginCreateNewAdapterParam
	kPluginMsg_GetAdapterList,			// 23 PluginGetAdapterListParam
	kPluginMsg_DeleteAdapter,			// 24 PluginDeleteAdapterParam
	kPluginMsg_SetAdapterAttribs,		// 25 PluginAdapterAttribsParam
	kPluginMsg_GetAdapterAttribs,		// 26 PluginAdapterAttribsParam
	kPluginMsg_DecodePacket,			// 27 PluginDecodePacketParam
	kPluginMsg_AdapterProperties,   	// 28 PluginAdapterPropertiesParam
	kPluginMsg_UserDecode,				// 29 PluginUserDecodeParam
	kPluginMsg_DecodersLoaded,			// 30 NULL
	kPluginMsg_IsMediaSupported,		// 31 PluginMediaSupportedParam
	kPluginMsg_ProcessPluginMessage,	// 32 PluginProcessPluginMessageParam
	kPluginMsg_HandleNotify,            // 33 PluginHandleNotifyParam
};

// Commands for apply messages.
enum
{
	kApplyMsg_Start,
	kApplyMsg_End,
	kApplyMsg_Packet
};

// Commands for select messages.
enum
{
	kSelectMsg_Start,
	kSelectMsg_End,
	kSelectMsg_Packet
};

// Commands for name table update messages.
enum
{
	kNameTableUpdateMsg_Add,
	kNameTableUpdateMsg_Edit,
	kNameTableUpdateMsg_Delete
};

// Entry types used in the LookupName, LookupEntry, and AddNameEntry callbacks.
enum
{
	kEntryType_EthernetAddr,			// 6-byte entry
	kEntryType_AppleTalkAddr,			// 4-byte entry (socket ignored)
	kEntryType_IPAddr,					// 4-byte entry
	kEntryType_DECnetAddr,				// 6-byte entry
	kEntryType_IPv6Addr,				// 16-byte entry
	kEntryType_IPPort,					// 2-byte entry
	kEntryType_ProtoSpec,				// 2-byte entry
	kEntryType_NWPort,					// 2-byte entry
	kEntryType_WirelessAddr,			// 6-byte entry
	kEntryType_IPXAddr,					// 10-byte entry
	kEntryType_WANDLCIAddr,				// 2-byte (10-bit) entry
	kEntryType_TokenRingAddr,			// 6-byte entry
};

// Host types for name lookup.
enum
{
	kHostType_Unknown,
	kHostType_Workstation,
	kHostType_Server,
	kHostType_Router,
	kHostType_Switch,
	kHostType_Repeater,
	kHostType_Printer,
	kHostType_AccessPoint
};


// AddNameEntry callback options.
enum
{
	kSetEntryName_NoMatchAdd			= 0x0001,
	kSetEntryName_NoMatchSkip			= 0x0002,
	kSetEntryName_NameMatchAdd			= 0x0010,
	kSetEntryName_NameMatchReplace		= 0x0020,
	kSetEntryName_NameMatchSkip			= 0x0040,
	kSetEntryName_AddrMatchAdd			= 0x0100,
	kSetEntryName_AddrMatchReplace		= 0x0200,
	kSetEntryName_AddrMatchSkip			= 0x0400
};

// List for DecodeOps
enum
{
	kDecodeOp_OFFS,
	kDecodeOp_LABL,
	kDecodeOp_HBIT,
	kDecodeOp_DBIT,
	kDecodeOp_BBIT,
	kDecodeOp_HBYT,
	kDecodeOp_DBYT,
	kDecodeOp_BBYT,
	kDecodeOp_HWRD,
	kDecodeOp_DWRD,
	kDecodeOp_BWRD,
	kDecodeOp_HLNG,
	kDecodeOp_DLNG,
	kDecodeOp_BLNG,
	kDecodeOp_D64B
};


// Used for NameTable calls.
typedef struct PluginNameTableEntryA
{
	const UInt8*	fEntry;
	const char*		fName;
	const char*		fGroup;
	PluginColor		fColor;
	UInt16			fEntryType;
	UInt8			fHostType;
} PluginNameTableEntryA;
typedef struct PluginNameTableEntryW
{
	const UInt8*	fEntry;
	const wchar_t*	fName;
	const wchar_t*	fGroup;
	PluginColor		fColor;
	UInt16			fEntryType;
	UInt8			fHostType;
} PluginNameTableEntryW;

#ifdef _UNICODE
typedef	PluginNameTableEntryW	PluginNameTableEntry;
#else
typedef	PluginNameTableEntryA	PluginNameTableEntry;
#endif

// Byte/count pair for summary statistics.
typedef struct ByteCountPair
{
	UInt64	fBytes;
	UInt64	fCount;
} ByteCountPair;

// Summary type sizes.
enum
{
	kPluginSummarySize_Mask				= 0x000000F0,
	kPluginSummarySize_UInt8			= 0x00000010,
	kPluginSummarySize_UInt16			= 0x00000020,
	kPluginSummarySize_UInt32			= 0x00000030,
	kPluginSummarySize_UInt64			= 0x00000040,
	kPluginSummarySize_ByteCountPair	= 0x00000050,
	kPluginSummarySize_Double			= 0x00000060
};

// Summary types.
enum
{
	kPluginSummaryType_Mask				= 0x0000000F,
	kPluginSummaryType_Date				= 0x00000001,
	kPluginSummaryType_Time				= 0x00000002,
	kPluginSummaryType_Duration			= 0x00000003,
	kPluginSummaryType_PacketCount		= 0x00000004,
	kPluginSummaryType_ByteCount		= 0x00000005,
	kPluginSummaryType_BothCount		= 0x00000006,
	kPluginSummaryType_OtherCount		= 0x00000007
};

// Summary flags.
enum
{
	kPluginSummaryFlag_Mask				= 0x00000F00,
	kPluginSummaryFlag_Ungraphable		= 0x00000100,
	kPluginSummaryFlag_IsOverTime		= 0x00000200,
	kPluginSummaryFlag_IsSampled		= 0x00000400
};

// Severity Levels for NotifyProc.
enum
{
	kNotifySeverity_Informational,
	kNotifySeverity_Minor,
	kNotifySeverity_Major,
	kNotifySeverity_Severe
};

// Media types.
enum
{
	kPluginPacketMediaType_802_3,			///< Ethernet (802.3)
	kPluginPacketMediaType_802_5,			///< Token Ring (802.5)
	kPluginPacketMediaType_Fddi,			///< FDDI
	kPluginPacketMediaType_Wan,				///< WAN
	kPluginPacketMediaType_LocalTalk,		///< LocalTalk
	kPluginPacketMediaType_Dix,				///< DEC/Intel/Xerox (DIX) Ethernet
	kPluginPacketMediaType_ArcnetRaw,		///< ARCNET (raw)
	kPluginPacketMediaType_Arcnet878_2,		///< ARCNET (878.2)
	kPluginPacketMediaType_Atm,				///< ATM
	kPluginPacketMediaType_WirelessWan,		///< Various wireless media
	kPluginPacketMediaType_Irda,			///< Infrared (IrDA)
	kPluginPacketMediaType_Bpc,				///< Broadcast Architecture
	kPluginPacketMediaType_CoWan,			///< Connection-oriented WAN
	kPluginPacketMediaType_1394,			///< IEEE 1394 (fire wire) bus
	kPluginPacketMediaType_Max				///< Not a real type, defined as an upper-bound
};

// Media sub type (sortof like physical medium)
enum
{
	kPluginPacketMediaSubType_Native,		///< Native media specified by the media type
	kPluginPacketMediaSubType_80211_b,		///< Wireless LAN network using 802.11b
	kPluginPacketMediaSubType_80211_a,		///< Wireless LAN network using 802.11a
	kPluginPacketMediaSubType_80211_gen,	///< All possible 802.11 types, a, b, g, and combinations
	kPluginPacketMediaSubType_wan_ppp,		///< PPP over a T1 or an E1
	kPluginPacketMediaSubType_wan_frameRelay, ///< Frame Relay
	kPluginPacketMediaSubType_wan_x25,		///< X.25
	kPluginPacketMediaSubType_wan_x25e,		///< X.25mod128
	kPluginPacketMediaSubType_wan_ipars,	///< IPARS
	kPluginPacketMediaSubType_wan_u200,     ///< U200
	kPluginPacketMediaSubType_wan_Q931,     ///< Q.931
	kPluginPacketMediaSubType_Max			///< Not a real type, defined as an upper-bound
};


// Flags for PluginPacket.
enum
{
	kPluginPacketFlag_Control			= 0x01,		// Control vs. data packet
	kPluginPacketFlag_CRC				= 0x02,		// Checksum error
	kPluginPacketFlag_Frame				= 0x04,		// Frame error
	kPluginPacketFlag_RouteInfo			= 0x08,		// Has routing info (Token Ring)
	kPluginPacketFlag_Oversize			= 0x10,		// Oversize error
	kPluginPacketFlag_Runt				= 0x20,		// Runt error
	kPluginPacketFlag_Trigger			= 0x40,		// Trigger packet
	kPluginPacketFlag_SNAP				= 0x80,		// SNAP packet
	kPluginPacketFlag_DroppedPackets	= 0x100,	// One or more packets were dropped prior to this packet
};

// Status flags for PluginPacket.
enum
{
	kPluginPacketStatus_Truncated		= 0x02,		// Truncated packet
	kPluginPacketStatus_Encrypted		= 0x04,		// Originally encrypted (e.g., WEP)
	kPluginPacketStatus_DecryptionError	= 0x08,		// Decryption error (e.g., WEP ICV)
	kPluginPacketStatus_Sliced			= 0x20,		// Sliced packet
	kPluginPacketStatus_ShortPreamble	= 0x40		// Short preamble
};

// Offset values for PacketGetLayer.
enum
{
	kPacketLayerType_Header				= 0x00,
	kPacketLayerType_Data				= 0x80,

	kPacketLayer_Physical				= 0x00,
	kPacketLayer_IP						= 0x01,
	kPacketLayer_UDP					= 0x02,
	kPacketLayer_TCP					= 0x03,
	kPacketLayer_ICMP					= 0x04
};

// Address types for PacketGetAddress.
enum
{
	kAddressType_SrcPhysical,
	kAddressType_DestPhysical,
	kAddressType_SrcLogical,
	kAddressType_DestLogical,
	kAddressType_BSSID,
	kAddressType_Receiver,
	kAddressType_Transmitter,
	kAddressType_Address1,
	kAddressType_Address2,
	kAddressType_Address3,
	kAddressType_Address4,
	kAddressType_WANDLCI,
};

// Context types for CreateContext.
enum
{
	kContextType_Global					= 0,
	kContextType_CaptureWindow			= 1,
	kContextType_FileWindow				= 2,
	kContextType_RemoteCaptureWindow	= 3,
	kContextType_RemoteFileWindow		= 4
};

// Select Packets flags.
enum
{
	kSelectPacketsFlag_ReplaceSelection	= 0x00,
	kSelectPacketsFlag_AddToSelection	= 0x01,
	kSelectPackets_FlagMask				= 0x0F
};

// Select Packets actions.
enum
{
	kSelectPacketsAction_PromptUser		= 0x00,
	kSelectPacketsAction_HideSelected	= 0x10,
	kSelectPacketsAction_HideUnselected	= 0x20,
	kSelectPackets_ActionMask			= 0xF0
};

// A packet.
typedef struct PluginPacket
{
	UInt64			fTimeStamp;				// Timestamp in nanoseconds
	UInt32			fProtoSpec;				// ProtoSpec ID
	UInt32			fFlags;					// CRC, frame, runt, ...
	UInt32			fStatus;				// Slicing, ...
	UInt16			fPacketLength;			// Total length of packet
	UInt16			fSliceLength;			// Sliced length of packet or zero
	const UInt8*	fMediaSpecInfoBlock;	// Media Specific Info pointer (may be NULL)
} PluginPacket;

// Bitmask definitions for the capabilites field.
#define kAppCapability_Unicode		0x00000001
#define kAppCapability_Pro			0x00000002
#define kAppCapability_RemoteAgent	0x00000004
#define kAppCapability_Beta			0x00000008
#define kAppCapability_Demo			0x00000010
#define kAppCapability_Eval			0x00000020
#define kAppCapability_VoIP			0x00000040
#define kAppCapability_Undef8		0x00000080
#define kAppCapability_Undef9		0x00000100
#define kAppCapability_Undef10		0x00000200
#define kAppCapability_Undef11		0x00000400
#define kAppCapability_Undef12		0x00000800
#define kAppCapability_Undef13		0x00001000
#define kAppCapability_Undef14		0x00002000
#define kAppCapability_Undef15		0x00004000
#define kAppCapability_Undef16		0x00008000
#define kAppCapability_Undef17		0x00010000
#define kAppCapability_Undef18		0x00020000
#define kAppCapability_Undef19		0x00040000
#define kAppCapability_Undef20		0x00080000
#define kAppCapability_Undef21		0x00100000
#define kAppCapability_Undef22		0x00200000
#define kAppCapability_Undef23		0x00400000
#define kAppCapability_Undef24		0x00800000
#define kAppCapability_Undef25		0x01000000
#define kAppCapability_Undef26		0x02000000
#define kAppCapability_Undef27		0x04000000
#define kAppCapability_Undef28		0x08000000
#define kAppCapability_Undef29		0x10000000
#define kAppCapability_Undef30		0x20000000
#define kAppCapability_Undef31		0x40000000
#define kAppCapability_Undef32		0x80000000

// -----------------------------------------------------------------------------
// XML Tags for Plug-in Adapters
// -----------------------------------------------------------------------------

#define kAdapterTag_StartCaptureText	_T("StartCaptureText")
#define kAdapterTag_StopCaptureText		_T("StopCaptureText")
#define kAdapterEle_Group				_T("Group")
#define kAdapterEle_Adapter				_T("Adapter")
#define kAdapterTag_Name				_T("Name")
#define kAdapterTag_ID					_T("ID")
#define kAdapterTag_Speed				_T("LinkSpeed")
#define kAdapterTag_DefaultSpeed		_T("DefaultLinkSpeed")
#define kAdapterTag_MediaType			_T("MediaType")
#define kAdapterTag_MediaSubType		_T("MediaSubType")
#define kAdapterTag_MediaDesc			_T("MediaDesc")
#define kAdapterTag_Deletable			_T("Deletable")
#define kAdapterVal_False				_T("false")
#define kAdapterVal_True				_T("true")
#define kAdapterTag_Address				_T("Address")
#define kAdapterTag_PluginID			_T("PluginID")
#define kAdapterTag_Device				_T("Device")		// A field in the adapter list
#define kAdapterTag_Properties			_T("Properties")	// Supports properties
#define kAdapterTag_Continuous			_T("Continuous")	// Supports continuous capture (can be used to monitor)

// Wireless adapter attributes.
#define kAdapterTag_CurrentSetting		_T("Setting")		// One of the adapter tags below
#define kAdapterTag_Channel				_T("Channel")		// Channel
#define kAdapterTag_ChannelNumber		_T("ChannelNumber")	// Channel #
#define kAdapterTag_ChannelFreq			_T("ChannelFreq")	// Channel frequency
#define kAdapterTag_ChannelBand			_T("ChannelBand")	// Channel band
#define kAdapterTag_ESSID				_T("ESSID")			// ESSID (name)
#define kAdapterTag_BSSID				_T("BSSID")			// BSSID (MAC address)
#define kAdapterTag_ChannelScan			_T("Scanning")		// Children are kAdapterTag_Channel with Enabled (=true/false) and Duration (in ms) attributes
#define kAdapterTag_Enabled				_T("Enabled")
#define kAdapterTag_Duration			_T("Duration")
#define kAdapterTag_WEPKeys				_T("WEP")			// (set/get) contains the name of the keyset as an attibute (kAdapterTag_Name)
															// (set) children are kAdapterTag_Key with attribute kAdapterTag_KeyNum and WEP key in hex as value
#define kAdapterTag_Key					_T("Key")
#define kAdapterTag_KeyNum				_T("KeyNum")

// -----------------------------------------------------------------------------
// Callbacks
// -----------------------------------------------------------------------------

#if TARGET_OS_WIN32
	#define PeekPlugCallback_( inReturnType, inFunctionName )	inReturnType (WINAPI * inFunctionName )
#elif TARGET_OS_MAC
	#define PeekPlugCallback_( inReturnType, inFunctionName )	pascal inReturnType (* inFunctionName )
#elif _LINUX
	#define PeekPlugCallback_( inReturnType, inFunctionName )	inReturnType (* inFunctionName )
#endif

// Protocol callbacks.
typedef PeekPlugCallback_( int,		GetProtocolNameProc		)
	(
		UInt32		inProtocol,
		wchar_t*	outString
	);

typedef PeekPlugCallback_( int, 	GetProtocolLongNameProc	)
	(
		UInt32		inProtocol,
		wchar_t*	outString
	);

typedef PeekPlugCallback_( int,		GetProtocolHierNameProc	)
	(
		UInt32		inProtocol,
		wchar_t*	outString
	);

typedef PeekPlugCallback_( int,		GetProtocolParentProc	)
	(
		UInt32		inProtocol,
		UInt32*		outProtocolParent
	);

typedef PeekPlugCallback_( int,		GetProtocolColorProc	)
	(
		UInt32			inProtocol,
		PluginColor*	outColor
	);

typedef PeekPlugCallback_( int,		IsDescendentOfProc		)
	(
		UInt32			inSubProtocol,
		const UInt32*	inParentArray,
		SInt32			inParentCount,
		UInt32			*outMatchID
	);

// Name table callbacks.
typedef PeekPlugCallback_( int,		LookupNameProc			)
	(
		PluginNameTableEntryW*	ioEntry
	);

typedef PeekPlugCallback_( int,		LookupEntryProc			)
	(
		PluginNameTableEntryW*	ioEntry
	);

typedef PeekPlugCallback_( int,		AddNameEntryProc		)
	(
		const PluginNameTableEntryW*	inEntry,
		UInt32							inOptions
	);

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		InvokeNameEditDialogProc)
	(
		const PluginNameTableEntryW*	inEntry
	);
#endif

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		ResolveAddressProc		)
	(
		UInt8*	inAddress,
		UInt16	inAddressType
	);
#endif

// Summary callbacks.
typedef PeekPlugCallback_( int,		SummaryGetEntryProc		)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		const wchar_t*			inLabel,
		const wchar_t*			inGroup,
		UInt32*					outType,
		void**					outData,
		UInt8*					outSource
	);

typedef PeekPlugCallback_( int,		SummaryModifyEntryProc	)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		const wchar_t*			inLabel,
		const wchar_t*			inGroup,
		UInt32					inType,
		void*					inData
	);

// Packet parsing callbacks.
typedef PeekPlugCallback_( UInt8 *,	PacketGetLayerProc		)
	(
		UInt8				inLayerType,
		UInt8				inMediaType,
		UInt8				inMediaSubType,
		const PluginPacket*	inPacket,
		const UInt8*		inPacketData,
		UInt16*				ioBytesLeft
	);

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( UInt8 *,	PacketGetDataLayerProc	)
	(
		UInt32				inProtoSpec,
		UInt8				inMediaType,
		UInt8				inMediaSubType,
		const PluginPacket*	inPacket,
		const UInt8*		inPacketData,
		UInt16*				ioBytesLeft,
		UInt32*				outSourceProtoSpec
	);
#endif

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( UInt8 *,	PacketGetHeaderLayerProc)
	(
		UInt32				inLayerType,
		UInt8				inMediaType,
		UInt8				inMediaSubType,
		const PluginPacket*	inPacket,
		const UInt8*		inPacketData,
		UInt16*				ioBytesLeft,
		UInt32*				outSourceProtoSpec
	);
#endif

typedef PeekPlugCallback_( int,		PacketGetAddressProc	)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		UInt8					inAddressSelector,
		UInt8					inMediaType,
		UInt8					inMediaSubType,
		const PluginPacket*		inPacket,
		const UInt8*			inPacketData,
		UInt64					inPacketNumber,
		UInt8*					outAddress,
		UInt16*					outAddressType
	);

// Preferences callbacks.
typedef PeekPlugCallback_( int,		PrefsGetValueProc		)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		const wchar_t*			inName,
		const void*				outData,
		UInt32*					ioLength
	);

typedef PeekPlugCallback_( int,		PrefsSetValueProc		)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		const wchar_t*			inName,
		const void*				inData,
		UInt32					inLength
	);

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		PrefsGetPrefsPathProc	)
	(
		wchar_t*	outString
	);
#endif

// Packet list callbacks.
typedef PeekPlugCallback_( int,		InsertPacketProc		)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		const PluginPacket*		inPacket,
		const UInt8*			inPacketData,
		UInt8					inMediaType,
		UInt8					inMediaSubType,
		UInt32					inReserved
	);

typedef PeekPlugCallback_( int,		SelectPacketsProc		)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		UInt32					inPacketCount,
		UInt64*					inPacketArray,
		UInt32					inFlags
	);

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		SelectPacketsExProc		)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		const UInt8*			inSrcAddr,
		UInt16					inSrcAddrType,
		const UInt8*			inDestAddr,
		UInt16					inDestAddrType,
		UInt16					inSrcPort,
		UInt16					inDestPort,
		UInt16					inPortTypes,
		bool					inBothDirections,
		UInt32					inFlags
	);
#endif

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		GetPacketCountProc		)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		UInt32*					outCount
	);
#endif

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		GetFirstPacketIndexProc	)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		UInt32*					outIndex
	);
#endif

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		GetPacketProc			)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		UInt32					inIndex,
		UInt64*					outPacketNumber,
		const PluginPacket**	outPacket,
		const UInt8**			outPacketData
	);
#endif

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		ClaimPacketStringProc	)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		UInt64					inPacketNumber,
		bool					inExpert
	);
#endif

// Decoder callbacks.
#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		DecodeOpProc			)
	(
		PluginContext			inDecodeContext,
		PluginContext			inDecodeState,
		int						inOp,
		UInt32					inValue,
		UInt32					inGlobal,
		UInt8					inStyleValue,
		UInt8					inStyleLabel,
		wchar_t*				pszString,
		wchar_t*				pszSummary
	 );
#endif

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		AddUserDecodeProc		)
	(
		const wchar_t*			pszFuncName
	);
#endif

// Plug-in UI callbacks.
#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		AddTabProc				)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		const wchar_t*			inTabName,
		const wchar_t*			inWindowClass,
		void**					outTabWnd
	);
#endif

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		AddTabWithGroupProc		)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		const wchar_t*			inTabName,
		const wchar_t*			inGroupName,
		const wchar_t*			inWindowClass,
		void**					outTabWnd
	);
#endif

// Misc. callbacks.
typedef PeekPlugCallback_( int,		NotifyProc				)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		UInt64					inTimeStamp,
		UInt8					inSeverity,
		const wchar_t*			inShortString,
		const wchar_t*			inLongString
	);

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		SendPluginMessageProc	)
	(
		PluginAppContext		inAppContext,
		PluginCaptureContext	inCaptureContext,
		UInt8*					inParamData,
		UInt32					inParamDataLength
	);
#endif

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		MakeFilterProc			)
	(
		const UInt8*	inSrcAddr,
		UInt16			inSrcAddrType,
		const UInt8*	inDestAddr,
		UInt16			inDestAddrType,
		UInt16			inSrcPort,
		UInt16			inDestPort,
		UInt16			inPortTypes,
		bool			inBothDirections
	);
#endif

#if TARGET_OS_WIN32
typedef PeekPlugCallback_( int,		GetAppResourcePathProc	)
	(
		wchar_t*	outAppResourcePath
	);
#endif

typedef PeekPlugCallback_( int,		SendPacketProc			)
	(
		const UInt8*	inPacketData,
		UInt16			inPacketLength
	);

#if TARGET_OS_MAC
typedef PeekPlugCallback_( void,	EventDispatchProc		)
	(
		const EventRecord*	inEvent
	);
#endif

#if TARGET_OS_WIN32 || _LINUX
	// Callback names for importing from Peek.
	#define kExportName_GetProtocolName			_T("GetProtocolNameCallback")
	#define kExportName_GetProtocolLongName		_T("GetProtocolLongNameCallback")
	#define kExportName_GetProtocolHierName		_T("GetProtocolHierNameCallback")
	#define kExportName_GetProtocolParent		_T("GetProtocolParentCallback")
	#define kExportName_GetProtocolColor		_T("GetProtocolColorCallback")
	#define kExportName_IsDescendentOf			_T("IsDescendentOfCallback")
	#define kExportName_LookupName				_T("LookupNameCallback")
	#define kExportName_LookupEntry				_T("LookupEntryCallback")
	#define kExportName_AddNameEntry			_T("AddNameEntryCallback")
	#define kExportName_InvokeNameEditDialog	_T("InvokeNameEditDialogCallback")
	#define kExportName_ResolveAddress			_T("ResolveAddressCallback")
	#define kExportName_SummaryGetEntry			_T("SummaryGetEntryCallback")
	#define kExportName_SummaryModifyEntry		_T("SummaryModifyEntryCallback")
	#define kExportName_PacketGetLayer			_T("PacketGetLayerCallback")
	#define kExportName_PacketGetDataLayer		_T("PacketGetDataLayerCallback")
	#define kExportName_PacketGetHeaderLayer	_T("PacketGetHeaderLayerCallback")
	#define kExportName_PacketGetAddress		_T("PacketGetAddressCallback")
	#define kExportName_PrefsGetValue			_T("PrefsGetValueCallback")
	#define kExportName_PrefsSetValue			_T("PrefsSetValueCallback")
	#define kExportName_PrefsGetPrefsPath		_T("PrefsGetPrefsPathCallback")
	#define kExportName_InsertPacket			_T("InsertPacketCallback")
	#define kExportName_SelectPackets			_T("SelectPacketsCallback")
	#define kExportName_SelectPacketsEx			_T("SelectPacketsExCallback")
	#define kExportName_GetPacketCount			_T("GetPacketCountCallback")
	#define kExportName_GetFirstPacketIndex		_T("GetFirstPacketIndexCallback")
	#define kExportName_GetPacket				_T("GetPacketCallback")
	#define kExportName_ClaimPacketString		_T("ClaimPacketStringCallback")
	#define kExportName_DecodeOp				_T("DecodeOpCallback")
	#define kExportName_CallUserDecodeCallback	_T("CallUserDecodeCallback")
	#define kExportName_AddUserDecode			_T("AddUserDecodeCallback")
	#define kExportName_AddTab					_T("AddTabCallback")
	#define kExportName_AddTabWithGroup			_T("AddTabWithGroupCallback")
	#define kExportName_Notify					_T("NotifyCallback")
	#define kExportName_SendPluginMessage		_T("SendPluginMessageCallback")
	#define kExportName_MakeFilter				_T("MakeFilterCallback")
	#define kExportName_GetAppResourcePath		_T("GetAppResourcePathCallback")
	#define kExportName_SendPacket				_T("SendPacketCallback")

	typedef void *	ClientAppDataPtr;
#elif TARGET_OS_MAC	// end TARGET_OS_WIN32 || _LINUX
	struct PeekPlugCallbacks
	{
		GetProtocolNameProc			mGetProtocolNameProc;
		GetProtocolLongNameProc		mGetProtocolLongNameProc;
		GetProtocolHierNameProc		mGetProtocolHierNameProc;
		GetProtocolParentProc		mGetProtocolParentProc;
		GetProtocolColorProc		mGetProtocolColorProc;
		IsDescendentOfProc			mIsDescendentOfProc;
		NotifyProc					mNotifyProc;
		LookupNameProc				mLookupNameProc;
		LookupEntryProc				mLookupEntryProc;
		AddNameEntryProc			mAddNameEntryProc;
		SendPacketProc				mSendPacketProc;
		SummaryGetEntryProc			mSummaryGetEntryProc;
		SummaryModifyEntryProc		mSummaryModifyEntryProc;
		PacketGetLayerProc			mPacketGetLayerProc;
		PacketGetAddressProc		mPacketGetAddressProc;
		PrefsGetValueProc			mPrefsGetValueProc;
		PrefsSetValueProc			mPrefsSetValueProc;
		InsertPacketProc			mInsertPacketProc;
		SelectPacketsProc			mSelectPacketsProc;
		EventDispatchProc			mEventDispatchProc;
	};

	struct ClientAppData
	{
		PeekPlugCallbacks	mCallbacks;
		CFBundleRef			mPluginBundle;
	};
	typedef ClientAppData *	ClientAppDataPtr;
#endif	// end TARGET_OS_MAC

// -----------------------------------------------------------------------------
// Message structures.
// -----------------------------------------------------------------------------

// kPluginMsg_Load parameters.
#define kPluginNameMaxLength				256
#define kPluginLoadErrorMessageMaxLength	1024
typedef struct PluginLoadParamA
{
	UInt32				fAPIVersion;
	UInt32				fAppCapabilities;
	char*				fName;
	PluginID			fID;
	UInt16				fAttributes;
	UInt16				fSupportedActions;
	UInt16				fDefaultActions;
	UInt32				fSupportedCount;
	UInt32*				fSupportedProtoSpecs;
	ClientAppDataPtr	fClientAppData;
	PluginAppContext	fAppContextData;	// Plug-in retains to give back to callbacks
	char*				fLoadErrorMessage;
	LCID				fLocaleId;
} PluginLoadParamA;
typedef struct PluginLoadParamW
{
	UInt32				fAPIVersion;
	UInt32				fAppCapabilities;
	wchar_t*			fName;
	PluginID			fID;
	UInt16				fAttributes;
	UInt16				fSupportedActions;
	UInt16				fDefaultActions;
	UInt32				fSupportedCount;
	UInt32*				fSupportedProtoSpecs;
	ClientAppDataPtr	fClientAppData;
	PluginAppContext	fAppContextData;	// Plug-in retains to give back to callbacks
	wchar_t*			fLoadErrorMessage;
	LCID				fLocaleId;
} PluginLoadParamW;
#ifdef _UNICODE
typedef PluginLoadParamW	PluginLoadParam;
#else
typedef PluginLoadParamA	PluginLoadParam;
#endif

// kPluginMsg_IsMediaSupported parameters.
typedef struct PluginMediaSupportedParam
{
	UInt8				fMediaType;
	UInt8				fMediaSubType;
} PluginMediaSupportedParam;

// kPluginMsg_ProcessPacket parameters.
typedef struct PluginProcessPacketParam
{
	const PluginPacket*	fPacket;
	const UInt8*		fPacketData;
	UInt64				fPacketNumber;
	UInt8				fMediaType;
	UInt8				fMediaSubType;
	UInt32				fProtoSpecMatched;
	PluginContext		fContext;
} PluginProcessPacketParam;

// kPluginMsg_ProcessPluginMessage parameters.
typedef struct PluginProcessPluginMessageParam
{
	const UInt8*		fData;
	UInt32				fDataLen;
	UInt32				fResult;
	PluginContext		fContext;
} PluginProcessPluginMessageParam;

// kPluginMsg_DecodePacket parameters.
typedef struct PluginDecodePacketParam
{
	const PluginPacket*	fPacket;
	const UInt8*		fPacketData;
	UInt64				fPacketNumber;
	UInt8				fMediaType;
	UInt8				fMediaSubType;
	UInt32				fProtoSpecMatched;
	PluginContext		fContext;
} PluginDecodePacketParam;

// kPluginMsg_UserDecode parameters.
typedef struct PluginUserDecodeParamA
{
	const PluginPacket*	fPacket;
	const UInt8*		fPacketData;
	UInt64				fPacketNumber;
	UInt8				fMediaType;
	UInt8				fMediaSubType;
	UInt32				fProtoSpecMatched;
	PluginContext		fContext;
	char*				fFunctionName;
	PluginContext		fDecodeContext;
	PluginContext		fDecodeState;
} PluginUserDecodeParamA;
typedef struct PluginUserDecodeParamW
{
	const PluginPacket*	fPacket;
	const UInt8*		fPacketData;
	UInt64				fPacketNumber;
	UInt8				fMediaType;
	UInt8				fMediaSubType;
	UInt32				fProtoSpecMatched;
	PluginContext		fContext;
	wchar_t*			fFunctionName;
	PluginContext		fDecodeContext;
	PluginContext		fDecodeState;
} PluginUserDecodeParamW;

#ifdef _UNICODE
typedef PluginUserDecodeParamW	PluginUserDecodeParam;
#else
typedef PluginUserDecodeParamA	PluginUserDecodeParam;
#endif

// kPluginMsg_GetPacketString parameters.
typedef struct PluginGetPacketStringParamA
{
	const PluginPacket*	fPacket;
	const UInt8*		fPacketData;
	UInt64				fPacketNumber;
	UInt8				fMediaType;
	UInt8				fMediaSubType;
	UInt32				fProtoSpecMatched;
	char*				fString;
	PluginColor			fColor;
	PluginContext		fContext;
} PluginGetPacketStringParamA;
typedef struct PluginGetPacketStringParamW
{
	const PluginPacket*	fPacket;
	const UInt8*		fPacketData;
	UInt64				fPacketNumber;
	UInt8				fMediaType;
	UInt8				fMediaSubType;
	UInt32				fProtoSpecMatched;
	wchar_t*			fString;
	PluginColor			fColor;
	PluginContext		fContext;
} PluginGetPacketStringParamW;

#ifdef _UNICODE
typedef PluginGetPacketStringParamW	PluginGetPacketStringParam;
#else
typedef PluginGetPacketStringParamA	PluginGetPacketStringParam;
#endif

// kPluginMsg_Apply parameters.
typedef struct PluginApplyParam
{
	const PluginPacket*	fPacket;
	const UInt8*		fPacketData;
	UInt64				fPacketNumber;
	UInt8				fMediaType;
	UInt8				fMediaSubType;
	UInt32				fProtoSpecMatched;
	UInt16				fCommand;
	UInt32				fPrivateData;
	PluginContext		fContext;
} PluginApplyParam;

// kPluginMsg_Select parameters.
typedef struct PluginSelectParam
{
	const PluginPacket*	fPacket;
	const UInt8*		fPacketData;
	UInt64				fPacketNumber;
	UInt8				fMediaType;
	UInt8				fMediaSubType;
	UInt32				fProtoSpecMatched;
	UInt16				fCommand;
	UInt32				fPrivateData;
	PluginContext		fContext;
} PluginSelectParam;

// kPluginMsg_Reset parameters.
typedef struct PluginResetParamA
{
	PluginContext		fContext;
	const char*			fPluginAdapterID;
} PluginResetParamA;
typedef struct PluginResetParamW
{
	PluginContext		fContext;
	const wchar_t*		fPluginAdapterID;
} PluginResetParamW;

#ifdef _UNICODE
typedef	PluginResetParamW	PluginResetParam;
#else
typedef	PluginResetParamA	PluginResetParam;
#endif

// kPluginMsg_StartCapture parameters.
typedef struct PluginStartCaptureParam
{
	PluginContext		fContext;
} PluginStartCaptureParam;

// kPluginMsg_StopCapture parameters.
typedef struct PluginStopCaptureParam
{
	PluginContext		fContext;
} PluginStopCaptureParam;

// kPluginMsg_GetAdapterList parameters.
typedef struct PluginGetAdapterListParamA
{
	const char*			fOutXMLAdapterList;
	UInt32				fOutXMLStreamLength;
} PluginGetAdapterListParamA;
typedef struct PluginGetAdapterListParamW
{
	const wchar_t*		fOutXMLAdapterList;
	UInt32				fOutXMLStreamLength;
} PluginGetAdapterListParamW;

#ifdef _UNICODE
typedef	PluginGetAdapterListParamW	PluginGetAdapterListParam;
#else
typedef	PluginGetAdapterListParamA	PluginGetAdapterListParam;
#endif

// kPluginMsg_DeleteAdapter parameters.
typedef struct PluginDeleteAdapterParamA
{
	const char*		fInDeleteID;
} PluginDeleteAdapterParamA;
typedef struct PluginDeleteAdapterParamW
{
	const wchar_t*		fInDeleteID;
} PluginDeleteAdapterParamW;

#ifdef _UNICODE
typedef	PluginDeleteAdapterParamW	PluginDeleteAdapterParam;
#else
typedef	PluginDeleteAdapterParamA	PluginDeleteAdapterParam;
#endif

// kPluginMsg_AdapterProperties parameters.
typedef struct PluginAdapterPropertiesParamA
{
	const char*			fInAdapterID;
} PluginAdapterPropertiesParamA;
typedef struct PluginAdapterPropertiesParamW
{
	const wchar_t*		fInAdapterID;
} PluginAdapterPropertiesParamW;

#ifdef _UNICODE
typedef	PluginAdapterPropertiesParamW	PluginAdapterPropertiesParam;
#else
typedef	PluginAdapterPropertiesParamA	PluginAdapterPropertiesParam;
#endif

// kPluginMsg_SetAdapterAttribs, kPluginMsg_GetAdapterAttribs parameters.
typedef struct PluginAdapterAttribsParamA
{
	const char*			fAdapterID;
	const char*			fInParamTagStream;
	UInt32				fInParamTagStreamLen;
	const char*			fOutParamTagStream;
	UInt32				fOutParamTagStreamLen;
} PluginAdapterAttribsParamA;
typedef struct PluginAdapterAttribsParamW
{
	const wchar_t*		fAdapterID;
	const wchar_t*		fInParamTagStream;
	UInt32				fInParamTagStreamLen;
	const wchar_t*		fOutParamTagStream;
	UInt32				fOutParamTagStreamLen;
} PluginAdapterAttribsParamW;

#ifdef _UNICODE
typedef	PluginAdapterAttribsParamW	PluginAdapterAttribsParam;
#else
typedef	PluginAdapterAttribsParamA	PluginAdapterAttribsParam;
#endif

// kPluginMsg_PacketsLoaded parameters.
typedef struct PluginPacketsLoadedParam
{
	PluginContext		fContext;
} PluginPacketsLoadedParam;

// kPluginMsg_Summary parameters.
typedef struct PluginSummaryParam
{
	PluginContext		fContext;
} PluginSummaryParam;

// kPluginMsg_CreateContext parameters.
typedef struct PluginCreateContextParam
{
	PluginContext*			fContextPtr;
	PluginCaptureContext	fCaptureContext;
	PluginContextData		fContextData;
	PluginContextFlags		fContextFlags;
} PluginCreateContextParam;

// kPluginMsg_DisposeContext parameters.
typedef struct PluginDisposeContextParam
{
	PluginContext		fContext;
} PluginDisposeContextParam;

// kPluginMsg_Filter parameters.
typedef struct PluginFilterParam
{
	const PluginPacket*	fPacket;
	const UInt8*		fPacketData;
	UInt8				fMediaType;
	UInt8				fMediaSubType;
	UInt32				fProtoSpecMatched;
	SInt16				fBytesAccepted;
	PluginContext		fContext;
} PluginFilterParam;

// kPluginMsg_NameTableUpdate parameters.
typedef struct PluginNameTableUpdateParamA
{
	PluginNameTableEntryA*	fEntry;
	UInt16					fCommand;
} PluginNameTableUpdateParamA;
typedef struct PluginNameTableUpdateParamW
{
	PluginNameTableEntryW*	fEntry;
	UInt16					fCommand;
} PluginNameTableUpdateParamW;

#ifdef _UNICODE
typedef	PluginNameTableUpdateParamW	PluginNameTableUpdateParam;
#else
typedef	PluginNameTableUpdateParamA	PluginNameTableUpdateParam;
#endif

// kPluginMsg_CreateNewAdapter parameters.
typedef struct PluginCreateNewAdapterParamA
{
	char*				fOutSelectedAdapterTag;
	UInt16				fInMaxLength;
} PluginCreateNewAdapterParamA;
typedef struct PluginCreateNewAdapterParamW
{
	wchar_t*			fOutSelectedAdapterTag;
	UInt16				fInMaxLength;
} PluginCreateNewAdapterParamW;

#ifdef _UNICODE
typedef	PluginCreateNewAdapterParamW	PluginCreateNewAdapterParam;
#else
typedef	PluginCreateNewAdapterParamA	PluginCreateNewAdapterParam;
#endif

// kPluginMsg_HandleNotify parameters.
typedef struct PluginHandleNotifyParamA
{
	UInt64               fTimeStamp;
	UInt8                fSeverity;
	const char*	         fShortMessage;
	const char*	         fLongMessage;
	UInt32               fFlags;
	PluginContext        fContext;
} PluginHandleNotifyParamA;
typedef struct PluginHandleNotifyParamW
{
	UInt64               fTimeStamp;
	UInt8                fSeverity;
	const wchar_t*       fShortMessage;
	const wchar_t*       fLongMessage;
	UInt32               fFlags;
	PluginContext        fContext;
} PluginHandleNotifyParamW;

#ifdef _UNICODE
typedef	PluginHandleNotifyParamW	PluginHandleNotifyParam;
#else
typedef	PluginHandleNotifyParamA	PluginHandleNotifyParam;
#endif

// Union of message parameter blocks
typedef union PluginParamBlock
{
	PluginLoadParam					uLoad;						// kPluginMsg_Load
	PluginCreateContextParam		uCreateContext;				// kPluginMsg_CreateContext
	PluginDisposeContextParam		uDisposeContext;			// kPluginMsg_DisposeContext
	PluginProcessPacketParam		uProcessPacket;				// kPluginMsg_ProcessPacket
	PluginGetPacketStringParam		uGetPacketString;			// kPluginMsg_GetPacketString
	PluginApplyParam				uApply;						// kPluginMsg_Apply
	PluginSelectParam				uSelect;					// kPluginMsg_Select
	PluginResetParam				uReset;						// kPluginMsg_Reset
	PluginStartCaptureParam			uStartCapture;				// kPluginMsg_StartCatpure
	PluginStopCaptureParam			uStopCapture;				// kPluginMsg_StopCapture
	PluginPacketsLoadedParam		uPacketsLoaded;				// kPluginMsg_PacketsLoaded
	PluginSummaryParam				uSummary;					// kPluginMsg_Summary
	PluginFilterParam				uFilter;					// kPluginMsg_Filter
	PluginNameTableUpdateParam		uNameTableUpdate;			// kPluginMsg_NameTableUpdate
	PluginGetAdapterListParam		uAdapterList;				// kPluginMsg_GetAdapterList
	PluginCreateNewAdapterParam 	uCreateAdapter;				// kPluginMsg_CreateNewAdapter
	PluginDeleteAdapterParam		uDeleteAdapter;				// kPluginMsg_DeleteAdapter
	PluginAdapterAttribsParam   	uAdapterAttribs;			// kPluginMsg_SetAdapterAttribs, kPluginMsg_GetAdapterAttribs
	PluginDecodePacketParam			uDecodePacket;				// kPluginMsg_DecodePacket
	PluginAdapterPropertiesParam	uAdapterProperties;			// kPluginMsg_AdapterProperties
	PluginUserDecodeParam			uUserDecode;				// kPluginMsg_UserDecode
	PluginMediaSupportedParam		uMediaSupported;			// kPluginMsg_MediaSupported
	PluginProcessPluginMessageParam	uProcessPluginMessage;		// kPluginMsg_ProcessPluginMessage
    PluginHandleNotifyParam         uHandleNotify;				// kPluginMsg_HandleNotify
} PluginParamBlock;

// -----------------------------------------------------------------------------
// Return Codes.
// -----------------------------------------------------------------------------

#define PLUGIN_RESULT_SUCCESS		0
#define PLUGIN_RESULT_ERROR			-1
#define PLUGIN_RESULT_DISABLED		-2

// Return when processing kPluginMsg_Apply and kPluginMsg_Select during the
// kApplyMsg_Start/kSelectMsg_Start phase to indicate whether to continue the
// operation.
#define PLUGIN_START_CONTINUE		0
#define PLUGIN_START_CANCEL			-1

// Return when processing kPluginMsg_Apply, kPluginMsg_Filter, and
// kPluginMsg_Select to indicate whether to include a packet in the operation.
#define PLUGIN_PACKET_ACCEPT		0
#define PLUGIN_PACKET_REJECT		-1

// When processing kPluginMsg_Filter, assign to
// TPluginFilterParam.fBytesAccepted to indicate the entire length of the
// packet should be accepted. In other words, no filter slicing should take
// place.
#define PLUGIN_ACCEPT_WHOLE_PACKET	0

// Entry point names to export from the plug-in module.
#define kPluginMainProc				"PlugInMain"
#define kPluginInitProc				"PlugInInitialize"

// The main entry point of a plug-in through which all messages are received.
#if TARGET_OS_WIN32
typedef int (WINAPI *PluginProc)( SInt16 inMessage, PluginParamBlock* ioParams );
#elif TARGET_OS_MAC
typedef pascal int (*PluginProc)( SInt16 inMessage, PluginParamBlock *ioParams );
#endif

#define CallPluginProc(userRoutine, inMessage, ioParams)		\
		((PluginProc)(userRoutine))((inMessage), (ioParams))

#pragma pack(pop)

#ifdef __cplusplus
}	// end extern "C"
}	// end namespace PeekPlugin
#endif

#endif	// end PEEKPLUG_H
