//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "ISR.h"

// Find occurrences of any child ISR.


class ISROr : publicISR
	{
	public:

		ISR ** Terms;
		unsigned NumberOfTerms;
		Location GetStartLocation( );//{return nearestStartLocation;}
		Location GetEndLocation( );// {return nearestEndLocation;}
		Post*Seek( Location target);
			// Seek all the ISRs to the first occurrence beginning at// the target location. Return null if there is no match.
			// The document is the document containing the nearest term.
		 Post*Next( );//{ Do a next on the nearest term, then return// the new nearest match.}

		Post*NextDocument( );
		//{ Seek all the ISRs to the first occurrence just past the end of this document.returnSeek( DocumentEnd->GetEndLocation( ) + 1 );}
	private:
		unsigned nearestTerm;
		// nearStartLocation and nearestEndLocation are// the start and end of the nearestTerm.
		Location nearestStartLocation, nearestEndLocation;

	};

