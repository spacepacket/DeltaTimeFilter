// ============================================================================
//	Options.h
//		interface for the COptions class.
// ============================================================================
//	Copyright (c) WildPackets, Inc. 2004. All rights reserved.

#pragma once

#include "XRefCounter.h"
#include "XMLDoc.h"

class	CPeekPlugin;

#define kPref_Filters				_T( "Filters" )
#define kPref_Options				_T( "Options" )
#define kPref_Name					_T( "Name" )
#define kPref_Filter				_T( "Filter" )
#define kPref_Comment				_T( "Comment" )




// -----------------------------------------------------------------------------
//		CFilter
// -----------------------------------------------------------------------------


class CFilter
{
public:

	X_DECLARE_OBJ( CString, Name );
	X_DECLARE_OBJ( CString, Filter );
	X_DECLARE_OBJ( CString, Comment );

	X_DECLARE_COUNTER( Count );

	void	operator=( CFilter& in )
	{
		CopyFilter( in );
	}

	void CopyFilter( CFilter& in )
	{
		SetName( in.GetName() );
		SetFilter( in.GetFilter() );
		SetComment( in.GetComment() );
	}


	CFilter()
	{
		m_nCount = 0;
	}

	~CFilter() {}

	XXMLElement*	WriteXML();
	void			ReadXML(XXMLElement* pElement);
};
