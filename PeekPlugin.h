// =============================================================================
//	PeekPlugin.h
//		interface for the CPeekPlugin class.
// =============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#pragma once

#include "StdAfx.h"
#include "PeekPlug.h"
#include "PeekApp.h"

using namespace PeekPlugin;

#if TARGET_OS_MAC
	#include <new>
	typedef PeekPlugCallbacks * HMODULE;
	typedef Ptr	FARPROC;
	// CFM routines made to work like windows calls.
	static HMODULE GetModuleHandle( const TCHAR* inClientAppDataP );
	static FARPROC GetProcAddress( HMODULE inModule, const TCHAR* inProcName );
#endif // TARGET_OS_MAC

#if TARGET_OS_WIN32
	#define		kPeekPluginResourceFolder	_T("PluginRes")
#endif // TARGET_OS_WIN32


///////////////////////////////////////////////////////////////////////////////
//		CPeekPlugin
///////////////////////////////////////////////////////////////////////////////

class CPeekPlugin
{
protected:
	UInt32				m_APIVersion;
	bool				m_bIsPeekUnicode;
	CPeekApp*			m_pPeekApp;

#if TARGET_OS_WIN32
	HINSTANCE			m_hInstance;			// Calling app's instance handle.
	HINSTANCE			m_hResInstance;
	TCHAR*				m_szResourceFilename;
	bool				m_bResourceDllLoaded;
#if !defined(_UNICODE) && !defined(UNICODE)
	UINT				m_nCodePage;			// Code page from User's default, for ASCII build
#endif // !UNICODE
#elif TARGET_OS_MAC
	static EventDispatchProc	s_procEventDispatch;	// MacOS event dispatch proc.
	CFBundleRef					mBundle;
#endif // TARGET_OS_WIN32

public:
	bool			m_bFailure;

	;				CPeekPlugin();
	virtual			~CPeekPlugin();

#ifdef _UNICODE
	virtual int		HandleMessageW( SInt16 inMessage, PluginParamBlock* ioParams );
	#define HandleMessage	HandleMessageW
#else
	virtual int		HandleMessageA( SInt16 inMessage, PluginParamBlock* ioParams );
	#define HandleMessage	HandleMessageA
#endif // _UNICODE

#if TARGET_OS_WIN32
	virtual BOOL	DllMain( HINSTANCE inInstance, DWORD inReason, LPVOID inReserved );
#endif  // TARGET_OS_WIN32

	virtual void	GetName( TCHAR* outName, int nBufSize ) const = 0;
	virtual void	GetID( PluginID* outID ) const = 0;
	virtual UInt16	GetAttributes() const = 0;
	virtual UInt16	GetSupportedActions() const = 0;
	virtual UInt16	GetDefaultActions() const = 0;
	virtual void	GetSupportedProtoSpecs( UInt32* outNumProtoSpecs, UInt32** outProtoSpecs ) const;

	//	Plugin Message Handlers
	virtual int		OnLoad( PluginLoadParam* ioParams );
	virtual int		OnUnload();
	virtual int		OnReadPrefs();
	virtual int		OnWritePrefs();
	virtual int		OnAbout();
	virtual int		OnOptions();
	virtual int		OnFilterOptions();
	virtual int		OnCreateContext( PluginCreateContextParam* ioParams );
	virtual int		OnDisposeContext( PluginDisposeContextParam* ioParams );
	virtual int		OnNameTableUpdate( PluginNameTableUpdateParam* ioParams );
	virtual int		OnCreateNewAdapter( PluginCreateNewAdapterParam* ioParams );
	virtual int		OnGetAdapterList( PluginGetAdapterListParam* ioParams );
	virtual int		OnDeleteAdapter( PluginDeleteAdapterParam* ioParams );
	virtual int		OnSetAdapterAttribs( PluginAdapterAttribsParam* ioParams );
	virtual int		OnGetAdapterAttribs( PluginAdapterAttribsParam* ioParams );
	virtual int		OnAdapterProperties( PluginAdapterPropertiesParam* ioParams );
	virtual int		OnUserDecode( PluginUserDecodeParam* ioParams );
	virtual int		OnDecodersLoaded();
	virtual int		OnIsMediaSupported( PluginMediaSupportedParam* ioParams );

	//	Context Specific Message Handlers
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

	// Utility routines.
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
							inMediaType, inMediaSubType, outIPHdrData, outIPHdrBytes,
							outIPData, outIPDataBytes, outDeliveryProtocol );
					}

#if TARGET_OS_WIN32
	virtual HINSTANCE	GetResourceHandle();
#endif // TARGET_OS_WIN32

	// Wrappers for callback functions.
	int				DoGetProtocolName( UInt32 inProtocol, TCHAR* outString );
	int				DoGetProtocolLongName( UInt32 inProtocol, TCHAR* outString );
	int				DoGetProtocolHierName( UInt32 inProtocol, TCHAR* outString );
	int				DoGetProtocolParent( UInt32 inProtocol, UInt32* outProtocolParent );
	int				DoIsDescendentOf( UInt32 inSubProtocol, const UInt32* inParentArray,
						SInt32 inParentCount, UInt32* outMatchID );
	int				DoNotify( PluginCaptureContext inCaptureContext, UInt64 inTimeStamp, UInt8 inSeverity,
						const TCHAR* inShortString, const TCHAR* inLongString );
	int				DoLookupName( const UInt8* inEntry, UInt16 inEntryType, TCHAR* outName, UInt8* outType );
	int				DoLookupName( PluginNameTableEntry* ioEntry );
	int				DoLookupEntry( const TCHAR* inName, UInt16 inEntryType, UInt8* outEntry );
	int				DoLookupEntry( PluginNameTableEntry* ioEntry );
	int				DoAddNameEntry( const TCHAR* inName, const TCHAR* inGroup, const UInt8* inEntry,
						UInt16 inEntryType, UInt16 inOptions );
	int				DoAddNameEntry( const PluginNameTableEntry* inEntry, UInt16 inOptions );
	int				DoSummaryModifyEntry( PluginCaptureContext inCaptureContext, const TCHAR* inLabel,
						const TCHAR* inGroup, UInt32 inType, void* inData );
	int				DoSummaryGetEntry( PluginCaptureContext inCaptureContext, const TCHAR* inLabel,
						const TCHAR* inGroup, UInt32* outType, void** outData, UInt8* outSource );
	const UInt8*	DoPacketGetLayer( UInt8 inLayerType, UInt8 inMediaType, UInt8 inMediaSubType,
						const PluginPacket* inPacket, const UInt8* inPacketData, UInt16* ioBytesLeft );
	const UInt8*	DoPacketGetDataLayer( UInt32 inProtoSpec, UInt8 inMediaType, UInt8 inMediaSubType,
						const PluginPacket*	inPacket, const UInt8* inPacketData, UInt16* ioBytesLeft,
						UInt32* outSourceProtoSpec );
	const UInt8*	DoPacketGetHeaderLayer( UInt32 inProtoSpec, UInt8 inMediaType, UInt8 inMediaSubType,
						const PluginPacket*	inPacket, const UInt8* inPacketData, UInt16* ioBytesLeft,
						UInt32* outSourceProtoSpec );
	int				DoPacketGetAddress( PluginCaptureContext inCaptureContext, UInt8 inAddressSelector,
						UInt8 inMediaType, UInt8 inMediaSubType, const PluginPacket* inPacket,
						const UInt8* inPacketData, UInt64 inPacketNumber, UInt8* outAddress, UInt16* outAddressType );
	int				DoPrefsGetValue( PluginCaptureContext inCaptureContext, const TCHAR* inName,
						const void* outData, UInt32* ioLength );
	int				DoPrefsSetValue( PluginCaptureContext inCaptureContext, const TCHAR* inName,
						const void* inData, UInt32 inLength );
	int				DoSendPacket( const UInt8* inPacketData, UInt16 inPacketLength );
	int				DoInsertPacket( PluginCaptureContext inCaptureContext, const PluginPacket* inPacket,
						const UInt8* inPacketData, UInt8 inMediaType, UInt8 inMediaSubType, UInt32 inReserved );
	int				DoSelectPackets( PluginCaptureContext inCaptureContext, UInt32 inNumPackets,
						UInt64* inPacketNumbers, UInt32 inFlags );

	int				DoGetPacketCount( PluginCaptureContext inCaptureContext, UInt32* outCount );
	int				DoGetFirstPacketIndex( PluginCaptureContext inCaptureContext, UInt32* outIndex );
	int				DoGetPacket( PluginCaptureContext inCaptureContext, UInt32 inIndex,
						UInt64* outPacketNumber, const PluginPacket** outPacket, const UInt8** outPacketData );
	int				DoDecodeOp( PluginContext inDecodeContext, PluginContext inDecodeState, int nOp,
						UInt32 nValue, UInt32 nGlobal, UInt8 nStyleValue, UInt8 nStyleLabel,
						TCHAR* pszString, TCHAR* pszSummary );
	int				DoAddUserDecode( const TCHAR* inFuncName );
	int				DoSendPluginMessage( PluginCaptureContext inCaptureContext, UInt8* inParamData,
						UInt32 inParamDataLen );
#if TARGET_OS_WIN32
	int				DoAddTab( PluginCaptureContext inCaptureContext, const TCHAR* inTabName,
						const TCHAR* inWindowClass, void** outTabWnd );
	int				DoSelectPacketsEx( PluginCaptureContext inCaptureContext, const UInt8* inSrcAddr,
						UInt16 inSrcAddrType, const UInt8* inDestAddr, UInt16 inDestAddrType, UInt16 inSrcPort,
						UInt16 inDestPort, UInt16 inPortTypes, bool inBothDirections, UInt32 inFlags );
	int				DoMakeFilter( const UInt8* inSrcAddr, UInt16 inSrcAddrType, const UInt8* inDestAddr,
						UInt16 inDestAddrType, UInt16 inSrcPort, UInt16 inDestPort, UInt16 inPortTypes,
						bool inBothDirections );
	int				DoClaimPacketString( PluginCaptureContext inCaptureContext, UInt64 inPacketNumber, bool inExpert );
	int				DoInvokeNameEditDialog( PluginNameTableEntry* inEntry );
	int				DoPrefsGetPrefsPath( TCHAR* outString );
	int				DoResolveAddress( UInt8* inAddress, UInt16 inAddressType );
	int				DoGetProtocolColor( UInt32 inProtocol, COLORREF* outColor );
#elif TARGET_OS_MAC
	void			DoEventDispatch( const EventRecord* inEvent );
	int				DoGetProtocolColor( UInt32 inProtocol, RGBColor* outColor );
#endif
};
