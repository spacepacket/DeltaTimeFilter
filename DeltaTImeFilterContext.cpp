// ============================================================================
// DeltaTimeFilterContext.cpp:
//      implementation of the CDeltaTimeFilterContext class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#include "stdafx.h"
#include "resource.h"
#include "DeltaTimeFilterContext.h"
#include "DeltaTimeFilterPlugin.h"
#include "DeltaTimeFilterParent.h"
#include "DeltaTimeFilterTab.h"
#include "Memutil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif




//////////////////////////////////////////////////////////////////////
//		CDeltaTimeFilterContext
//////////////////////////////////////////////////////////////////////

CDeltaTimeFilterContext::CDeltaTimeFilterContext(
	CPeekApp*		pPeekApp,
	CDeltaTimeFilterPlugin*	pPlugin )
	:	m_pPlugin( pPlugin )
{
	m_LastTimeStamp		= 0;
	m_nOperator			= 0;
	m_nDeltaFilter		= 0;
}


// -----------------------------------------------------------------------------
//		Init
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::Init(
	PluginCreateContextParam*	ioParams )
{
	CPeekContext::Init( ioParams );

	if (ioParams->fContextFlags == kContextType_Global) 
		return 0;


	HWND	hTabWnd = NULL;
	int		nResult = DoAddTab(
		_T( "DeltaTimeFilter" ),
		_T( "STATIC" ),
		(void**) &hTabWnd );
	ASSERT( nResult == 0 );
	if ( nResult != 0 ) return PLUGIN_RESULT_ERROR;
	ASSERT( hTabWnd != NULL );
	if ( hTabWnd == NULL ) return PLUGIN_RESULT_ERROR;

	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	// Subclass the static window Peek created.
	#undef SubclassWindow					// The compiler picks up this macro
	m_TabParent.SubclassWindow( hTabWnd );	// instead of this function.

	// Create a dialog to be embedded in the Parent window. The Parent window will delete it.
	m_pTab = new CDeltaTimeFilterTab;
	ASSERT( m_pTab != NULL );
	if ( m_pTab == NULL ) return PLUGIN_RESULT_ERROR;

	SetCapturing( FALSE );

	m_pTab->SetContext( this );
	m_pTab->Create( IDD_DeltaTimeFilter_TAB, &m_TabParent );
	m_TabParent.SetChild( m_pTab );
	m_pTab->ShowWindow( SW_SHOW );
	
	return PLUGIN_RESULT_SUCCESS;
}



// -----------------------------------------------------------------------------
//      Term
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::Term( )
{
	CPeekContext::Term();

	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnReset
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnReset(
	PluginResetParam*	ioParams )
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnStartCapture
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnStartCapture(
	PluginStartCaptureParam*	ioParams )
{
	SetCapturing( TRUE );
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnStopCapture
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnStopCapture(
	PluginStopCaptureParam*	ioParams )
{
	SetCapturing( FALSE );
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnProcessPacket
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnProcessPacket(
	PluginProcessPacketParam*	ioParams )
{
	USES_CONVERSION;

	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//      OnGetPacketString
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnGetPacketString(
	PluginGetPacketStringParam*	ioParams )
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnApply
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnApply(
	PluginApplyParam*	ioParams )
{
	if ( ioParams->fCommand == kApplyMsg_Start )	return PLUGIN_RESULT_SUCCESS;
	if ( ioParams->fCommand == kApplyMsg_End )		return PLUGIN_RESULT_SUCCESS;
	if ( ioParams->fCommand != kApplyMsg_Packet )	return -1;
	if ( ioParams->fPacket == NULL )				return -1;
    return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnSelect
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnSelect(
	PluginSelectParam*	ioParams )
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnPacketsLoaded
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnPacketsLoaded(
	PluginPacketsLoadedParam*	/* ioParams */ )
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnSummary
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnSummary(
	PluginSummaryParam*	ioParams )
{


	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnFilter
// -----------------------------------------------------------------------------

#define kLessThan		0
#define kGreaterThan	1

int
CDeltaTimeFilterContext::OnFilter(
	PluginFilterParam*	ioParams )
{
	USES_CONVERSION;
	int	ret = PLUGIN_PACKET_REJECT;

	if (m_LastTimeStamp == 0 || m_LastTimeStamp > ioParams->fPacket->fTimeStamp)
	{
		TCHAR buffer[1025];
		int i = m_pTab->m_DeltaTimeCtrl.GetLine(0, buffer);
		if (i == 0)
		{
			ioParams->fBytesAccepted = ioParams->fPacket->fPacketLength;
			ret = PLUGIN_PACKET_ACCEPT;
		}
		buffer[i] = 0;
		UInt64 nDeltaFilter = static_cast<UInt64>(_ttoi64(buffer));
		m_nDeltaFilter = nDeltaFilter *= 1000000;

		int nOperator = m_pTab->m_OperatorCtrl.GetCheck();
		m_nOperator = (nOperator == 1) ? kLessThan : kGreaterThan;

		m_LastTimeStamp = 0;
		ret = PLUGIN_PACKET_REJECT;
	}
	else
	{
		UInt64 nDeltaTime = ioParams->fPacket->fTimeStamp - m_LastTimeStamp;

		if (m_nOperator == kLessThan && nDeltaTime < m_nDeltaFilter )
		{
			ioParams->fBytesAccepted = ioParams->fPacket->fPacketLength;
			ret = PLUGIN_PACKET_ACCEPT;
		}
		else
		if (m_nOperator == kGreaterThan && nDeltaTime > m_nDeltaFilter )
		{
			ioParams->fBytesAccepted = ioParams->fPacket->fPacketLength;
			ret = PLUGIN_PACKET_ACCEPT;
		}
	}

	m_LastTimeStamp = ioParams->fPacket->fTimeStamp;
	return ret;
}


// -----------------------------------------------------------------------------
//      OnGetPacketAnalysis
// -----------------------------------------------------------------------------
// Called when a packet needs to be displayed in the main packet list.  Plug-ins
// will only get packets which correspond the the ProtoSpecs they supplied
// during Load (in GetSupportedProtoSpecs).

int
CDeltaTimeFilterContext::OnGetPacketAnalysis(
	PluginGetPacketStringParam*	ioParams )
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnDecodePacket
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnDecodePacket(
	PluginDecodePacketParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnProcessPluginMessage
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnProcessPluginMessage(
	PluginProcessPluginMessageParam*	/*ioParams*/ )
{
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		OnHandleNotify
// -----------------------------------------------------------------------------

int
CDeltaTimeFilterContext::OnHandleNotify(
	PluginHandleNotifyParam*	/*ioParams*/ )
{
	// TODO: Add code here to handle notifications.
	return PLUGIN_RESULT_SUCCESS;
}


// -----------------------------------------------------------------------------
//		ListenToMessage
// -----------------------------------------------------------------------------

void 
CDeltaTimeFilterContext::ListenToMessage( UInt32 inMessage, void* ioParam )
{
	ASSERT(m_pTab);
	if (m_pTab == NULL) return;

}