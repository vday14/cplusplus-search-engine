
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
	score += StaticScore( website ) * STATIC_WEIGHT;
//	score += PhraseMatch( website ) * Scorer::PHRASE_WEIGHT;

	return score / (double)numberOfFunctions;
	}

/**
 * Static ranker
 *
 * @param inputSite
 * @return double
 */
double Scorer::StaticScore( Site inputSite )
	{
	double score = 0;
	std::string domain = inputSite.getUrl( ).getDomain( );

	//FIXME shouldn't have to create a new parsed url
	if ( domain == "" )
		{
		domain = ParsedUrl( "http://" + inputSite.getUrl( ).getCompleteUrl( ) ).getDomain();
		}

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
double Scorer::PhraseMatch( Site inputSite )
	{
	double score = 0;
//	auto queryTokens = inputSite.getQuery( ).getQueryTokens( );

	//TODO Logic

	return score;
	}

/**
 * Calculates score for proximity matches
 *
 * @param inputSite
 * @return double
 */
double Scorer::ProximityMatch( Site inputSite )
	{
	double score = 0;
//	auto queryTokens = inputSite.getQuery( ).getQueryTokens( );

	//TODO Logic
	return score;
	}
