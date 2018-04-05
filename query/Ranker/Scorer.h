//
// Created by Zane Dunnings on 4/2/18.
//

#ifndef EECS398_SEARCH_SCORER_H
#define EECS398_SEARCH_SCORER_H

class Scorer
	{
public:
	Scorer()
		{
		}

	double getScore( Site );

private:

	//Simple example heuristic
	double Simple( Site );
	const double SIMPLE_WEIGHT = 1.0;
	};
#endif //EECS398_SEARCH_SCORER_H
