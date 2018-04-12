//
// Created by Zane Dunnings on 4/2/18.
//

#include "Site.h"
#include "Scorer.h"
#include <string>
#include <vector>
#include <iostream>

/***
 * Returns the score of some site. Either grabs the value if its been scored previously, or generates a new score using
 * a scorer object.
 * @return
 */
double Site::getScore ( )
	{
	clock_t start  = clock ( );
	if( this->hasBeenScored )
		{
	return this->score;
		}

	hasBeenScored = true;
	Scorer rank = Scorer();
	score = rank.getScore (*this);
	clock_t end  = clock ( );
	double time = (end - start) / (double) CLOCKS_PER_SEC;
	//std::cout << "GET SCORE FN TIME " << time << std::endl;

	return score;
	}