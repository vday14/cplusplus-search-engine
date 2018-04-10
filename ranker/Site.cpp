//
// Created by Zane Dunnings on 4/2/18.
//

#include "Site.h"
#include "Scorer.h"
#include <string>
#include <vector>

/***
 * Returns the score of some site. Either grabs the value if its been scored previously, or generates a new score using
 * a scorer object.
 * @return
 */
double Site::getScore ( )
	{
	if( this->hasBeenScored )
		{
		return this->score;
		}

	hasBeenScored = true;
	Scorer rank = Scorer();
	return rank.getScore( *this );
	}