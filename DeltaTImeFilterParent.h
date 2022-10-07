// ============================================================================
// DeltaTimeFilterParent.h:
//      interface for the CDeltaTimeFilterParent class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#pragma once

//////////////////////////////////////////////////////////////////////
//		CDeltaTimeFilterParent
//////////////////////////////////////////////////////////////////////

class CDeltaTimeFilterParent
	:	public CStatic
{
protected:
	DECLARE_DYNAMIC(CDeltaTimeFilterParent)

	CWnd*	m_pChild;

public:
	;			CDeltaTimeFilterParent() : m_pChild( NULL ) {}
	virtual		~CDeltaTimeFilterParent() {}

	void		SetChild( CWnd* inTab );

	DECLARE_MESSAGE_MAP()

	afx_msg void	OnSize( UINT nType, int cx, int cy );
};
