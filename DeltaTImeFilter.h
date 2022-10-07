// ============================================================================
//	DeltaTimeFilter.h
//		interface for the CDeltaTimeFilterApp class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2006. All rights reserved.

#pragma once

#include "DeltaTimeFilterPlugin.h"

class CDeltaTimeFilterApp
	:	public CWinApp
{
protected:
	DECLARE_MESSAGE_MAP()

public:
	CDeltaTimeFilterPlugin	m_Plugin;

	;				CDeltaTimeFilterApp();

	CDeltaTimeFilterPlugin&		GetPlugin() { return m_Plugin; };

	virtual BOOL	InitInstance();
};
