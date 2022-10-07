// ============================================================================
// DeltaTimeFilterTab.cpp:
//      implementation of the CDeltaTimeFilterTab class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#include "stdafx.h"
#include "DeltaTimeFilterTab.h"
#include "DeltaTimeFilterContext.h"
#include "XMLBuilder.h"
#include "DeltaTimeFilter.h"
#include "Options.h"
#include "CatchHR.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CDeltaTimeFilterApp	theApp;

//////////////////////////////////////////////////////////////////////
//		CDeltaTimeFilterTab
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CDeltaTimeFilterTab, CDialog)

CDeltaTimeFilterTab::CDeltaTimeFilterTab(
	CWnd*	pParent /* NULL */ )
	:	CDialog( CDeltaTimeFilterTab::IDD, pParent )
	, m_DeltaTimeFilter(_T(""))
	, m_Operator(0)
{

}

CDeltaTimeFilterTab::~CDeltaTimeFilterTab()
{
	
}


// -----------------------------------------------------------------------------
//		DoDataExchange
// -----------------------------------------------------------------------------

void
CDeltaTimeFilterTab::DoDataExchange(
	CDataExchange*	pDX )
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DeltaTimeFilter);
	DDX_Radio(pDX, IDC_LESS_THAN, m_Operator);
	DDX_Control(pDX, IDC_EDIT1, m_DeltaTimeCtrl);
	DDX_Control(pDX, IDC_LESS_THAN, m_OperatorCtrl);
}


// -----------------------------------------------------------------------------
//		OnInitDialog
// -----------------------------------------------------------------------------

BOOL
CDeltaTimeFilterTab::OnInitDialog()
{	  
	__super::OnInitDialog();
	m_DeltaTimeFilter.SetString(_T("0")); 
	return TRUE;  // return TRUE unless you set the focus to a control
}


// -----------------------------------------------------------------------------
//		Reset
// -----------------------------------------------------------------------------

void
CDeltaTimeFilterTab::Reset()
{

}

// -----------------------------------------------------------------------------
//		Message Map
// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CDeltaTimeFilterTab, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// -----------------------------------------------------------------------------
//		OnSize
// -----------------------------------------------------------------------------

void 
CDeltaTimeFilterTab::OnSize(UINT nType, int cx, int cy) 
{
	__super::OnSize(nType, cx, cy);

	if (GetSafeHwnd() == NULL) return;

}

