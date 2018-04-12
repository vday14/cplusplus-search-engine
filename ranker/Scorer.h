
#ifndef EECS398_SEARCH_SCORER_H
#define EECS398_SEARCH_SCORER_H

#include "Site.h"
#include <unordered_map>
#include <string>

class Scorer
	{
public:
	/**
	 * Scorer cstor
	 */
	Scorer( );

	/***
	 * Calculate the score for some site, Normalize the score to 1.0
	 *
	 * @return
	 */
	double getScore( Site );

	/**
	 * Map of domain TLDs to weights
	 *
	 * https://en.wikipedia.org/wiki/List_of_Internet_top-level_domains
	 */
	std::unordered_map< std::string, double > domainMap =
			{ { ".gov", 0.9 }, { ".com", 0.6 }, { ".net", 0.4 }, { ".org", 1.0 }, { ".edu", 0.9 }, { ".us", 0.1 } };

	std::string getUrlDomain( std::string url );

	/**
	 * Static ranker
	 *
	 * @param inputSite
	 * @return double
	 */
	double staticScore ( Site inputSite );

	/**
	 * Calculates score for exact phrase matches
	 *
	 * @param inputSite
	 * @return double
	 */
	double phraseMatch ( Site inputSite );

	int phraseMatchHelper ( std::string str1, std::string str2, std::unordered_map< std::string, data > *wordData );

	/**
	 * Calculates score for proximity matches
	 *
	 * @param inputSite
	 * @return double
	 */
	double proximityMatch ( Site inputSite );

private:
	const double STATIC_WEIGHT = 1.0;
	const double PHRASE_WEIGHT = 1.0;
	const double PROXIMITY_WEIGHT = 1.0;
	const double TFIDF_WEIGHT = 1.0;

	};
#endif //EECS398_SEARCH_SCORER_H
