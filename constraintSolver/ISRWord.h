//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "ISR.h"

//Find occurrences of individual words

class ISRWord : ISR
	{
	public:
		unsigned GetDocumentCount( );
		unsigned GetNumberOfOccurrences( );
		virtual Post *GetCurrentPost( );

	};


