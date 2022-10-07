// ============================================================================
// DeltaTimeFilterContext.h:
//      interface for the CDeltaTimeFilterContext class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#pragma once

#include "PeekApp.h"
#include "PeekContext.h"
#include "DeltaTimeFilterParent.h"
#include "DeltaTimeFilterTab.h"
#include "Listener.h"

class CDeltaTimeFilterPlugin;

class CDeltaTimeFilterContext :	
	public CPeekContext,
	public CListener
{
protected:
    CDeltaTimeFilterPlugin*		m_pPlugin;
	CDeltaTimeFilterParent			m_TabParent;
	CDeltaTimeFilterTab*			m_pTab;
	UInt64					m_LastTimeStamp;
	int						m_nOperator;
	UInt64					m_nDeltaFilter;

	X_DECLARE_BOOL( Capturing );

public:
					CDeltaTimeFilterContext( CPeekApp* pPeekApp, CDeltaTimeFilterPlugin* pPlugin );
	virtual			~CDeltaTimeFilterContext() {};

	virtual int		Init( PluginCreateContextParam* ioParams );
	virtual int		Term();

	void			ListenToMessage( UInt32 inMessage, void* ioParam );

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
};


///////////////////////////////////////////////////////////////////////////////
//		CDeltaTimeFilterContextList
///////////////////////////////////////////////////////////////////////////////

class CDeltaTimeFilterContextList
	:	public CAtlArray<CDeltaTimeFilterContext*>
{
public:
	void	Remove( CDeltaTimeFilterContext* inContext );
	void	DoNotifyAll( UInt64 inTimeStamp, UInt8 inSeverity,
				const TCHAR* inShortString, const TCHAR* inLongString );
};

