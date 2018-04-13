
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

	std::vector< std::string > queryTokens = inputSite.getQuery( ).getQueryTokens( );

	// find the rarest word in doc
	std::string minWord = getMinFreq( &inputSite.wordData, &queryTokens );

	//start of the rarest word
	unsigned long start = inputSite.wordData[ minWord ].offsets[ 0 ];

	// get offsets for other words to be as close as possible to the rarest word
	// Get Min Delta ( start of relevant word matrix )
	for ( int i = 0; i < queryTokens.size( ); ++i )
		{
			inputSite.wordData[ queryTokens [ i ] ].minDelta = getMinDelta( start, &(inputSite.wordData[ queryTokens [ i ] ].offsets) );
		}

	// get average span delta
	unsigned long spanDelta = 0;

	// for each word in query
	for ( int i = 0; i < queryTokens.size( ); ++i )
		{
		for ( int j = i + 1; j < queryTokens.size( ); ++i )
			{
			spanDelta += inputSite.wordData[ queryTokens [ i ] ].offsets[ inputSite.wordData[ queryTokens [ i ] ].minDelta ];
			//++minDelta
			//Check if reached the end of one column
			}
		}





	return score;
	}

/**
 * Return index of the minum offset
 * @param start
 * @param offsets
 * @return
 */
int Scorer::getMinDelta( unsigned long start, std::vector< size_t >* offsets )
	{
	long minSoFar = std::abs( long( ( *offsets )[ 0 ] - start ) );
	long delta = 0;
	int index = 0;
	for ( int i = 0; i < offsets->size( ); ++i )
		{
		delta = std::abs( long( ( *offsets )[ i ] - start ) );
		if ( delta < minSoFar )
			{
			minSoFar = delta;
			index = i;
			}
		if ( delta >= minSoFar )
			{
			return index;
			}
		}
	return index;
	}


/**
 * Returns the word with the least frequency ( rarest )
 * @param wordData
 * @return
 */
std::string Scorer::getMinFreq( std::unordered_map< std::string, data>* wordData, std::vector< std::string > *queryTokens )
	{
	unordered_map< std::string, unsigned long > freqMap;

	for (int i = 0; i < queryTokens->size( ); ++i )
		{

		freqMap[ ( *queryTokens )[ i ] ] = ( *wordData )[ ( *queryTokens )[ i ] ].frequency;
		}

	std::pair<std::string, unsigned long > min
			= *min_element( freqMap.begin( ), freqMap.end( ), CompFreq( ) );
	return min.first;
	}