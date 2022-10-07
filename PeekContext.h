// =============================================================================
//	PeekContext.h
//		interface for the CPeekContext class.
// =============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#pragma once

#include "PeekPlugin.h"
#include "PeekApp.h"

using namespace PeekPlugin;


///////////////////////////////////////////////////////////////////////////////
//		CPeekContext
///////////////////////////////////////////////////////////////////////////////

class CPeekContext
{
protected:
	PluginCaptureContext	m_pCaptureContext;
	PluginContextFlags		m_ContextFlags;
	HWND					m_hCaptureWindow;

public:
	;				CPeekContext() : m_pCaptureContext( NULL ), m_ContextFlags( 0 ), m_hCaptureWindow( NULL ) {}
	virtual			~CPeekContext() {}

	virtual int		Init( PluginCreateContextParam* ioParams );
	virtual int		Term();
	virtual PluginCaptureContext	GetCaptureContext() { return m_pCaptureContext; }
	virtual	PluginContextFlags		GetContextType() { return (m_ContextFlags && 0xFF); }
	virtual HWND	GetCaptureWindow() { return m_hCaptureWindow; }
	virtual CString	GetCaptureTitle();

	virtual int		OnReset( PluginResetParam* ioParams );
	virtual int		OnStartCapture( PluginStartCaptureParam* ioParams );
	virtual int		OnStopCapture( PluginStopCaptureParam* ioParams );
	virtual int		OnProcessPacket( PluginProcessPacketParam* ioParams );
	virtual int		OnGetPacketString( PluginGetPacketStringParam* ioParams );
	virtual int		OnApply( PluginApplyParam* ioParams );
	virtual int		OnSelect( PluginSelectParam* ioParams );
	virtual int		OnPacketsLoaded( PluginPacketsLoadedParam* ioParams );
	virtual int		OnSummary( PluginSummaryParam* ioParams );
	virtual int		OnFilter( PluginFilterParam* ioParams );
	virtual int		OnGetPacketAnalysis( PluginGetPacketStringParam* ioParams );
	virtual int		OnDecodePacket( PluginDecodePacketParam* ioParams );
	virtual int		OnProcessPluginMessage( PluginProcessPluginMessageParam* ioParams );
	virtual int		OnHandleNotify( PluginHandleNotifyParam* ioParams );

	// Utility functions.
	bool			LoadString( UInt32 inID, TCHAR* outString, int nBufSize ) const;
	bool			IsMACFrame( const UInt8* inPacketData ) { return CPeekApp::IsMACFrame( inPacketData ); }
	UInt16			GetSourceRouteInfoLength( const PluginPacket* inPacket, const UInt8* inPacketData ) {
						return CPeekApp::GetSourceRouteInfoLength( inPacket, inPacketData );
					}
	UInt16			GetPacketActualLength( const PluginPacket* inPacket ) {
						return CPeekApp::GetPacketActualLength( inPacket );
					}
	int				GetTCPUDPInfo( UInt32 inProtoSpecMatched, const PluginPacket* inPacket,
							const UInt8* inPacketData, UInt8 inMediaType, UInt8 inMediaSubType,
							const UInt8** outHdrData, UInt16* outHdrBytes, const UInt8** outData,
							UInt16* outDataBytes, UInt32* outDeliveryProtocol ) {
						return CPeekApp::GetTCPUDPInfo( inProtoSpecMatched, inPacket, inPacketData,
							inMediaType, inMediaSubType, outHdrData, outHdrBytes, outData,
							outDataBytes, outDeliveryProtocol );
					}
	int				GetIPInfo( UInt32 inProtoSpecMatched, const PluginPacket* inPacket,
							const UInt8* inPacketData, UInt8 inMediaType, UInt8 inMediaSubType,
							const UInt8** outIPHdrData, UInt16* outIPHdrBytes,
							const UInt8** outIPData, UInt16* outIPDataBytes,
							UInt32* outDeliveryProtocol ) {
						return CPeekApp::GetIPInfo( inProtoSpecMatched, inPacket, inPacketData,
							inMediaType, inMediaSubType, outIPHdrData, outIPHdrBytes, outIPData,
							outIPDataBytes, outDeliveryProtocol );
					}

	// Wrappers for callback functions.
	int				DoGetProtocolName( UInt32 inProtocol, TCHAR* outString );
	int				DoGetProtocolLongName( UInt32 inProtocol, TCHAR* outString );
	int				DoGetProtocolHierName( UInt32 inProtocol, TCHAR* outString );
	int				DoGetProtocolParent( UInt32 inProtocol, UInt32* outProtocolParent );
	int				DoGetProtocolColor( UInt32 inProtocol, COLORREF* outColor );
	int				DoIsDescendentOf( UInt32 inSubProtocol, const UInt32* inParentArray,
						SInt32 inParentCount, UInt32* outMatchID );
	int				DoNotify( UInt64 inTimeStamp, UInt8 inSeverity, const TCHAR* inShortString,
						const TCHAR* inLongString );
	int				DoLookupName( const UInt8* inEntry, SInt16 inEntryType, TCHAR* outName, UInt8* outType );
	int				DoLookupName( PluginNameTableEntry* ioEntry );
	int				DoLookupEntry( const TCHAR* inName, SInt16 inEntryType, UInt8* outEntry );
	int				DoLookupEntry( PluginNameTableEntry* ioEntry );
	int				DoAddNameEntry( const TCHAR* inName, const TCHAR* inGroup, const UInt8* inEntry,
						SInt16 inEntryType, UInt16 inOptions );
	int				DoAddNameEntry( const PluginNameTableEntry* inEntry, UInt16 inOptions );
	int				DoSendPacket( const UInt8* inPacketData, UInt16 inPacketLength );
	int				DoSummaryModifyEntry( const TCHAR* inLabel, const TCHAR* inGroup,
						UInt32 inType, void* inData );
	int				DoSummaryGetEntry( const TCHAR* inLabel, const TCHAR* inGroup, UInt32* outType,
						void** outData, UInt8* outSource );
	const UInt8*	DoPacketGetLayer( UInt8 inLayerType, UInt8 inMediaType, UInt8 inMediaSubType,
						const PluginPacket* inPacket, const UInt8* inPacketData, UInt16* ioBytesLeft );
	int				DoPrefsGetValue( const TCHAR* inName, const void* outData, UInt32* ioLength );
	int				DoPrefsSetValue( const TCHAR* inName, const void* inData, UInt32 inLength );
	int				DoInsertPacket( const PluginPacket* inPacket, const UInt8* inPacketData,
						UInt8 inMediaType, UInt8 inMediaSubType, UInt32 inReserved );
	int				DoSelectPackets( UInt32 inNumPackets, UInt64* inPacketNumbers, UInt32 inFlags );

	int				DoGetPacketCount( UInt32* outCount );
	int				DoGetFirstPacketIndex( UInt32* outIndex );
	int				DoGetPacket( UInt32 inIndex, UInt64* outPacketNumber, const PluginPacket** outPacket,
						const UInt8** outPacketData );
	int				DoSendPluginMessage( UInt8* inParamData, UInt32 inParamDataLen );

#if TARGET_OS_WIN32
	int				DoAddTab( const TCHAR* inTabName, const TCHAR* inWindowClass, void** outTabWnd );
	int				DoSelectPacketsEx( const UInt8* inSrcAddr, UInt16 inSrcAddrType, const UInt8* inDestAddr,
						UInt16 inDestAddrType, UInt16 inSrcPort, UInt16 inDestPort, UInt16 inPortTypes,
						bool inBothDirections, UInt32 inFlags );
	int				DoMakeFilter( const UInt8* inSrcAddr, UInt16 inSrcAddrType, const UInt8* inDestAddr,
						UInt16 inDestAddrType, UInt16 inSrcPort, UInt16 inDestPort, UInt16 inPortTypes,
						bool inBothDirections );
	int				DoClaimPacketString( UInt64 inPacketNumber, bool inExpert );
	int				DoInvokeNameEditDialog( PluginNameTableEntry* inEntry );
	int				DoPrefsGetPrefsPath( TCHAR* outString );
	int				DoResolveAddress( UInt8* inAddress, UInt16 inAddressType );
#elif TARGET_OS_MAC
	void			DoEventDispatch( const EventRecord* inEvent );
	int				DoGetProtocolColor( UInt32 inProtocol, RGBColor* outColor );
#endif
};
