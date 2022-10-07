// ============================================================================
// DeltaTimeFilterTab.h:
//      interface for the CDeltaTimeFilterTab class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#pragma once

#include "resource.h"
#include "Options.h"


//////////////////////////////////////////////////////////////////////
//		CDeltaTimeFilterTab
//////////////////////////////////////////////////////////////////////

class CDeltaTimeFilterContext;
class CFilterUpdateMessage;

class CDeltaTimeFilterTab :	public CDialog
{
private:
	CDeltaTimeFilterContext*	m_pContext;

public:
	CString m_DeltaTimeFilter;
	int		m_Operator;
	CEdit	m_DeltaTimeCtrl;
	CButton m_OperatorCtrl;

protected:
	DECLARE_DYNAMIC(CDeltaTimeFilterTab)

	virtual void DoDataExchange( CDataExchange* pDX );    // DDX/DDV support

public:
	CDeltaTimeFilterTab( CWnd* pParent = NULL );
	~CDeltaTimeFilterTab();

	void SetContext( CDeltaTimeFilterContext* pContext )
	{
		m_pContext = pContext;
	}

	enum { IDD = IDD_DeltaTimeFilter_TAB };

	virtual BOOL	OnInitDialog();

	void			Reset();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnSize( UINT nType, int cx, int cy );
};
