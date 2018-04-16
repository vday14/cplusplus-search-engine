
#include "Scorer.h"
#include "Site.h"
#include <utility>
#include <cmath>
#include <vector>
#include "../shared/url.h"
#include <algorithm>
#include "../constraintSolver/ISRWord.h"
#include "../indexer/Corpus.h"
#include "../query/Query.h"

#include "../parser/queryTokenizer.h"
#include <cassert>
#include <limits>

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
double Scorer::getScore ( Site website )
	{
	double score = 0.0;

	// check to see if decorate query tokens are in wordData map
	if ( website.hasAnchor )
		score += proximityMatch( website, website.getQuery( ).getQueryAnchor( ) ) * PROXIMITY_WEIGHT;

	if ( website.hasUrl )
		score += proximityMatch( website, website.getQuery( ).getQueryUrl( ) ) * PROXIMITY_WEIGHT;

	if ( website.hasTitle )
		score += proximityMatch( website, website.getQuery( ).getQueryTitle( ) ) * PROXIMITY_WEIGHT;

	if ( website.hasBody )
		score += proximityMatch( website, website.getQuery( ).getQueryBody( ) ) * PROXIMITY_WEIGHT;

	score += staticScore( website ) * STATIC_WEIGHT;
    score += executeTfIdf( website ) * TFIDF_WEIGHT;

	score += wordLocationScore ( website ) * LOCATION_WEIGHT;
	score /= ( STATIC_WEIGHT + ( PROXIMITY_WEIGHT * 4 ) + LOCATION_WEIGHT + TFIDF_WEIGHT);

	assert ( score <= 1.0);
	return score;
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

	if ( domainMap.find( domain ) != domainMap.end( ) )
		{
		score = domainMap[ domain ];
		}
	return score;
	}

/**
 * Returns the TLD of the url
 *
 * @param url
 * @return
 */
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
 * Calculates score for proximity matches
 *
 * @param inputSite
 * @param alpha
 * @param alphaPrime
 *
 * @return double
 */
double Scorer::proximityMatch ( Site inputSite, std::vector< std::string > queryTokens )
	{
	double score = 0;

	if ( queryTokens.size( ) <= 1 )
		return score;

	// find the rarest word in doc
	std::string minWord = getMinFreq( &inputSite.wordData, &queryTokens );

	// no match for this doc and query
	if ( minWord == "" )
		return score;

	//start of the rarest word
	unsigned long start = inputSite.wordData[ minWord ].offsets[ 0 ];

	// get offsets for other words to be as close as possible to the rarest word
	// Get Min Delta ( start of relevant word matrix )

	std::pair< unsigned long, int > pair = setMinDelta( &inputSite.wordData, &queryTokens, start );

	unsigned long minLength = std::get< 0 >( pair );
	int minLengthWord = std::get< 1 >( pair );


	ScoreData data( &inputSite.wordData, & queryTokens, minLength, minLengthWord );

	double percentExactPhrases = double( data.numPhrases) / data.numSpans;
	if ( percentExactPhrases > PERFECT_DOC )
		percentExactPhrases = PERFECT_DOC;

	if ( data.avrgSpanDelta != 0 )
		{
		score = ( ALPHA * ( double( queryTokens.size( ) ) / ( data.avrgSpanDelta ) ) );
		}
	else
	{
		score = 0;
	}

//	score = ( ALPHA * ( double( queryTokens.size( ) ) / ( data.avrgSpanDelta ) ) );
	score += ALPHA_PRIME * ( percentExactPhrases );

	double maxScore = ALPHA * ( double( queryTokens.size( ) ) / double( queryTokens.size( ) - 1 ) );
	maxScore += ALPHA_PRIME * PERFECT_DOC;

	return ( score / maxScore );
	}

/**
 * Return index of the minimum offset
 *
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
 * Updates the min deltas for the query tokens for Site's wordData
 *
 * @param wordData
 * @param queryTokens
 * @param start
 * @return
 */
std::pair< unsigned long, int > Scorer::setMinDelta( std::unordered_map< std::string, data>* wordData, std::vector< std::string > *queryTokens, unsigned long start )
	{
	//minLength starts out as inf
	unsigned long minLength = 0;
	int minLengthWord = 0;
	bool first = true;

	for ( int i = 0; i < queryTokens->size( ); ++i )
		{
		std::string word = ( *queryTokens )[ i ];
		// make sure word is in wordData
		if ( wordData->find( word ) != wordData->end( ) )
			{
			(*wordData)[ word ].minDelta = getMinDelta ( start, &(*wordData)[ word ].offsets );

			// first time thru loop
			if ( first )
				{
				minLength = (*wordData)[ word ].offsets.size ( );
				minLengthWord = i;
				first = false;
				}

			if ( (*wordData)[ word ].offsets.size ( ) < minLength )
				{
				minLength = (*wordData)[ word ].offsets.size ( );
				minLengthWord = i;
				}
			}
		}

	std::pair< unsigned long, int > pair( minLength, minLengthWord );
	return pair;
	}

/**
 * Returns the word with the least frequency ( rarest )
 *
 * @param wordData
 * @return
 */
std::string Scorer::getMinFreq( std::unordered_map< std::string, data>* wordData, std::vector< std::string > *queryTokens )
{
    unordered_map< std::string, unsigned long > freqMap;

    for (int i = 0; i < queryTokens->size( ); ++i )
    {

        if ( wordData->find( ( *queryTokens )[ i ] ) != wordData->end( ) )
            freqMap[ ( *queryTokens )[ i ] ] = ( *wordData )[ ( *queryTokens )[ i ] ].frequency;
    }

    if ( freqMap.empty( ) )
        return "";

    std::pair<std::string, unsigned long > min
            = *min_element( freqMap.begin( ), freqMap.end( ), CompFreq( ) );

    return min.first;
}



/***
 * returns the score for where the word was: title, url, body
 * @param inputSite
 * @return
 */
double Scorer::wordLocationScore ( Site inputSite )
	{
	double score = 0.0;
	const double AVG_TITLE_SIZE = 12.0;
	const double URL_WEIGHT = 4.0 ;
	const double TITLE_WEIGHT = 2.0 ;
	const double BODY_WEIGHT = 1.0;

	int numberOfUniqueWords = 0;
	int totalNumOfWords = 0;

	for ( auto word:inputSite.wordData )
		{
		wordLocType type = matchType ( word.first );
		double word_score = 0.0;
		switch ( type )
			{

			case URLType:
				 word_score = URL_WEIGHT * AVG_TITLE_SIZE * (word.second.frequency / (double)getNumWordsInURL ( inputSite.getUrl() ) );
				//This is to apply a max score to anything with a very positive match. Essentiall if 50% of the words in the title
				// match, then just give the max score
				if ( word_score > 4.0 )
					word_score  = 4.0;

				score+= word_score;
				++numberOfUniqueWords;
				break;
			case titleType:
				//TODO: replace with actual title size
				 word_score = TITLE_WEIGHT * AVG_TITLE_SIZE * (word.second.frequency / (double)getNumWordsInTitle( inputSite.getTitle( )) );
				if ( word_score > 2.0 )
					word_score  = 2.0;
				++numberOfUniqueWords;
				score+= word_score;
				break;
			default:
				break;
			}
		}
	//Normalize scores to 1
	if( numberOfUniqueWords == 0)
		{
		return 0;
		}
	return score / ( URL_WEIGHT * numberOfUniqueWords);
	}

/***
 * returns the type of word given
 * @param input
 * @return
 */
Scorer::wordLocType Scorer::matchType( string input )
	{

	assert( input != "" );
	char decoration = input[ 0 ];

	if(decoration == '#')
		{
			return titleType;
		}
	else if(decoration == '$')
		{
		return URLType;
		}
	else if( decoration == '%')
		{
		return bodyType;
		}
	else{
		return bodyType;
		}
	}

/**
* Get total corpus doc count
* @return
*/
size_t Scorer::getDocCount( Corpus corpus )
    {
	return corpus.numberDocuments;
    }

/**
* Calculates tifidf weight vector for query and input site (doc)
* @param inputSite
* @return
*/
std::unordered_map< std::string, TfIdf > Scorer::calcTfIdf( Site inputSite )
    {
	Corpus corpus = Corpus::getInstance( );
    unsigned totalNumDocs = getDocCount(  corpus );
    Query query = inputSite.getQuery( );
    string queryString = query.getQueryString( );
	QueryTokenizer parsedQuery( queryString );
    const unordered_map< string, vector< unsigned long > > *queryTokens = parsedQuery.executeQueryOffsets( );

    //calculate weight vector for this specific site/document
    unordered_map< string, TfIdf > docWeights;
    auto begin = inputSite.wordData.begin( );
    auto end = inputSite.wordData.end( );
    while ( begin != end )
        {
        string currTerm = begin->first;
        string term = removeDecorator( currTerm );
        if ( queryTokens->find( term ) != queryTokens->end( ) )
            {
            if ( docWeights.find( term ) != docWeights.end( ) )
                {
                docWeights[ currTerm ].tf += begin->second.frequency;
                docWeights[ currTerm ].totalDocFreq += corpus.getWordInfo( begin->first ).docFrequency;
                }
            else
                {
                TfIdf ti;
                ti.tf = begin->second.frequency;
                ti.totalDocFreq = corpus.getWordInfo( begin->first ).docFrequency;
                docWeights[ currTerm ] = ti;
                }
            }
            ++begin;
        }
    auto beginDocWeights = docWeights.begin( );
    auto endDocWeights = docWeights.end( );
    while ( beginDocWeights != endDocWeights )
        {
        unsigned long tf = beginDocWeights->second.tf;
        double totalDocFrequency = beginDocWeights->second.totalDocFreq;
        beginDocWeights->second.tfIdf = tf + log(totalNumDocs / totalDocFrequency);

        if (queryTokens->find(beginDocWeights->first) != queryTokens->end())
            {
            queryWeights[beginDocWeights->first] = beginDocWeights->second.tfIdf;
            }
        ++beginDocWeights;
        }
    return docWeights;
    }
/**
* Calculate total difference between doc weights and query weights
* @param docWeights
* @return
*/
double Scorer::compareTfIdf( unordered_map< string, TfIdf > *docWeights )
    {
    auto begin_weights = docWeights->begin( );
    auto end_weights = docWeights->end( );
    double difference = 0;
    while ( begin_weights != end_weights )
        {
        double docWeight = begin_weights->second.tfIdf;
        double queryWeight = queryWeights.find( begin_weights->first )->second;
        difference += abs( docWeight - queryWeight );
        }
    difference = 1 / difference;
    return difference;
    }

/**
* Executes tfidf weight calculation and returns rough similarity score
* @param inputSite
* @return
*/
double Scorer::executeTfIdf( Site inputSite )
    {
    unordered_map< string, TfIdf > docWeights = calcTfIdf( inputSite );
    double tfIdfScore = compareTfIdf( &docWeights );
    return tfIdfScore;
    }

int Scorer::getNumWordsInURL ( string url )
	{
	set< char > split = { '.', ':', '/', '\\', '_', '?', '-', '~', '#', '[', ']', '@', '!', '$', '&', '\'',
	                      '(', ')', '*', '+', ',', ';', '=' };

	return splitStr ( url, split, true).size( );
	}

int Scorer::getNumWordsInTitle ( string title )
	{

	return splitStr ( title, ' ', true).size( );
	}
