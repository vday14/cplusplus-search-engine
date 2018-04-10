//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "ISR.h"

// Find occurrences of all child ISRs as a phrase

class ISRPhrase : ISR
	{
public:

	vector< ISR* >Terms;
	unsigned NumberOfTerms;

	ISRPhrase ( vector<ISR * > InputTerms );

	Location Seek ( Location target ) override;
	ISREndDoc * GetEndDocument ( ) override;





	};


