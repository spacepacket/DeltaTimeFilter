// =============================================================================
//	PeekPlugin.cpp
//		implementation of the CPeekPlugin class.
// =============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#include "StdAfx.h"
#include "PeekPlugin.h"

#if TARGET_OS_MAC
#include "StUseBundleResFile.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



///////////////////////////////////////////////////////////////////////////////
//		CPeekPlugin
///////////////////////////////////////////////////////////////////////////////

CPeekPlugin::CPeekPlugin()
	:	m_APIVersion( kPluginAPIVersion )
#if TARGET_OS_WIN32
	,	m_hInstance( NULL )
	,	m_hResInstance( NULL )
	,	m_szResourceFilename( NULL )
	,	m_bResourceDllLoaded( false )
#elif TARGET_OS_MAC
	,	mBundle( NULL )
#endif
	,	m_bIsPeekUnicode( true )
	,	m_bFailure( false )
{
	m_pPeekApp = new CPeekApp();
}

CPeekPlugin::~CPeekPlugin()
{
	if ( m_bResourceDllLoaded ) {
		::FreeLibrary( m_hResInstance );
	}
	delete m_pPeekApp;
}


#ifdef _UNICODE
// -----------------------------------------------------------------------------
//		HandleMessageW
// -----------------------------------------------------------------------------

int
CPeekPlugin::HandleMessageW(
	SInt16				inMessage,
	PluginParamBlock*	ioParams )
{
	try {
		switch ( inMessage ) {
			case kPluginMsg_Load:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				m_bIsPeekUnicode =
					(((PluginLoadParam*)ioParams)->fAppCapabilities & kAppCapability_Unicode);
				return OnLoad( (PluginLoadParam*) ioParams );
			}
			break;

			case kPluginMsg_Unload:
			{
				return OnUnload();
			}
			break;

			case kPluginMsg_ReadPrefs:
			{
				return OnReadPrefs();
			}
			break;

			case kPluginMsg_WritePrefs:
			{
				return OnWritePrefs();
			}
			break;

			case kPluginMsg_CreateContext:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnCreateContext( (PluginCreateContextParam*) ioParams );
			}
			break;

			case kPluginMsg_DisposeContext:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnDisposeContext( (PluginDisposeContextParam*) ioParams );
			}
			break;

			case kPluginMsg_ProcessPacket:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnProcessPacket( (PluginProcessPacketParam*) ioParams );
			}
			break;

			case kPluginMsg_GetPacketString:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnGetPacketString( (PluginGetPacketStringParam*) ioParams );
			}
			break;

			case kPluginMsg_Apply:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnApply( (PluginApplyParam*) ioParams );
			}
			break;

			case kPluginMsg_Select:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnSelect( (PluginSelectParam*) ioParams );
			}
			break;

			case kPluginMsg_Reset:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnReset( (PluginResetParam*) ioParams );
			}
			break;

			case kPluginMsg_StartCapture:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnStartCapture( (PluginStartCaptureParam*) ioParams );
			}
			break;

			case kPluginMsg_StopCapture:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnStopCapture( (PluginStopCaptureParam*) ioParams );
			}
			break;

			case kPluginMsg_PacketsLoaded:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnPacketsLoaded( (PluginPacketsLoadedParam*) ioParams );
			}
			break;

			case kPluginMsg_About:
			{
				return OnAbout();
			}
			break;

			case kPluginMsg_Options:
			{
				return OnOptions();
			}
			break;

			case kPluginMsg_Summary:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnSummary( (PluginSummaryParam*) ioParams );
			}
			break;

			case kPluginMsg_Filter:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnFilter( (PluginFilterParam*) ioParams );
			}
			break;

			case kPluginMsg_FilterOptions:
			{
				return OnFilterOptions();
			}
			break;

			case kPluginMsg_NameTableUpdate:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnNameTableUpdate( (PluginNameTableUpdateParam*) ioParams );
			}
			break;

			case kPluginMsg_GetPacketAnalysis:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnGetPacketAnalysis( (PluginGetPacketStringParam*) ioParams );
			}
			break;

			case kPluginMsg_CreateNewAdapter:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnCreateNewAdapter( (PluginCreateNewAdapterParam*) ioParams );
			}
			break;

			case kPluginMsg_GetAdapterList:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnGetAdapterList( (PluginGetAdapterListParam*) ioParams );
			}
			break;

			case kPluginMsg_DeleteAdapter:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnDeleteAdapter( (PluginDeleteAdapterParam*) ioParams );
			}
			break;

			case kPluginMsg_SetAdapterAttribs:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnSetAdapterAttribs( (PluginAdapterAttribsParam*) ioParams );
			}
			break;

			case kPluginMsg_GetAdapterAttribs:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnGetAdapterAttribs( (PluginAdapterAttribsParam*) ioParams );
			}
			break;

			case kPluginMsg_DecodePacket:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnDecodePacket( (PluginDecodePacketParam*) ioParams );
			}
			break;

			case kPluginMsg_AdapterProperties:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnAdapterProperties( (PluginAdapterPropertiesParam*) ioParams );
			}
			break;

			case kPluginMsg_UserDecode:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnUserDecode( (PluginUserDecodeParam*) ioParams );
			}
			break;

			case kPluginMsg_DecodersLoaded:
			{
				return OnDecodersLoaded();
			}
			break;

			case kPluginMsg_IsMediaSupported:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnIsMediaSupported( (PluginMediaSupportedParam*) ioParams );
			}
			break;

			case kPluginMsg_ProcessPluginMessage:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnProcessPluginMessage( (PluginProcessPluginMessageParam*) ioParams );
			}
			break;

			case kPluginMsg_HandleNotify:
			{
				return OnHandleNotify( (PluginHandleNotifyParam*) ioParams );
			}
			break;

			default:
			{
				PLUGIN_DEBUGSTR( _T("Unknown message received in CPlugin::HandleMessage!") );
			}
			break;
		}
	}
	catch ( ... ) {
		m_bFailure = true;
	}

	return PLUGIN_RESULT_ERROR;
}

#else	// _UNICODE

// -----------------------------------------------------------------------------
//		HandleMessageA
// -----------------------------------------------------------------------------

int
CPeekPlugin::HandleMessageA(
	SInt16				inMessage,
	PluginParamBlock*	ioParams )
{
	try {
		switch ( inMessage ) {
			case kPluginMsg_Load:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				m_bIsPeekUnicode =
					(((PluginLoadParam*)ioParams)->fAppCapabilities & kAppCapability_Unicode);
				return OnLoad( (PluginLoadParam*) ioParams );
			}
			break;

			case kPluginMsg_Unload:
			{
				return OnUnload();
			}
			break;

			case kPluginMsg_ReadPrefs:
			{
				return OnReadPrefs();
			}
			break;


			case kPluginMsg_WritePrefs:
			{
				return OnWritePrefs();
			}
			break;

			case kPluginMsg_CreateContext:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnCreateContext( (PluginCreateContextParam*) ioParams );
			}
			break;

			case kPluginMsg_DisposeContext:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnDisposeContext( (PluginDisposeContextParam*) ioParams );
			}
			break;

			case kPluginMsg_ProcessPacket:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnProcessPacket( (PluginProcessPacketParam*) ioParams );
			}
			break;

			case kPluginMsg_GetPacketString:
			{
				PLUGIN_ASSERT( ioParams != NULL );

				// Since the main App is in Wide Char, we need to do proper conversion
				PluginGetPacketStringParam	ioParamProxy;
				PluginGetPacketStringParam*	pSrc = (PluginGetPacketStringParam*) ioParams;
				ioParamProxy = *pSrc;
				char szOut[1024];
				szOut[0] = '\0';
				ioParamProxy.fString = szOut;

				int nResult = OnGetPacketString( &ioParamProxy );
				mbstowcs( (wchar_t*) pSrc->fString, szOut, 1024 );

				return nResult;
			}
			break;

			case kPluginMsg_Apply:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnApply( (PluginApplyParam*) ioParams );
			}
			break;

			case kPluginMsg_Select:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnSelect( (PluginSelectParam*) ioParams );
			}
			break;

			case kPluginMsg_Reset:
			{
				PLUGIN_ASSERT( ioParams != NULL );

				// Since the main App is in Wide Char, we need to do proper conversion
				PluginResetParam	ioParamProxy;
				PluginResetParam*	pSrc = (PluginResetParam*) ioParams;
				ioParamProxy = *pSrc;
				char szOut[kPluginNameMaxLength];
				szOut[0] = '\0';
				ioParamProxy.fPluginAdapterID = szOut;

				int nResult = OnReset( &ioParamProxy );
				mbstowcs( (wchar_t*) pSrc->fPluginAdapterID, szOut, sizeof(szOut) );

				return nResult;
			}
			break;

			case kPluginMsg_StartCapture:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnStartCapture( (PluginStartCaptureParam*) ioParams );
			}
			break;

			case kPluginMsg_StopCapture:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnStopCapture( (PluginStopCaptureParam*) ioParams );
			}
			break;

			case kPluginMsg_PacketsLoaded:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnPacketsLoaded( (PluginPacketsLoadedParam*) ioParams );
			}
			break;

			case kPluginMsg_About:
			{
				return OnAbout();
			}
			break;

			case kPluginMsg_Options:
			{
				return OnOptions();
			}
			break;

			case kPluginMsg_Summary:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnSummary( (PluginSummaryParam*) ioParams );
			}
			break;

			case kPluginMsg_Filter:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnFilter( (PluginFilterParam*) ioParams );
			}
			break;

			case kPluginMsg_FilterOptions:
			{
				return OnFilterOptions();
			}
			break;

			case kPluginMsg_NameTableUpdate:
			{
				PLUGIN_ASSERT( ioParams != NULL );

				// Since the main App is in Wide Char, we need to do proper conversion
				PluginNameTableUpdateParam	ioParamProxy;
				PluginNameTableUpdateParam*	pSrc = (PluginNameTableUpdateParam*) ioParams;
				ioParamProxy = *pSrc;

				// Nametable entry
				PluginNameTableEntry theNTEntry;
				ioParamProxy.fEntry = &theNTEntry;
				theNTEntry = *pSrc->fEntry;

				// Convert Name
				CW2A szLabelName((wchar_t*) pSrc->fEntry->fName );
				ioParamProxy.fEntry->fName = szLabelName;

				// Convert GroupName
				CW2A szGroupName((wchar_t*) pSrc->fEntry->fGroup );
				ioParamProxy.fEntry->fGroup = szGroupName;

				int nResult = OnNameTableUpdate( &ioParamProxy );

				return nResult;
			}
			break;

			case kPluginMsg_GetPacketAnalysis:
			{
				PLUGIN_ASSERT( ioParams != NULL );

				// Since the main App is in Wide Char, we need to do proper conversion
				PluginGetPacketStringParam	ioParamProxy;
				PluginGetPacketStringParam*	pSrc = (PluginGetPacketStringParam*) ioParams;
				ioParamProxy = *pSrc;
				char szOut[1024];
				szOut[0] = '\0';
				ioParamProxy.fString = szOut;

				int nResult = OnGetPacketAnalysis( &ioParamProxy );
				mbstowcs( (wchar_t*) pSrc->fString, szOut, 1024 );

				return nResult;

			}
			break;

			case kPluginMsg_CreateNewAdapter:
			{
				PLUGIN_ASSERT( ioParams != NULL );

				// Since the main App is in Wide Char, we need to do proper conversion
				PluginCreateNewAdapterParam	ioParamProxy;
				PluginCreateNewAdapterParam*	pSrc = (PluginCreateNewAdapterParam*) ioParams;
				ioParamProxy = *pSrc;

				// Convert Adapter Name to ASCII
				CW2A szLabelName((wchar_t*) pSrc->fOutSelectedAdapterTag );
				ioParamProxy.fOutSelectedAdapterTag = szLabelName;

				return OnCreateNewAdapter( &ioParamProxy );
			}
			break;

			case kPluginMsg_GetAdapterList:
			{
				PLUGIN_ASSERT( ioParams != NULL );

				// Since the main App is in Wide Char, we need to do proper conversion
				PluginGetAdapterListParam	ioParamProxy;
				PluginGetAdapterListParam*	pSrc = (PluginGetAdapterListParam*) ioParams;
				ioParamProxy = *pSrc;

				// Create temporary storage for the adapter list
				ioParamProxy.fOutXMLAdapterList = (char*) malloc( pSrc->fOutXMLStreamLength * sizeof(char) );

				int nResult = OnGetAdapterList( &ioParamProxy );

				// Convert it back to wide char
				mbstowcs( (wchar_t*) pSrc->fOutXMLAdapterList, ioParamProxy.fOutXMLAdapterList, pSrc->fOutXMLStreamLength );

				// Free up the string
				free( (void*) ioParamProxy.fOutXMLAdapterList );

				return nResult;
			}
			break;

			case kPluginMsg_DeleteAdapter:
			{
				PLUGIN_ASSERT( ioParams != NULL );

				PluginDeleteAdapterParam	ioParamProxy;
				PluginDeleteAdapterParam*	pSrc = (PluginDeleteAdapterParam*) ioParams;
				ioParamProxy = *pSrc;

				// Create temporary storage for the adapter list
				CW2A szId( (wchar_t*) pSrc->fInDeleteID);
				ioParamProxy.fInDeleteID = szId;

				return OnDeleteAdapter( &ioParamProxy );
			}
			break;

			case kPluginMsg_SetAdapterAttribs:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnSetAdapterAttribs( (PluginAdapterAttribsParam*) ioParams );
			}
			break;

			case kPluginMsg_GetAdapterAttribs:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnGetAdapterAttribs( (PluginAdapterAttribsParam*) ioParams );
			}
			break;

			case kPluginMsg_DecodePacket:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnDecodePacket( (PluginDecodePacketParam*) ioParams );
			}
			break;

			case kPluginMsg_AdapterProperties:
			{
				PLUGIN_ASSERT( ioParams != NULL );

				PluginAdapterPropertiesParam	ioParamProxy;
				PluginAdapterPropertiesParam*	pSrc = (PluginAdapterPropertiesParam*) ioParams;
				ioParamProxy = *pSrc;

				// Create temporary storage for the adapter list
				CW2A szId( (wchar_t*) pSrc->fInAdapterID);
				ioParamProxy.fInAdapterID = szId;

				return OnAdapterProperties( &ioParamProxy );
			}

			case kPluginMsg_UserDecode:
			{
				PLUGIN_ASSERT( ioParams != NULL );

				PluginUserDecodeParam	ioParamProxy;
				PluginUserDecodeParam*	pSrc = (PluginUserDecodeParam*) ioParams;
				ioParamProxy = *pSrc;

				// Create temporary storage for the adapter list
				CW2A szId( (wchar_t*) pSrc->fFunctionName);
				ioParamProxy.fFunctionName = szId;

				return OnUserDecode( &ioParamProxy );
			}
			break;

			case kPluginMsg_DecodersLoaded:
			{
				return OnDecodersLoaded();
			}
			break;

			case kPluginMsg_IsMediaSupported:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnIsMediaSupported( (PluginMediaSupportedParam*) ioParams );
			}
			break;

			case kPluginMsg_ProcessPluginMessage:
			{
				PLUGIN_ASSERT( ioParams != NULL );
				return OnProcessPluginMessage( (PluginProcessPluginMessageParam*) ioParams );
			}
			break;

			case kPluginMsg_HandleNotify:
			{
				PLUGIN_ASSERT( ioParams != NULL );

				PluginHandleNotifyParam		ioParamProxy;
				PluginHandleNotifyParam*	pSrc = (PluginHandleNotifyParam*) ioParams;
				ioParamProxy = *pSrc;

				// create temporary storage for the short message.
				CW2A	szShortMsg( (wchar_t*) pSrc->fShortMessage );
				ioParamProxy.fShortMessage = szShortMsg;

				// create temporary storage for the long message.
				CW2A	szLongMsg( (wchar_t*) pSrc->fLongMessage );
				ioParamProxy.fLongMessage = szLongMsg;

				return OnHandleNotify( &ioParamProxy );
			}
			break;

			default:
			{
				PLUGIN_DEBUGSTR( _T("Unknown message received in CPlugin::HandleMessage!") );
			}
			break;
		}
	}
	catch ( ... ) {
		m_bFailure = true;
	}
	return PLUGIN_RESULT_ERROR;
}
#endif // _UNICODE


#if TARGET_OS_WIN32
// -----------------------------------------------------------------------------
//		DllMain
// -----------------------------------------------------------------------------

BOOL
CPeekPlugin::DllMain(
	HINSTANCE	inInstance,
	DWORD		inReason,
	LPVOID		inReserved )
{
	inReserved;

	if ( inReason == DLL_PROCESS_ATTACH ) {
		m_hInstance = inInstance;
		m_hResInstance = inInstance;
	}

	return TRUE;
}
#endif // TARGET_OS_WIN32

// -----------------------------------------------------------------------------
//		GetSupportedProtoSpecs
// -----------------------------------------------------------------------------

void
CPeekPlugin::GetSupportedProtoSpecs(
	UInt32*		outNumProtoSpecs,
	UInt32**	outProtoSpecs ) const
{
	*outNumProtoSpecs = 0;
	*outProtoSpecs = NULL;
}


// =============================================================================
//		Plugin Message Handlers
// =============================================================================

// -----------------------------------------------------------------------------
//		OnLoad
// -----------------------------------------------------------------------------
int
CPeekPlugin::OnLoad(
	PluginLoadParam*	ioParams )
{
	// Check the API version.
	if ( ioParams->fAPIVersion == kPluginAPIVersion ) {
		m_APIVersion = kPluginAPIVersion;
	}
	else {
		return PLUGIN_RESULT_ERROR;
	}

	// Return the API version used by the plugin.
	ioParams->fAPIVersion = m_APIVersion;

	m_pPeekApp->Init( ioParams->fAppContextData, ioParams->fClientAppData );

	// Get the name of the plugin.
	ioParams->fName[0] = 0;
#ifdef _UNICODE
	GetName( ioParams->fName, (kPluginNameMaxLength * sizeof( TCHAR )) );
#else
	char	szName[kPluginNameMaxLength];
	szName[0] = '\0';
	GetName( szName, sizeof( szName ) );
	mbstowcs( (wchar_t*) ioParams->fName, szName, sizeof( szName ) );
#endif

	// Get the plugin id.
	GetID( &ioParams->fID );

	// Get the plugin attributes.
	ioParams->fAttributes = GetAttributes();

	// Get the supported actions.
	ioParams->fSupportedActions = GetSupportedActions();

	// Get the default actions.
	ioParams->fDefaultActions = GetDefaultActions();

	// Get supported ProtoSpecs.
	GetSupportedProtoSpecs(
		&ioParams->fSupportedCount,
		&ioParams->fSupportedProtoSpecs );

	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnUnload
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnUnload()
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnReadPrefs
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnReadPrefs()
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnWritePrefs
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnWritePrefs()
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnAbout
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnAbout()
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnOptions
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnOptions()
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnFilterOptions
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnFilterOptions()
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnCreateContext
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnCreateContext(
	PluginCreateContextParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnDisposeContext
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnDisposeContext(
	PluginDisposeContextParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnNameTableUpdate
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnNameTableUpdate(
	PluginNameTableUpdateParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnCreateNewAdapter
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnCreateNewAdapter(
	PluginCreateNewAdapterParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnGetAdapterList
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnGetAdapterList(
	PluginGetAdapterListParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnDeleteAdapter
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnDeleteAdapter(
	PluginDeleteAdapterParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnSetAdapterAttribs
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnSetAdapterAttribs(
	PluginAdapterAttribsParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnGetAdapterAttribs
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnGetAdapterAttribs(
	PluginAdapterAttribsParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnAdapterProperties
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnAdapterProperties(
	PluginAdapterPropertiesParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnUserDecode
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnUserDecode(
						  PluginUserDecodeParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnDecodersLoaded
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnDecodersLoaded()
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnIsMediaSupported
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnIsMediaSupported(
	PluginMediaSupportedParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// =============================================================================
//		Context Specific Message Handlers
// =============================================================================

// -----------------------------------------------------------------------------
//		OnReset
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnReset(
	PluginResetParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnStartCapture
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnStartCapture(
	PluginStartCaptureParam*	/* ioParams */ )
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnStopCapture
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnStopCapture(
	PluginStopCaptureParam*	/* ioParams */ )
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnProcessPacket
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnProcessPacket(
	PluginProcessPacketParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnGetPacketString
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnGetPacketString(
	PluginGetPacketStringParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnApply
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnApply(
	PluginApplyParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnSelect
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnSelect(
	PluginSelectParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnPacketsLoaded
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnPacketsLoaded(
	PluginPacketsLoadedParam*	/* ioParams */ )
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnSummary
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnSummary(
	PluginSummaryParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnFilter
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnFilter(
	PluginFilterParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnGetPacketAnalysis
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnGetPacketAnalysis(
	PluginGetPacketStringParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnDecodePacket
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnDecodePacket(
	PluginDecodePacketParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnProcessPluginMessage
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnProcessPluginMessage(
	PluginProcessPluginMessageParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnHandleNotify
// -----------------------------------------------------------------------------

int
CPeekPlugin::OnHandleNotify(
	PluginHandleNotifyParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// =============================================================================
//		Utility Routines
// =============================================================================

// -----------------------------------------------------------------------------
//		LoadString
// -----------------------------------------------------------------------------
// Load string from resource.

bool
CPeekPlugin::LoadString(
	UInt32	inID,
	TCHAR*	outString,
	int		nBufSize ) const
{
	// Sanity check.
	PLUGIN_ASSERT( outString != NULL );
	if ( outString == NULL ) return false;

	// Start with an empty string.
	outString[0] = 0;

#if TARGET_OS_WIN32
	bool bRet = true;
	if ( m_hResInstance == NULL ) {
		// This should never be the case. This means the Plugin specified a
		//  Resource DLL but that DLL was never loaded.
		ASSERT(0);
		if (::LoadString( m_hInstance, inID, outString, nBufSize ) == 0 ) {
			bRet = false;
		}
	}
	else {
		if (::LoadString( m_hResInstance, inID, outString, nBufSize ) == 0 ) {
			bRet = false;
		}
		else {
			// Use proper null termination.
			outString[nBufSize-1] = 0;
		}
	}

	return bRet;
#elif TARGET_OS_MAC
	// Open our resource file.
	StUseBundleResFile  fork( mBundle );
	StringHandle hString = ::GetString( inID );
	if ( hString != NULL ) {
		::BlockMoveData( &((*hString)[1]), outString, (*hString)[0] );
		outString[(*hString)[0]] = 0;
		::ReleaseResource( (Handle) hString );
	}
	return (outString[0] != 0);
#endif
}


#if TARGET_OS_WIN32
// -----------------------------------------------------------------------------
//		GetResourceHandle
// -----------------------------------------------------------------------------

HINSTANCE
CPeekPlugin::GetResourceHandle()
{
	if ( m_szResourceFilename == NULL ) {
		return m_hInstance;
	}

	if ( !m_bResourceDllLoaded ) {

		// Otherwise ....
		TCHAR	szAppResPath[MAX_PATH];
		int		nResult= CPeekApp::DoGetAppResourcePath( szAppResPath );
		if ( nResult == PLUGIN_RESULT_SUCCESS ) {
			// Try to open the Resource file
			CString theResoucePath;
			theResoucePath.Format( _T("%s\\%s\\%s"), szAppResPath,
				kPeekPluginResourceFolder, m_szResourceFilename );
			m_hResInstance = ::LoadLibrary( theResoucePath );
			ASSERT( m_hResInstance != NULL );
			if ( m_hResInstance != NULL ) {
				m_bResourceDllLoaded = true;
			}
		}
	}

	return m_hResInstance;
}
#endif  // TARGET_OS_WIN32


// =============================================================================
//  Callback Routines
// =============================================================================

// -----------------------------------------------------------------------------
//		DoGetProtocolName
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoGetProtocolName(
	UInt32	inProtocol,
	TCHAR*	outString )
{
	return CPeekApp::DoGetProtocolName( inProtocol, outString );
}


// -----------------------------------------------------------------------------
//		DoGetProtocolLongName
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoGetProtocolLongName(
	UInt32	inProtocol,
	TCHAR*	outString )
{
	return CPeekApp::DoGetProtocolLongName( inProtocol, outString );
}


// -----------------------------------------------------------------------------
//		DoGetProtocolHierName
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoGetProtocolHierName(
	UInt32	inProtocol,
	TCHAR*	outString )
{
	return CPeekApp::DoGetProtocolHierName( inProtocol, outString );
}


// -----------------------------------------------------------------------------
//		DoGetProtocolParent
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoGetProtocolParent(
	UInt32	inProtocol,
	UInt32*	outProtocolParent )
{
	return CPeekApp::DoGetProtocolParent( inProtocol, outProtocolParent );
}


// -----------------------------------------------------------------------------
//		DoIsDescendentOf
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoIsDescendentOf(
	UInt32			inSubProtocol,
	const UInt32*	inParentArray,
	SInt32			inParentCount,
	UInt32*			outMatchID )
{
	return CPeekApp::DoIsDescendentOf(
		inSubProtocol,
		inParentArray,
		inParentCount,
		outMatchID );
}


// -----------------------------------------------------------------------------
//		DoNotify
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoNotify(
	PluginCaptureContext	inCaptureContext,
	UInt64					inTimeStamp,
	UInt8					inSeverity,
	const TCHAR*			inShortString,
	const TCHAR*			inLongString )
{
	return CPeekApp::DoNotify(
		inCaptureContext,
		inTimeStamp,
		inSeverity,
		inShortString,
		inLongString );
}


// -----------------------------------------------------------------------------
//		DoLookupName
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoLookupName(
	const UInt8*	inEntry,
	UInt16			inEntryType,
	TCHAR*			outName,
	UInt8*			outType )
{
	return CPeekApp::DoLookupName(
		inEntry,
		inEntryType,
		outName,
		outType );
}


// -----------------------------------------------------------------------------
//		DoLookupName
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoLookupName(
	PluginNameTableEntry*	ioEntry )
{
	return CPeekApp::DoLookupName( ioEntry );
}


// -----------------------------------------------------------------------------
//		DoLookupEntry
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoLookupEntry(
	const TCHAR*	inName,
	UInt16			inEntryType,
	UInt8*			outEntry )
{
	return CPeekApp::DoLookupEntry(
		inName,
		inEntryType,
		outEntry );
}


// -----------------------------------------------------------------------------
//		DoLookupEntry
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoLookupEntry(
	PluginNameTableEntry*	inEntry )
{
	return CPeekApp::DoLookupEntry( inEntry );
}


// -----------------------------------------------------------------------------
//		DoAddNameEntry
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoAddNameEntry(
	const TCHAR*	inName,
	const TCHAR*	inGroup,
	const UInt8*	inEntry,
	UInt16			inEntryType,
	UInt16			inOptions )
{
	return CPeekApp::DoAddNameEntry(
		inName,
		inGroup,
		inEntry,
		inEntryType,
		inOptions );
}


// -----------------------------------------------------------------------------
//		DoAddNameEntry
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoAddNameEntry(
	const PluginNameTableEntry*	inEntry,
	UInt16						inOptions )
{
	return CPeekApp::DoAddNameEntry( inEntry, inOptions );
}


// -----------------------------------------------------------------------------
//		DoSendPacket
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoSendPacket(
	const UInt8*	inPacketData,
	UInt16			inPacketLength )
{
	return CPeekApp::DoSendPacket( inPacketData, inPacketLength );
}


// -----------------------------------------------------------------------------
//		DoSummaryModifyEntry
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoSummaryModifyEntry(
	PluginCaptureContext	inCaptureContext,
	const TCHAR*			inLabel,
	const TCHAR*			inGroup,
	UInt32					inType,
	void*					inData )
{
	return CPeekApp::DoSummaryModifyEntry(
		inCaptureContext,
		inLabel,
		inGroup,
		inType,
		inData );
}


// -----------------------------------------------------------------------------
//		DoSummaryGetEntry
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoSummaryGetEntry(
	PluginCaptureContext	inCaptureContext,
	const TCHAR*			inLabel,
	const TCHAR*			inGroup,
	UInt32*					outType,
	void**					outData,
	UInt8*					outSource )
{
	return CPeekApp::DoSummaryGetEntry(
		inCaptureContext,
		inLabel,
		inGroup,
		outType,
		outData,
		outSource );
}


// -----------------------------------------------------------------------------
//		DoPacketGetLayer
// -----------------------------------------------------------------------------

const UInt8*
CPeekPlugin::DoPacketGetLayer(
	UInt8				inLayerType,
	UInt8				inMediaType,
	UInt8				inMediaSubType,
	const PluginPacket*	inPacket,
	const UInt8*		inPacketData,
	UInt16*				ioBytesLeft )
{
	return CPeekApp::DoPacketGetLayer(
		inLayerType,
		inMediaType,
		inMediaSubType,
		inPacket,
		inPacketData,
		ioBytesLeft );
}


// -----------------------------------------------------------------------------
//		DoPacketGetDataLayer
// -----------------------------------------------------------------------------

const UInt8*
CPeekPlugin::DoPacketGetDataLayer(
	UInt32				inProtoSpec,
	UInt8				inMediaType,
	UInt8				inMediaSubType,
	const PluginPacket*	inPacket,
	const UInt8*		inPacketData,
	UInt16*				ioBytesLeft,
	UInt32*				outSourceProtoSpec )
{
	return CPeekApp::DoPacketGetDataLayer(
		inProtoSpec,
		inMediaType,
		inMediaSubType,
		inPacket,
		inPacketData,
		ioBytesLeft,
		outSourceProtoSpec );
}


// -----------------------------------------------------------------------------
//		DoPacketGetHeaderLayer
// -----------------------------------------------------------------------------

const UInt8*
CPeekPlugin::DoPacketGetHeaderLayer(
	UInt32				inProtoSpec,
	UInt8				inMediaType,
	UInt8				inMediaSubType,
	const PluginPacket*	inPacket,
	const UInt8*		inPacketData,
	UInt16*				ioBytesLeft,
	UInt32*				outSourceProtoSpec )
{
	return CPeekApp::DoPacketGetHeaderLayer(
		inProtoSpec,
		inMediaType,
		inMediaSubType,
		inPacket,
		inPacketData,
		ioBytesLeft,
		outSourceProtoSpec );
}


// -----------------------------------------------------------------------------
//		DoPacketGetAddress
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoPacketGetAddress(
	PluginCaptureContext	inCaptureContext,
	UInt8					inAddressSelector,
	UInt8					inMediaType,
	UInt8					inMediaSubType,
	const PluginPacket*		inPacket,
	const UInt8*			inPacketData,
	UInt64					inPacketNumber,
	UInt8*					outAddress,
	UInt16*					outAddressType )
{
	return CPeekApp::DoPacketGetAddress(
		inCaptureContext,
		inAddressSelector,
		inMediaType,
		inMediaSubType,
		inPacket,
		inPacketData,
		inPacketNumber,
		outAddress,
		outAddressType );
}


// -----------------------------------------------------------------------------
//		DoPrefsGetValue
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoPrefsGetValue(
	PluginCaptureContext	inCaptureContext,
	const TCHAR*			inName,
	const void*				outData,
	UInt32*					ioLength )
{
	return CPeekApp::DoPrefsGetValue(
		inCaptureContext,
		inName,
		outData,
		ioLength );
}


// -----------------------------------------------------------------------------
//		DoPrefsSetValue
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoPrefsSetValue(
	PluginCaptureContext	inCaptureContext,
	const TCHAR*			inName,
	const void*				inData,
	UInt32					inLength )
{
	return CPeekApp::DoPrefsSetValue(
		inCaptureContext,
		inName,
		inData,
		inLength );
}


// -----------------------------------------------------------------------------
//		DoInsertPacket
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoInsertPacket(
	PluginCaptureContext	inCaptureContext,
	const PluginPacket*		inPacket,
	const UInt8*			inPacketData,
	UInt8					inMediaType,
	UInt8					inMediaSubType,
	UInt32					inReserved )
{
	return CPeekApp::DoInsertPacket(
		inCaptureContext,
		inPacket,
		inPacketData,
		inMediaType,
		inMediaSubType,
		inReserved );
}


// -----------------------------------------------------------------------------
//		DoSelectPackets
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoSelectPackets(
	PluginCaptureContext	inCaptureContext,
	UInt32					inNumPackets,
	UInt64*					inPacketNumbers,
	UInt32					inFlags )
{
	return CPeekApp::DoSelectPackets(
		inCaptureContext,
		inNumPackets,
		inPacketNumbers,
		inFlags );
}


// -----------------------------------------------------------------------------
//		DoGetPacketCount
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoGetPacketCount(
	PluginCaptureContext	inCaptureContext,
	UInt32*					outCount )
{
	return CPeekApp::DoGetPacketCount(
		inCaptureContext,
		outCount );
}


// -----------------------------------------------------------------------------
//		DoGetFirstPacketIndex
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoGetFirstPacketIndex(
	PluginCaptureContext	inCaptureContext,
	UInt32*					outIndex )
{
	return CPeekApp::DoGetFirstPacketIndex(
		inCaptureContext,
		outIndex );
}


// -----------------------------------------------------------------------------
//		DoGetPacket
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoGetPacket(
	PluginCaptureContext	inCaptureContext,
	UInt32					inIndex,
	UInt64*					outPacketNumber,
	const PluginPacket**	outPacket,
	const UInt8**			outPacketData )
{
	return CPeekApp::DoGetPacket(
		inCaptureContext,
		inIndex,
		outPacketNumber,
		outPacket,
		outPacketData );
}


// -----------------------------------------------------------------------------
//		DoDecodeOp
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoDecodeOp(
	PluginContext	inDecodeContext,
	PluginContext	inDecodeState,
	int				nOp,
	UInt32			nValue,
	UInt32			nGlobal,
	UInt8			nStyleValue,
	UInt8			nStyleLabel,
	TCHAR*			pszString,
	TCHAR*			pszSummary )
{
	return CPeekApp::DoDecodeOp(
		inDecodeContext,
		inDecodeState,
		nOp,
		nValue,
		nGlobal,
		nStyleValue,
		nStyleLabel,
		pszString,
		pszSummary );
}


// -----------------------------------------------------------------------------
//		DoAddUserDecode
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoAddUserDecode(
	const TCHAR*	inFuncName )
{
	return CPeekApp::DoAddUserDecode( inFuncName );
}


// -----------------------------------------------------------------------------
//		DoSendPluginMessage
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoSendPluginMessage(
	PluginCaptureContext	inCaptureContext,
	UInt8*					inParamData,
	UInt32					inParamDataLen )
{
	return CPeekApp::DoSendPluginMessage(
		inCaptureContext,
		inParamData,
		inParamDataLen );
}


#if TARGET_OS_WIN32
// -----------------------------------------------------------------------------
//		DoAddTab
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoAddTab(
	PluginCaptureContext	inCaptureContext,
	const TCHAR*			inTabName,
	const TCHAR*			inWindowClass,
	void**					outTabWnd )
{
	return CPeekApp::DoAddTab(
		inCaptureContext,
		inTabName,
		inWindowClass,
		outTabWnd );
}

// -----------------------------------------------------------------------------
//		DoSelectPackets
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoSelectPacketsEx(
	PluginCaptureContext	inCaptureContext,
	const UInt8*			inSrcAddr,
	UInt16					inSrcAddrType,
	const UInt8*			inDestAddr,
	UInt16					inDestAddrType,
	UInt16					inSrcPort,
	UInt16					inDestPort,
	UInt16					inPortTypes,
	bool					inBothDirections,
	UInt32					inFlags )
{
	return CPeekApp::DoSelectPacketsEx(
		inCaptureContext,
		inSrcAddr,
		inSrcAddrType,
		inDestAddr,
		inDestAddrType,
		inSrcPort,
		inDestPort,
		inPortTypes,
		inBothDirections,
		inFlags );
}


// -----------------------------------------------------------------------------
//		DoMakeFilter
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoMakeFilter(
	const UInt8*	inSrcAddr,
	UInt16			inSrcAddrType,
	const UInt8*	inDestAddr,
	UInt16			inDestAddrType,
	UInt16			inSrcPort,
	UInt16			inDestPort,
	UInt16			inPortTypes,
	bool			inBothDirections )
{
	return CPeekApp::DoMakeFilter(
		inSrcAddr,
		inSrcAddrType,
		inDestAddr,
		inDestAddrType,
		inSrcPort,
		inDestPort,
		inPortTypes,
		inBothDirections );
}


// -----------------------------------------------------------------------------
//		DoClaimPacketString
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoClaimPacketString(
	PluginCaptureContext	inCaptureContext,
	UInt64					inPacketNumber,
	bool					inExpert )
{
	return CPeekApp::DoClaimPacketString(
		inCaptureContext,
		inPacketNumber,
		inExpert );
}


// -----------------------------------------------------------------------------
//		DoInvokeNameEditDialog
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoInvokeNameEditDialog(
	PluginNameTableEntry*	inEntry )
{
	return CPeekApp::DoInvokeNameEditDialog( inEntry );
}


// -----------------------------------------------------------------------------
//		DoPrefsGetPrefsPath
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoPrefsGetPrefsPath(
	TCHAR*	outString )
{
	return CPeekApp::DoPrefsGetPrefsPath( outString );
}


// -----------------------------------------------------------------------------
//		DoResolveAddress
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoResolveAddress(
	UInt8*	inAddress,
	UInt16	inAddressType )
{
	return CPeekApp::DoResolveAddress( inAddress, inAddressType );
}


// -----------------------------------------------------------------------------
//		DoGetProtocolColor
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoGetProtocolColor(
	UInt32		inProtocol,
	COLORREF*	outColor )
{
	return CPeekApp::DoGetProtocolColor( inProtocol, outColor );
}

#elif TARGET_OS_MAC

// -----------------------------------------------------------------------------
//		DoEventDispatch
// -----------------------------------------------------------------------------

void
CPeekPlugin::DoEventDispatch(
	const EventRecord*	inEvent )
{
	PLUGIN_ASSERT( inEvent != NULL );
	if ( inEvent == NULL ) return;
	PLUGIN_ASSERT( s_procEventDispatch != NULL );
	if ( s_procEventDispatch == NULL ) return;
	(s_procEventDispatch)( inEvent );
}


// -----------------------------------------------------------------------------
//		DoGetProtocolColor
// -----------------------------------------------------------------------------

int
CPeekPlugin::DoGetProtocolColor(
	UInt32		inProtocol,
	RGBColor*	outColor )
{
	return CPeekApp::DoGetProtocolColor( inProtocol, outColor );
}
#endif // TARGET_OS_xx
