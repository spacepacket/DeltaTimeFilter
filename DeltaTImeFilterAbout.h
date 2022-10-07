// ============================================================================
//	DeltaTimeFilterAbout.h:
//		interface for the CDeltaTimeFilterAbout class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDeltaTimeFilterAbout dialog

class CDeltaTimeFilterAbout
	:	public CDialog
{
protected:
	enum { IDD = IDD_ABOUT };

	DECLARE_MESSAGE_MAP()

	virtual void	DoDataExchange( CDataExchange* pDX );

public:
	;				CDeltaTimeFilterAbout( CWnd* pParent = NULL );
};
