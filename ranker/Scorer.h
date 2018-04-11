
#ifndef EECS398_SEARCH_SCORER_H
#define EECS398_SEARCH_SCORER_H

#include "Site.h"
#include <unordered_map>
#include <string>

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
	double Static( Site inputSite );
	double PhraseMatch( Site inputeSite );
	// https://en.wikipedia.org/wiki/List_of_Internet_top-level_domains
	std::unordered_map< std::string, double > domainMap =
			{ { ".gov", 0.9 }, { ".com", 0.6 }, { ".net", 0.4 }, { ".org", 1.0 }, { ".edu", 0.9 }, { ".us", 0.1 } };

	const double STATIC_WEIGHT = 1.0;
	};
#endif //EECS398_SEARCH_SCORER_H
