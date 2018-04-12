//
// Created by Jake Close on 3/13/18.
//

#include "ISROr.h"
#include <cassert>

ISROr::ISROr( vector < ISR * > InputTerms ) : Terms( InputTerms )
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






Location ISROr::Seek( Location target )
	{


	//Todo
	// 1. Seek all the ISRs to the first occurrence beginning at
	//    the target location.
	// 2. Move the document end ISR to just past the furthest
	//    word, then calculate the document begin location.
	// 3. Seek all the other terms to past the document begin.
	// 4. If any term is past the document end, return to
	//    step 2.
	// 5. If any ISR reaches the end, there is no match.

	Location nearest = MAX_Location ;


		//find nearest & furthest ISR
		for ( auto isr : Terms )
			{
			Location temp = isr->Seek( target );
			if ( temp < nearest )
				{
				nearest = temp;
				nearestTerm = isr;
				}

			}
		return nearest;







	}

ISREndDoc *ISROr::GetEndDocument()
	{
	//What does currentLocation hold?  When is it updated?
	return nearestTerm->GetEndDocument();
	}



