// ============================================================================
//	Listener.h
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2000-2004. All rights reserved.
//	Copyright (c) AG Group, Inc. 1996-2000. All rights reserved.

#ifndef LISTENER_H
#define LISTENER_H

#include "ArrayEx.h"

class CBroadcaster;

class DECLSPEC CListener
{
	friend class CBroadcaster;
public:
					CListener();
					CListener( const CListener& inOriginal );
	virtual			~CListener();

	virtual void	StartListening() { m_bListening = true; }
	virtual void	StopListening() { m_bListening = false; }
	bool			IsListening() const { return m_bListening; }

	bool			HasBroadcaster( CBroadcaster* inBroadcaster ) const;

	virtual void	ListenToMessage( UInt32 inMessage, void* ioParam ) = 0;

protected:
	TPtrArrayEx<CBroadcaster>	m_Broadcasters;
	bool						m_bListening;

	void			AddBroadcaster( CBroadcaster* inBroadcaster );
	void			RemoveBroadcaster( CBroadcaster* inBroadcaster );
};

#endif
