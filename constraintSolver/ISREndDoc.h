//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "ISR.h"

// Find occurrences of document ends.

class ISREndDoc : ISR
	{
	public:
		Location GetCurrentLocation( );
		Location GetPreviousLocation( );
		unsigned GetDocumentLength( );
		unsigned GetTitleLength( );
		unsigned GetUrlLength( );
	};


