
#include "Scorer.h"
#include "Site.h"
#include <cmath>
#include <vector>
#include "../shared/url.h"
#include "../parser/Parser.h"
#include "../parser/queryTokenizer.h"

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
	std::string domain = getUrlDomain ( inputSite.getUrl( ) );


	if ( Scorer::domainMap.find( domain ) != Scorer::domainMap.end( ) )
		{
		score = Scorer::domainMap[ domain ];
		}
	return score;
	}

std::string Scorer::getUrlDomain( std::string url )
	{
	if ( findStr(".gov", url) != url.size( ) )
		return ".gov";

	if ( findStr(".com", url) != url.size( ) )
		return ".com";

	if ( findStr(".net", url) != url.size( ) )
		return ".net";

	if ( findStr(".org", url) != url.size( ) )
		return ".org";

	if ( findStr(".edu", url) != url.size( ) )
		return ".edu";

	if ( findStr(".us", url) != url.size( ) )
		return ".us";
	return "";
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
	std::vector< std::string > queryTokens = inputSite.getQuery( ).getQueryTokens();

	//if only one word, don't phrase match
	if ( queryTokens.size(  ) <= 1 )
		{
		return score;
		}

	int i = 0;
	int j = 1;
	int numPhrases = 0;
	while ( j < queryTokens.size( ) )
		{
		score = 1;
		numPhrases = phraseMatchHelper( queryTokens[ i ], queryTokens[ j ], &inputSite.wordData );
		while ( j < queryTokens.size( ) &&  numPhrases != 0 )
			{
			++i;
			++j;
			score += numPhrases;
			}
		++i;
		++j;
		}

	// score == number of words in phrase match
	return ( score == 1 ) ? 0 : score;
	}

/**
 * Helper for phrase matching
 * Returns true is the two words are adjacent in Site
 *
 * @param str1
 * @param str2
 * @param wordData
 * @return
 */
int Scorer::phraseMatchHelper ( std::string str1, std::string str2, std::unordered_map< std::string, data > *wordData )
	{
	if ( wordData->find( str1 ) == wordData->end( ) || wordData->find( str2 ) == wordData->end( ) )
		return false;

	int i = 0;
	int j = 0;
	int numPhrases = 0;
	while ( wordData->at( str1 ).offsets[ i ] < wordData->at( str2 ).offsets[ j ] && i < wordData->at( str1 ).offsets.size( ) && j < wordData->at( str2 ).offsets.size( ) )
		{
		if ( wordData->at( str1 ).offsets[ i ] + 1 ==  wordData->at( str2 ).offsets[ j ] )
			{
			++numPhrases;
			}
		++i;
		++j;
		}
	return numPhrases;

	}


/**
 * Calculates score for proximity matches
 *
 * @param inputSite
 * @return double
 */
//FIXME trying her lecture way
double Scorer::proximityMatch ( Site inputSite )
	{
	double score = 0;

	// find the smallest list of words and start there



	return score;
	}
