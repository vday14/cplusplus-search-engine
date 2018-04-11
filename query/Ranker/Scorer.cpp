//
// Created by Zane Dunnings on 4/2/18.
//

#include "Scorer.h"
#include "Site.h"
#include <vector>
#include <cassert>

/***
 * Calculate the score for some site, Normalize the score to 1.0
 * @return
 */
double Scorer::getScore ( Site website)
	{
	assert( SIMPLE_WEIGHT == 1);
	double score = 0.0;
	int numberOfFunctions = 1;

	//Repeat for each function
	score += Simple( website )*SIMPLE_WEIGHT;

	return score / (double)numberOfFunctions;
	}

double Scorer::Simple( Site inputSite)
	{
	double score = 0;
	for( auto i = inputSite.wordData.begin(); i != inputSite.wordData.end(); ++i )
		{
		score+=i->second.frequency;
		}
	return score;
	}