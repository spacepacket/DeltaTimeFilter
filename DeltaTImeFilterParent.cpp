// ============================================================================
// DeltaTimeFilterParent.cpp:
//      implementation of the CDeltaTimeFilterParent class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#include "stdafx.h"
#include "DeltaTimeFilterParent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
//		CDeltaTimeFilterParent
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CDeltaTimeFilterParent, CStatic)


// -----------------------------------------------------------------------------
//		SetTab
// -----------------------------------------------------------------------------

void
CDeltaTimeFilterParent::SetChild(
	CWnd* inChild )
{
	m_pChild = inChild;
}
							   


// -----------------------------------------------------------------------------
//		Message Map
// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CDeltaTimeFilterParent, CStatic)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// -----------------------------------------------------------------------------
//		OnSize
// -----------------------------------------------------------------------------

void
CDeltaTimeFilterParent::OnSize(
	UINT	nType,
	int		cx,
	int		cy )
{
	CStatic::OnSize( nType, cx, cy );

	if ( m_pChild != NULL ) {
		m_pChild->MoveWindow( 0, 0, cx, cy );
	}
}
