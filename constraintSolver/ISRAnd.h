//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "ISR.h"
#include <vector>

using namespace std;
//Find occurrences of all child ISRs within a single document

class ISRAnd : ISR
	{
public:
	vector<ISR*>Terms;
	unsigned NumberOfTerms;

	ISRAnd ( vector<ISR * > InputTerms );

	Location First ( ) override;
	Location Next ( ) override;
	Location NextDocument ( ) override;
	Location Seek ( Location target ) override;
	Location GetEndDocument ( ) override;
	Location GetCurrentLocation();



private:
	ISR *nearestTerm;
	// nearStartLocation and nearestEndLocation are// the start and end of the nearestTerm.
	Location nearestStartLocation, nearestEndLocation;

	};


