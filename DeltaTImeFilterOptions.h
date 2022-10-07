// ============================================================================
//	DeltaTimeFilterOptions.h:
//		interface for the CDeltaTimeFilterOptions class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#pragma once


/////////////////////////////////////////////////////////////////////////////
// CDeltaTimeFilterOptions
/////////////////////////////////////////////////////////////////////////////

class CDeltaTimeFilterOptions
	:	public CDialog
{
protected:
	virtual void	DoDataExchange( CDataExchange* pDX );
	virtual BOOL	OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	enum { IDD = IDD_OPTIONS };

	;				CDeltaTimeFilterOptions( CWnd* pParent = NULL );
	virtual			~CDeltaTimeFilterOptions() {};

	UInt32			m_Dummy;
};
