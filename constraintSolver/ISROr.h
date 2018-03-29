//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "ISR.h"
#include <vector>
// Find occurrences of any child ISR.
using namespace std;
class ISROr : public ISR
	{
public:

	vector<ISR*>Terms;
	unsigned NumberOfTerms;

	Location GetCurrentLocation();

	Location GetStartLocation ( );

	Location GetEndLocation ( );

	Location Seek ( Location target );

	//ISR *GetCurrentEndDoc ( );


	Location First ( ) ;

	Location Next ( );
	//{ Do a next on the nearest term, then return// the new nearest match.}
	//next on nearest term, return nearest temr


	Location NextDocument ( );
	//
	// 	{ Seek all the ISRs to the first occurrence just past the end of this document.returnSeek( DocumentEnd->GetEndLocation( ) + 1 );}


	ISROr ( vector<ISR * > InputTerms ) : Terms( InputTerms )
		{

		for(auto currentTerm : InputTerms)
			{
			currentTerm->First( );
			Location currentLocation = currentTerm->currentLocation;
			if ( currentLocation < nearestStartLocation )
				{
				nearestTerm = currentTerm;
				nearestStartLocation = currentLocation;

				}
			if ( currentLocation > nearestEndLocation )
				{
				nearestEndLocation = currentLocation;
				}
			++NumberOfTerms;
			currentTerm++;

		}

		}

private:
	ISR *nearestTerm;
	// nearStartLocation and nearestEndLocation are// the start and end of the nearestTerm.
	Location nearestStartLocation, nearestEndLocation;

	};

