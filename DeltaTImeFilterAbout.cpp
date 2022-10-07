// ============================================================================
//	DeltaTimeFilterAbout.cpp:
//		implementation of the CDeltaTimeFilterAbout class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#include "stdafx.h"
#include "resource.h"
#include "DeltaTimeFilterAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////////////////////////////////////////////
//		CDeltaTimeFilterAbout
////////////////////////////////////////////////////////////////////////////////

CDeltaTimeFilterAbout::CDeltaTimeFilterAbout(
	CWnd* pParent /*=NULL*/)
	:	CDialog( CDeltaTimeFilterAbout::IDD, pParent )
{
}


// -----------------------------------------------------------------------------
//		DoDataExchange
// -----------------------------------------------------------------------------

void
CDeltaTimeFilterAbout::DoDataExchange(
	CDataExchange*	pDX )
{
	CDialog::DoDataExchange( pDX );
}


BEGIN_MESSAGE_MAP( CDeltaTimeFilterAbout, CDialog )
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////
// CDeltaTimeFilterAbout message handlers
