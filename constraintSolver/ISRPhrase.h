//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "ISR.h"

// Find occurrences of all child ISRs as a phrase

class ISRPhrase : ISR
	{
	public:
		ISR **Terms;
		unsigned NumberOfTerms;
		Post *Seek( Location target )
			{
	// 1. Seek all ISRs to the first occurrence beginning at
	//    the target location.
	// 2. Pick the furthest term and attempt to seek all
	//    the other terms to the first location beginning
	//    where they should appear relative to the furthest
	//    term.
	// 3. If any term is past the desired location, return
	//    to step 2.
	// 4. If any ISR reaches the end, there is no match.
			}


		Post *Next( )
			{
	// Finds overlapping phrase matches. return Seek( nearestStartLocation + 1 );
			}

	};


