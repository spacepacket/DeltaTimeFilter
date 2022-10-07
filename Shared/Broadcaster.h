// ============================================================================
//	Broadcaster.h
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2000-2004. All rights reserved.
//	Copyright (c) AG Group, Inc. 1996-2000. All rights reserved.

#ifndef BROADCASTER_H
#define BROADCASTER_H

#include "ArrayEx.h"

class CListener;

class DECLSPEC CBroadcaster
{
public:
	enum
	{
		kMsg_BroadcasterDied	= 'BDIE'
	};


					CBroadcaster();
					CBroadcaster( const CBroadcaster& inOriginal );
	virtual			~CBroadcaster();

	void			AddListener( CListener* inListener );
	void			RemoveListener( CListener* inListener );

	virtual void	StartBroadcasting() { m_bBroadcasting = true; }
	virtual void	StopBroadcasting() { m_bBroadcasting = false; }
	bool			IsBroadcasting() const { return m_bBroadcasting; }

	bool			HasListener( CListener* inListener ) const;

	virtual void	BroadcastMessage( UInt32 inMessage, void* ioParam = NULL );

protected:
	TPtrArrayEx<CListener>	m_Listeners;
	bool					m_bBroadcasting;
};

#endif
