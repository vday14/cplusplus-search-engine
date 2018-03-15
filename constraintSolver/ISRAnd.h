//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "ISR.h"


//Find occurrences of all child ISRs within a single document


class ISRAnd : ISR
	{
	public:
		ISR **Terms;
		unsigned NumberOfTerms;
		Post *Seek( Location target )
			{
	// 1. Seek all the ISRs to the first occurrence beginning at
	//    the target location.
	// 2. Move the document end ISR to just past the furthest
	//    word, then calculate the document begin location.
	// 3. Seek all the other terms to past the document begin.
	// 4. If any term is past the document end, return to
	//    step 2.
	// 5. If any ISR reaches the end, there is no match.
			}
		Post *Next( )
			{
			return Seek( nearestStartLocation + 1 );
			}


	private:
		unsigned nearestTerm, farthestTerm;
		Location nearestStartLocation, nearestEndLocation;

		};


