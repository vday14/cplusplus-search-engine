
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
	score += Static( website ) * Scorer::STATIC_WEIGHT;
	score += PhraseMatch( website ) * Scorer::PHRASE_WEIGHT;

	return score / (double)numberOfFunctions;
	}

/**
 * Static ranker
 *
 * @param inputSite
 * @return
 */
double Scorer::Static( Site inputSite )
	{
	double score = 0;
	std::string inputUrl = inputSite.getUrl( );
	if ( findStr( "http://", inputUrl ) == inputUrl.size( ) )
		{
		inputUrl = "http://" + inputUrl;
		}
	ParsedUrl url(  inputUrl );
	std::string domain = url.getDomain( );

	if ( Scorer::domainMap.find( domain ) != Scorer::domainMap.end( ) )
		{
		score = Scorer::domainMap[ domain ];
		}
	return score;
	}

/**
 * Calculates score for phrase matching
 *
 * @param inputSite
 * @return
 */
double Scorer::PhraseMatch( Site inputSite )
	{
	QueryParser parser( inputSite.getQuery( ) );
	auto dictionary = parser.execute( );


	delete dictionary;
	dictionary = nullptr;
	return 0;
	}


