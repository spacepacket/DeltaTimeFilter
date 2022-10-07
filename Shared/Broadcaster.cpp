// =============================================================================
//	Broadcaster.cpp
// =============================================================================
//	Copyright (c) WildPackets, Inc. 2000-2005. All rights reserved.
//	Copyright (c) AG Group, Inc. 1996-2000. All rights reserved.

#include "stdafx.h"
#include "Listener.h"
#include "Broadcaster.h"

#if defined(_DEBUG) && defined(_AFX)
#define new DEBUG_NEW
#endif

// -----------------------------------------------------------------------------
//		CBroadcaster
// -----------------------------------------------------------------------------

CBroadcaster::CBroadcaster()
	: m_bBroadcasting( true )
{
}


// -----------------------------------------------------------------------------
//		CBroadcaster(const CBroadcaster&)
// -----------------------------------------------------------------------------

CBroadcaster::CBroadcaster(
	const CBroadcaster&	inOriginal )
{
	m_bBroadcasting = inOriginal.m_bBroadcasting;
}


// -----------------------------------------------------------------------------
//		~CBroadcaster
// -----------------------------------------------------------------------------

CBroadcaster::~CBroadcaster()
{
	// Notify listeners that the broadcaster is going away.
	BroadcastMessage( kMsg_BroadcasterDied, this );

	// Detach from all listeners.
	UInt32	nCount = m_Listeners.GetCount();
	for ( SInt32 i = 0; i < (SInt32) nCount; i++ )
	{
		// Get the next listener.
		CListener*	pListener = m_Listeners.GetItemPtr( CArrayEx::kArrayIndex_First );
		ASSERT( pListener != NULL );
		if ( pListener != NULL )
		{
			// Tell the listener to remove this broadcaster.
			pListener->RemoveBroadcaster( this );

			// Remove the listener from the list.
			m_Listeners.RemoveItems( 1, CArrayEx::kArrayIndex_First );
		}
	}
}


// -----------------------------------------------------------------------------
//		AddListener
// -----------------------------------------------------------------------------

void
CBroadcaster::AddListener(
	CListener*	inListener )
{
	// Sanity check.
	ASSERT( inListener != NULL );
	if ( inListener == NULL ) return;

//	TRACE1( "CBroadcaster::AddListener 0x%8.8X\n", inListener );

	// Try and find the listener already in the list.
	if ( !HasListener( inListener ) )
	{
		// Add the listener to the list.
		m_Listeners.AddItem( inListener );

		// Hook up this broadcaster to the listener.
		inListener->AddBroadcaster( this );
	}
}


// -----------------------------------------------------------------------------
//		RemoveListener
// -----------------------------------------------------------------------------

void
CBroadcaster::RemoveListener(
	CListener*	inListener )
{
	// Sanity check.
	ASSERT( inListener != NULL );

//	TRACE1( "CBroadcaster::RemoveListener 0x%8.8X\n", inListener );

	// Try and find the listener in the list.
	SInt32	nIndex = m_Listeners.GetIndexOf( inListener );

	if ( nIndex != CArrayEx::kArrayIndex_Invalid )
	{
		// Remove the listener from the list.
		m_Listeners.RemoveItems( 1, nIndex );

		// Unhook this broadcaster from listener.
		inListener->RemoveBroadcaster( this );
	}
}


// -----------------------------------------------------------------------------
//		HasListener
// -----------------------------------------------------------------------------

bool
CBroadcaster::HasListener(
	CListener*	inListener ) const
{
	// Sanity check.
	ASSERT( inListener != NULL );

	return (m_Listeners.GetIndexOf( inListener ) != CArrayEx::kArrayIndex_Invalid);
}


// -----------------------------------------------------------------------------
//		BroadcastMessage
// -----------------------------------------------------------------------------

void
CBroadcaster::BroadcastMessage(
	UInt32	inMessage,
	void*	ioParam )
{
	if ( IsBroadcasting() )
	{
		// Broadcast to all listening listeners.
		UInt32	nCount = m_Listeners.GetCount();
		for ( SInt32 i = 0; i < (SInt32) nCount; i++ )
		{
			// Get the next listener.
			CListener*	pListener = m_Listeners.GetItemPtr( i );
			ASSERT( pListener != NULL );

			// Check if the listener is listening.
			if ( (pListener != NULL) && pListener->IsListening() )
			{
				// Pass the message to the listener.
				pListener->ListenToMessage( inMessage, ioParam );
			}
		}
	}
}
