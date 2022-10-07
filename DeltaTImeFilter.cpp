// =============================================================================
//	DeltaTimeFilter.cpp
//		implementation of the CDeltaTimeFilterApp class.
// =============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.



#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "DeltaTimeFilter.h"
#include "DeltaTimeFilterPlugin.h"


////////////////////////////////////////////////////////////////////////////////
//		CDeltaTimeFilterApp
////////////////////////////////////////////////////////////////////////////////

CDeltaTimeFilterApp::CDeltaTimeFilterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


BEGIN_MESSAGE_MAP(CDeltaTimeFilterApp, CWinApp)
END_MESSAGE_MAP()

CDeltaTimeFilterApp theApp;


// -----------------------------------------------------------------------------
//		InitInstance
// -----------------------------------------------------------------------------

BOOL
CDeltaTimeFilterApp::InitInstance()
{
	m_Plugin.DllMain( m_hInstance, DLL_PROCESS_ATTACH, 0 );

	return CWinApp::InitInstance();
}

#if defined(_MSC_VER)
#if defined (_WIN64)
#pragma comment(linker, "/EXPORT:PlugInMain=PlugInMain,PRIVATE")
#else
#pragma comment(linker, "/EXPORT:PlugInMain=_PlugInMain@8,PRIVATE")
#endif
#endif


// ----------------------------------------------------------------------------
//		PlugInMain
// ----------------------------------------------------------------------------
extern "C"
int WINAPI
PlugInMain(
	SInt16				inMessage,
	PluginParamBlock*	ioParams)
{
	CPeekPlugin& Plugin = theApp.GetPlugin();
	return Plugin.HandleMessage(inMessage, ioParams);
}
