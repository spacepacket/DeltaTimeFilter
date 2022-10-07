// =============================================================================
//	Options.cpp
//		implementation of the COptions class.
// =============================================================================
//	Copyright (c) WildPackets, Inc. 2004. All rights reserved.

#include "StdAfx.h"
#include "Options.h"
#include "ByteStream.h"
#include "DeltaTimeFilter.h"
#include "CatchHR.h"


extern CDeltaTimeFilterApp theApp;


CStringA	g_strTrue( "True" );
CStringA	g_strFalse( "False" );



// -----------------------------------------------------------------------------
//		ReadXML
// -----------------------------------------------------------------------------

void
CFilter::ReadXML( XXMLElement* pElement )
{
	HRESULT hr = 0;
	try
	{
		XString theValue;
		CString csValue;

		BOOL bResult = pElement->GetNamedAttributeValue( kPref_Name, theValue );
		csValue = theValue;
		if (bResult) SetName( csValue );

		bResult = pElement->GetNamedAttributeValue( kPref_Filter, theValue );
		csValue = theValue;
		if (bResult) SetFilter( csValue );

		bResult = pElement->GetNamedAttributeValue( kPref_Comment, theValue );
		csValue = theValue;
		if (bResult) SetComment( csValue );
	}
	CATCH_HR(hr)
}

// -----------------------------------------------------------------------------
//		WriteXML
// -----------------------------------------------------------------------------

XXMLElement*
CFilter::WriteXML()
{
	HRESULT hr = 0;
	XXMLElement* pElement = NULL;

	try
	{
		pElement = new XXMLElement( kPref_Options );
		ASSERT(pElement);
		if (pElement == NULL) AtlThrow(-1);

		BOOL bResult = pElement->AddAttribute( kPref_Name, GetName() );
		if (bResult == FALSE) AtlThrow(-1);

		bResult = pElement->AddAttribute( kPref_Filter, GetFilter() );
		if (bResult == FALSE) AtlThrow(-1);

		bResult = pElement->AddAttribute( kPref_Comment, GetComment() );
		if (bResult == FALSE) AtlThrow(-1);
	}
	CATCH_HR(hr)

	return pElement;
}



