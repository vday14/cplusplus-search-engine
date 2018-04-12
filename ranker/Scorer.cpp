
#include "Scorer.h"
#include "Site.h"
#include <vector>
#include "../shared/url.h"
#include "../parser/Parser.h"
#include "../parser/queryParser.h"

/**
 * Scorer cstor
 */
Scorer::Scorer ( )
	{ }

/**
 * Calculate the score for some site, Normalize the score to 1.0
 *
 * @return
 */
double Scorer::getScore ( Site website)
	{
	double score = 0.0;
	int numberOfFunctions = 1;

	//Repeat for each function
	score += staticScore( website ) * STATIC_WEIGHT;
	score += phraseMatch( website ) * PHRASE_WEIGHT;
	score += proximityMatch( website ) * PROXIMITY_WEIGHT;

	return score / (double)numberOfFunctions;
	}

/**
 * Static ranker
 *
 * @param inputSite
 * @return double
 */
double Scorer::staticScore ( Site inputSite )
	{
	double score = 0;
	std::string domain = inputSite.getUrl( ).getDomain( );
	if ( Scorer::domainMap.find( domain ) != Scorer::domainMap.end( ) )
		{
		score = Scorer::domainMap[ domain ];
		}
	return score;
	}

/**
 * Calculates score for exact phrase matches
 *
 * @param inputSite
 * @return double
 */
double Scorer::phraseMatch ( Site inputSite )
	{
	double score = 0;
	vector< std::string > queryTokens = inputSite.getQuery( ).getQueryTokens();

	for ( int i = 0; i < queryTokens.size( ); ++i )
		{
		// check if query token is in doc
		if ( inputSite.wordData.find( queryTokens[ i ] != inputSite.wordData.end( ) ) )
			{
			wordOffsets = inputSite.wordData.at( queryTokens[ i ] ).offsets;
			}
		}

	return score;
	}

/**
 * Calculates score for proximity matches
 *
 * @param inputSite
 * @return double
 */
double Scorer::proximityMatch ( Site inputSite )
	{
	double score = 0;
//	auto queryTokens = inputSite.getQuery( ).getQueryTokens( );

	//TODO Logic
	return score;
	}
