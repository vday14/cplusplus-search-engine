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

	ISROr ( vector<ISR * > InputTerms );

	Location First ( ) override;
	Location Next ( ) override;
	Location NextDocument ( ) override;
	Location Seek ( Location target ) override;
	Location GetEndDocument ( ) override;

	Location GetCurrentLocation();

	Location GetStartLocation ( );
	Location GetEndLocation ( );


private:
	ISR *nearestTerm;
	// nearStartLocation and nearestEndLocation are// the start and end of the nearestTerm.
	Location nearestStartLocation, nearestEndLocation;

	};

