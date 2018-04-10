//
// Created by Jake Close on 3/13/18.
//

#include "ISRPhrase.h"


void ISRPhrase::ISRPhrase( vector < ISR * > InputTerms )
	{
	assert( InputTerms.size( ) > 1 );

	Location first = MAX_Location;

	for ( auto isr : Terms )
		{
		Location temp = isr->currentLocation;
		if ( temp < first )
			{
			first = temp;
			}
		}


	//fixme should this return the nearest location of one subterm or the nearest location all the terms match?
	currentLocation = Seek( first  );
	return;


	}


Location ISRPhrase::Seek( Location target )
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

ISREndDoc * ISRPhrase::GetEndDocument ( )
	{



	}