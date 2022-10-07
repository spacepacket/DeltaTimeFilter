// ============================================================================
//	Listener.cpp
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2000-2005. All rights reserved.
//	Copyright (c) AG Group, Inc. 1996-2000. All rights reserved.

#include "stdafx.h"
#include "Broadcaster.h"
#include "Listener.h"

#if defined(_DEBUG) && defined(_AFX)
#define new DEBUG_NEW
#endif

// -----------------------------------------------------------------------------
//		CListener
// -----------------------------------------------------------------------------

CListener::CListener()
	: m_bListening( true )
{
}


// -----------------------------------------------------------------------------
//		CListener(const CListener&)
// -----------------------------------------------------------------------------

CListener::CListener(
	const CListener&	inOriginal )
{
	m_bListening = inOriginal.m_bListening;
}


// -----------------------------------------------------------------------------
//		~CListener
// -----------------------------------------------------------------------------

CListener::~CListener()
{
	// Detach from all broadcasters.
	UInt32	nCount = m_Broadcasters.GetCount();
	for ( SInt32 i = 0; i < (SInt32) nCount; i++ )
	{
		// Get the next broadcaster.
		CBroadcaster*	pBroadcaster = m_Broadcasters.GetItemPtr( CArrayEx::kArrayIndex_First );
		ASSERT( pBroadcaster != NULL );
		if ( pBroadcaster != NULL )
		{
			// Tell the broadcaster to remove this listener.
			pBroadcaster->RemoveListener( this );
		}
	}
}


// -----------------------------------------------------------------------------
//		HasBroadcaster
// -----------------------------------------------------------------------------

bool
CListener::HasBroadcaster(
	CBroadcaster*	inBroadcaster ) const
{
	// Sanity check.
	ASSERT( inBroadcaster != NULL );

	return (m_Broadcasters.GetIndexOf( inBroadcaster ) != CArrayEx::kArrayIndex_Invalid);
}


// -----------------------------------------------------------------------------
//		ListenToMessage
// -----------------------------------------------------------------------------

void
CListener::ListenToMessage(
	UInt32	/*inMessage*/,
	void*	/*ioParam*/ )
{
	// Default implementation does nothing.
	// Note: this is only here so any derived class can call __super::ListenToMessage()
}


// -----------------------------------------------------------------------------
//		AddBroadcaster
// -----------------------------------------------------------------------------

void
CListener::AddBroadcaster(
	CBroadcaster*	inBroadcaster )
{
	// Sanity check.
	ASSERT( inBroadcaster != NULL );
	if ( inBroadcaster == NULL ) return;

//	TRACE1( "CListener::AddBroadcaster 0x%8.8X\n", inBroadcaster );

	// Try and find the broadcaster already in the list.
	if ( !HasBroadcaster( inBroadcaster ) )
	{
		// Add the broadcaster to the list.
		m_Broadcasters.AddItem( inBroadcaster );
	}
}


// -----------------------------------------------------------------------------
//		RemoveBroadcaster
// -----------------------------------------------------------------------------

void
CListener::RemoveBroadcaster(
	CBroadcaster*	inBroadcaster )
{
	// Sanity check.
	ASSERT( inBroadcaster != NULL );

//	TRACE1( "CListener::RemoveBroadcaster 0x%8.8X\n", inBroadcaster );

	// Try and find the broadcaster in the list.
	SInt32	nIndex = m_Broadcasters.GetIndexOf( inBroadcaster );

	if ( nIndex != CArrayEx::kArrayIndex_Invalid )
	{
		// Remove the broadcaster from the list.
		m_Broadcasters.RemoveItems( 1, nIndex );
	}
}
