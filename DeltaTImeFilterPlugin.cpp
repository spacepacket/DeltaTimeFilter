// =============================================================================
//	DeltaTimeFilterPlugin.cpp
//		implementation of the CDeltaTimeFilterPlugin class.
// =============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#include "StdAfx.h"
#include "DeltaTimeFilterPlugin.h"
#include "DeltaTimeFilterContext.h"
#include "DeltaTimeFilterAbout.h"
#include "DeltaTimeFilterOptions.h"
#include "XMLDoc.h"
#include "CatchHR.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


////////////////////////////////////////////////////////////////////////////////
//		CDeltaTimeFilterPlugin
////////////////////////////////////////////////////////////////////////////////

CDeltaTimeFilterPlugin::CDeltaTimeFilterPlugin()
{
	HRESULT hr = CLSIDFromString( L"{DC15D17D-1DF1-46E1-9008-2EFAB15A55A6}", (LPCLSID) &s_ID );
	ASSERT( SUCCEEDED( hr ) );
	AddListener( this );
}


// -----------------------------------------------------------------------------
//		GetName
// -----------------------------------------------------------------------------

void
CDeltaTimeFilterPlugin::GetName(
	TCHAR*	outName,
	int		nBufSize ) const
{
	// Get the plugin name.
	LoadString( IDS_NAME, outName, nBufSize );
}


// -----------------------------------------------------------------------------
//		GetSupportedProtoSpecs
// -----------------------------------------------------------------------------

void
CDeltaTimeFilterPlugin::GetSupportedProtoSpecs(
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
CDeltaTimeFilterPlugin::OnLoad(
	PluginLoadParam*	ioParams )
{
	int	nResult = __super::OnLoad( ioParams );
	if ( nResult != PLUGIN_RESULT_SUCCESS ) {
		return nResult;
	}

	// Todo: allocate resources.

	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnUnload
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnUnload()
{
	// Todo: release resources.

	__super::OnUnload();
	return PLUGIN_RESULT_SUCCESS;
}


#define kOptionsFilename _T("/plugins/findme.xml") 

// -----------------------------------------------------------------------------
//		OnReadPrefs
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnReadPrefs()
{
	HRESULT hr = PLUGIN_RESULT_SUCCESS;

	TCHAR 	szModulePath[MAX_PATH];
	DWORD	cch = ::GetModuleFileName( NULL, szModulePath, MAX_PATH );
	TCHAR *ptr = _tcsrchr( szModulePath, '\\' );
	*ptr = 0;
	CString csPath( szModulePath );
	csPath += kOptionsFilename;

	// writing filters
	try 
	{
		XXMLDoc doc;
		doc.ParseFile( csPath );
		XXMLElement* pRoot = doc.GetRootElement();
		if (pRoot == NULL) return 0;

		SInt32 nCount = pRoot->CountChildren();
		for (SInt32 i=0; i < nCount; i++)
		{
			XXMLElement* pChild = pRoot->GetChild( i );
			if (pChild == NULL) AtlThrow( -1 );
			CFilter* pFilter = new CFilter;
			ASSERT(pFilter);
			if (pFilter == NULL) AtlThrow( -1 );

			pFilter->ReadXML( pChild );
			m_FilterMap.SetAt( pFilter->GetName(), pFilter );
		}
	}
	CATCH_HR(hr)

	return hr;
}


// -----------------------------------------------------------------------------
//		OnWritePrefs
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnWritePrefs()
{
	HRESULT hr = PLUGIN_RESULT_SUCCESS;

	TCHAR 	szModulePath[MAX_PATH];
	DWORD	cch = ::GetModuleFileName( NULL, szModulePath, MAX_PATH );
	TCHAR *ptr = _tcsrchr( szModulePath, '\\' );
	*ptr = 0;
	CString csPath( szModulePath );
	csPath += kOptionsFilename;

	//reading options per target
	try 
	{
		XXMLDoc doc;
		XXMLElement* pRoot = new XXMLElement( kPref_Filters );
		doc.SetRootElement( pRoot );

		POSITION thePos = m_FilterMap.GetStartPosition();
		while (thePos)
		{
			CFilter* pFilter = NULL;
			CString theKey;
			m_FilterMap.GetNextAssoc( thePos, theKey, (void*&)pFilter );
			ASSERT(pFilter);
			if (pFilter == NULL) break;

			XXMLElement* pElement = pFilter->WriteXML();
			pRoot->AddChild( pElement );
		}

		// build the stream
		CByteStream theStream;
		doc.BuildStream( theStream );
		theStream.WriteToFile( csPath );
	}
	CATCH_HR(hr)

	return hr;
}


// -----------------------------------------------------------------------------
//		OnAbout
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnAbout()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CDeltaTimeFilterAbout AboutDialog;
	AboutDialog.DoModal();
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnOptions
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnOptions()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnFilterOptions
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnFilterOptions()
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnCreateContext
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnCreateContext(
	PluginCreateContextParam*	ioParams )
{
	switch (ioParams->fContextFlags)
	{
		case kContextType_CaptureWindow:
		case kContextType_FileWindow:
			break;
		default:
			*(ioParams->fContextPtr) = NULL;	// explicitly set context pointer to null
			return 0;
	}

	CDeltaTimeFilterContext* pContext =
		new CDeltaTimeFilterContext( m_pPeekApp, this );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	if ( pContext ) 
	{
		pContext->Init( ioParams );
		*(ioParams->fContextPtr) = pContext;
		AddListener( pContext );

	}

	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnDisposeContext
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnDisposeContext(
	PluginDisposeContextParam*  ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	try {
		pContext->Term();
		RemoveListener( pContext );
	}
	catch ( int e ) {
		if ( e == -1 ) {
			delete pContext;
		}
	}

	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnNameTableUpdate
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnNameTableUpdate(
	PluginNameTableUpdateParam*	ioParams )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnCreateNewAdapter
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnCreateNewAdapter(
	PluginCreateNewAdapterParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnGetAdapterList
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnGetAdapterList(
	PluginGetAdapterListParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnDeleteAdapter
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnDeleteAdapter(
	PluginDeleteAdapterParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnSetAdapterAttribs
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnSetAdapterAttribs(
	PluginAdapterAttribsParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnGetAdapterAttribs
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnGetAdapterAttribs(
	PluginAdapterAttribsParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnAdapterProperties
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnAdapterProperties(
	PluginAdapterPropertiesParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_ERROR;
}


// -----------------------------------------------------------------------------
//		OnUserDecode
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnUserDecode(
	PluginUserDecodeParam*	ioParams )
{
	// TODO: Add a C decoder here.
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnDecodersLoaded
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnDecodersLoaded()
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnIsMediaSupported
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnIsMediaSupported(
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
CDeltaTimeFilterPlugin::OnReset(
	PluginResetParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnReset( ioParams );
}


// -----------------------------------------------------------------------------
//		OnStartCapture
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnStartCapture(
	PluginStartCaptureParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnStartCapture( ioParams );
}


// -----------------------------------------------------------------------------
//		OnStopCapture
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnStopCapture(
	PluginStopCaptureParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnStopCapture( ioParams );
}


// -----------------------------------------------------------------------------
//		OnProcessPacket
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnProcessPacket(
	PluginProcessPacketParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnProcessPacket( ioParams );
}


// -----------------------------------------------------------------------------
//		OnGetPacketString
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnGetPacketString(
	PluginGetPacketStringParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnGetPacketString( ioParams );
}


// -----------------------------------------------------------------------------
//		OnApply
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnApply(
	PluginApplyParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnApply( ioParams );
}


// -----------------------------------------------------------------------------
//		OnSelect
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnSelect(
	PluginSelectParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnSelect( ioParams );
}


// -----------------------------------------------------------------------------
//		OnPacketsLoaded
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnPacketsLoaded(
	PluginPacketsLoadedParam*	ioParams)
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnPacketsLoaded( ioParams );
}


// -----------------------------------------------------------------------------
//		OnSummary
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnSummary(
	PluginSummaryParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnSummary( ioParams );
}


// -----------------------------------------------------------------------------
//		OnFilter
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnFilter(
	PluginFilterParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnFilter( ioParams );
}


// -----------------------------------------------------------------------------
//		OnGetPacketAnalysis
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnGetPacketAnalysis(
	PluginGetPacketStringParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnGetPacketAnalysis( ioParams );
}


// -----------------------------------------------------------------------------
//		OnDecodePacket
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnDecodePacket(
	PluginDecodePacketParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnDecodePacket( ioParams );
}


// -----------------------------------------------------------------------------
//		OnProcessPluginMessage
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnProcessPluginMessage(
	PluginProcessPluginMessageParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnProcessPluginMessage( ioParams );
}


// -----------------------------------------------------------------------------
//		OnHandleNotify
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterPlugin::OnHandleNotify(
	PluginHandleNotifyParam*	ioParams )
{
	CDeltaTimeFilterContext* pContext =
		(CDeltaTimeFilterContext*) ( ioParams->fContext );

	if ( pContext == NULL ) return PLUGIN_RESULT_ERROR;

	return pContext->OnHandleNotify( ioParams );
}



// -----------------------------------------------------------------------------
//		ListenToMessage
// -----------------------------------------------------------------------------

void 
CDeltaTimeFilterPlugin::ListenToMessage( UInt32 inMessage, void* ioParam )
{

}

