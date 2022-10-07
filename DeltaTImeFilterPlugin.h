// ============================================================================
//	DeltaTimeFilterPlugin.h
//		interface for the CDeltaTimeFilterPlugin class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#pragma once

#include "PeekPlugin.h"
#include "DeltaTimeFilterContext.h"
#include "DeltaTimeFilterOptions.h"
#include "Listener.h"
#include "Broadcaster.h"

const UInt16	kAttributes =
	kPluginAttr_ProcessPackets |
	kPluginAttr_Filters |
	kPluginAttr_HandlesSummaries |
	kPluginAttr_HandlesApply;

const UInt16	kSupportedActions = kPluginAction_Display | kPluginAction_Notify;
const UInt16	kDefaultActions = kPluginAction_Display | kPluginAction_Notify;



#define kAddFilter			1
#define kDeleteFilter		2
#define kUpdateFilter		3
#define kDeleteAllFilters	4

class CFilterUpdateMessage
{
public:
	X_DECLARE_PTR( CFilter, Filter );
	X_DECLARE_OBJ( CString, OldName );
};



class CDeltaTimeFilterPlugin :	
	public CPeekPlugin,
	public CListener,
	public CBroadcaster
{
protected:
	PluginID			s_ID;
	CMapStringToPtr		m_FilterMap;

	void ListenToMessage( UInt32 inMessage, void* ioParam );

public:
	;				CDeltaTimeFilterPlugin();
	virtual			~CDeltaTimeFilterPlugin() {};

	CMapStringToPtr* GetFilterMap() { return &m_FilterMap; }

	virtual void	GetName( TCHAR* outName, int nBufSize ) const;
	virtual void	GetID( PluginID* outID ) const { *outID = s_ID; };
	virtual UInt16	GetAttributes() const { return kAttributes; };
	virtual UInt16	GetSupportedActions() const { return kSupportedActions; };
	virtual UInt16	GetDefaultActions() const { return kDefaultActions; };
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
};
