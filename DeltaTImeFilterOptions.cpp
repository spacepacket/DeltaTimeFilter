// ============================================================================
//	DeltaTimeFilterOptions.cpp:
//		implementation of the CDeltaTimeFilterOptions class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#include "stdafx.h"
#include "resource.h"
#include "DeltaTimeFilterOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
//		CDeltaTimeFilterOptions
/////////////////////////////////////////////////////////////////////////////

CDeltaTimeFilterOptions::CDeltaTimeFilterOptions(
	CWnd* pParent /*=NULL*/ )
	:	CDialog( CDeltaTimeFilterOptions::IDD, pParent )
{
	m_Dummy = 0;
}


// -----------------------------------------------------------------------------
//		DoDataExchange
// -----------------------------------------------------------------------------

void
CDeltaTimeFilterOptions::DoDataExchange(
	CDataExchange*	pDX )
{
	CDialog::DoDataExchange(pDX);
}


////////////////////////////////////////////////////////////////////////////////
// CDeltaTimeFilterOptions message handlers

BEGIN_MESSAGE_MAP(CDeltaTimeFilterOptions, CDialog)
END_MESSAGE_MAP()


// -----------------------------------------------------------------------------
//		OnInitDialog
// -----------------------------------------------------------------------------

BOOL
CDeltaTimeFilterOptions::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}
