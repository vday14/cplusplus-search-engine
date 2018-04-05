//
// Created by Zane Dunnings on 4/2/18.
//

#include "Scorer.h"

/***
 * Calculate the score for some site, Normalize the score to 1.0
 * @return
 */
double Scorer::getScore ( Site )
	{
	double score = 0.0;
	int numberOfFunctions = 1;

	//Repeat for each function
	score += Simple( Site )*SIMPLE_WEIGHT;

	return score / (double)numberOfFunctions;
	}

double Simple( Site )
	{
	return 42.0;
	}