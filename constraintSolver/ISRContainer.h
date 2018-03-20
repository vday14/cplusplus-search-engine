//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "ISR.h"
#include "ISREndDoc.h"

//Find occurrences of contained ISRs in a single document not containing any excluded ISRs.

class ISRContainer : ISR
	{
public:
	ISR **Contained,
			*Excluded; ISREndDoc *EndDoc; unsigned CountContained,
			CountExcluded; Location Next( );

	Post *Seek( Location target )
		{
// 1. Seek all the included ISRs to the first occurrence beginning at
//    the target location.
// 2. Move the document end ISR to just past the furthest
//    contained ISR, then calculate the document begin location.
// 3. Seek all the other contained terms to past the document begin.
// 4. If any contained erm is past the document end, return to
//    step 2.
// 5. If any ISR reaches the end, there is no match.
// 6. Seek all the excluded ISRs to the first occurrence beginning at
//    the document begin location.
// 7. If any excluded ISR falls within the document, reset the
//    target to one past the end of the document and return to
//    step 1.
		};


	Post *Next( )
		{
		Seek( Contained[ nearestContained ]->GetStartlocation( ) + 1 );
		}


private:
	unsigned nearestTerm, farthestTerm;
	Location nearestStartLocation, nearestEndLocation;
	};

	};


