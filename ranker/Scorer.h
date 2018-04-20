#ifndef EECS398_SEARCH_SCORER_H
#define EECS398_SEARCH_SCORER_H

#include "Site.h"
#include <unordered_map>
#include <string>
#include <vector>

/**
 * Custom Comparator to find the minimum frequency
 */
typedef std::pair<std::string, unsigned long > MyPairType;
struct CompFreq
	{
	bool operator()(const MyPairType& left, const MyPairType& right) const
		{
		return left.second < right.second;
		}
	};

/**
 * Gets the data need to compute the score
 *
 * @param wordData
 * @param queryTokens
 * @param minLength
 * @param minLengthWord
 * @return
 */
struct ScoreData
	{
	unsigned long avrgSpanDelta;
	int numSpans;
	int numPhrases;

	/**
	 * Constructor to set the relevant data for the prox match score
	 *
	 * @param wordData
	 * @param queryTokens
	 * @param minLength
	 * @param minLengthWord
	 */
	ScoreData( std::unordered_map< std::string, data>* wordData, std::vector< std::string > *queryTokens, unsigned long minLength, int minLengthWord )
		{
		// get average span delta
		unsigned long avrgSpanDelta = 0;
		unsigned long spanDelta = 0;
		int numPhrases = 0;
		int numSpans = 0;

		int row = 0;
		//while the min delta for each word column has not reached the end of the row
		while ( ( *wordData )[ ( *queryTokens )[ minLengthWord ] ].minDelta + row  < minLength )
			{
			spanDelta = 0;
			//find the delta between each word in the query and the next
			for ( int col = 0; col < queryTokens->size( ) - 1; ++col )
				{
				if ( wordData->find( ( *queryTokens )[ col ] ) != wordData->end( ) && wordData->find( ( *queryTokens )[ col + 1 ] ) != wordData->end( ) )
					{
					int indexA = (*wordData)[ (*queryTokens)[ col ] ].minDelta + row;
					int indexB = (*wordData)[ (*queryTokens)[ col + 1 ] ].minDelta + row;
					long delta = std::abs ( long ((*wordData)[ (*queryTokens)[ col ] ].offsets[ indexA ] -
					                              (*wordData)[ (*queryTokens)[ col + 1 ] ].offsets[ indexB ] ));
					spanDelta += delta;
					avrgSpanDelta += delta;
					}
				}
			++numSpans;
			++row;

			// check if exact phrase match
			if ( spanDelta == queryTokens->size( ) - 1 )
				++numPhrases;

			}
		avrgSpanDelta /= numSpans;

		this->avrgSpanDelta = avrgSpanDelta;
		this->numSpans = numSpans;
		this->numPhrases = numPhrases;

		}

	};

class Scorer
	{
public:

	/**
	 * Map of domain TLDs to weights
	 *
	 * https://en.wikipedia.org/wiki/List_of_Internet_top-level_domains
	 */
	std::unordered_map< std::string, double > domainMap =
			{ { ".gov", 0.9 }, { ".com", 0.6 }, { ".net", 0.4 }, { ".org", 1.0 }, { ".edu", 0.9 }, { ".us", 0.1 } };

/***
	 * 	defines the source of individual words
	 */
	enum wordLocType{
		titleType,
		bodyType,
		anchorType,
		URLType
		};

	/**
	 * Scorer cstor
	 */
	Scorer( );

	/**
	 * Scorer cstor that sets function weights
	 */
	Scorer(double stat, double prox, double loc );

	/***
	 * Calculate the score for some site, Normalize the score to 1.0
	 *
	 * @return
	 */
	double getScore( Site );

	/**
	 * Static ranker
	 *
	 * @param inputSite
	 * @return double
	 */
	double staticScore ( Site inputSite );

	/**
	 * Calculates the score for whether the text was in the title, body, or url
	 *
	 * @param inputSite
	 * @return double
	 */
	double wordLocationScore ( Site inputSite );

	/***
	 * Returns the type of word you pass in, whether it was in the title, url, or body etc
	 * @param input
	 * @return
	 */
	wordLocType matchType( string input );

	/**
	 * Get TLD for url
	 *
	 * @param url
	 * @return
	 */
	std::string getUrlDomain( std::string url );

	/**
	 * Calculates score for proximity matches
	 *
	 * @param inputSite
	 * @param queryTokens
	 * @return double
	 */
	double proximityMatch ( Site inputSite, std::vector< std::string > queryTokens );
	
	/**
     * Calculates tf idf score
     * @param inputSite
     * @param queryTokens
     * @return
     */
	//double tfIdfScore( Site inputSite, std::vector< std::string > queryTokens );

	/**
	 * Return index of the minimum offset
	 *
	 * @param start
	 * @param offsets
	 * @return
	 */
	int getMinDelta( unsigned long start, std::vector< size_t >* offsets );

	/**
	 * Updates the min deltas for the query tokens for Site's wordData
	 *
	 * @param wordData
	 * @param queryTokens
	 * @param start
	 * @return
	 */
	std::pair< unsigned long, int > setMinDelta( std::unordered_map< std::string, data>* wordData, std::vector< std::string > *queryTokens, unsigned long start );

	/**
	 * returns the word with the min frequency
	 * @return
	 */
	std::string getMinFreq( std::unordered_map< std::string, data>* wordData, std::vector< std::string > *queryTokens );

	/***
	 * returns the number of words in a given URL
	 */
	int getNumWordsInURL ( string url );

	/**
	 * returns the number of words in a given title
	 * @param title
	 * @return
	 */
	int getNumWordsInTitle ( string title );

private:
	/**
	 * Weights that each correspond to some function
	 */
	const double STATIC_WEIGHT = 1.0;
	const double PROXIMITY_WEIGHT = 1.0;
	const double LOCATION_WEIGHT = 1.0;
	const double TFIDF_WEIGHT = 1.0;
	const double ALPHA = 3;
	const double ALPHA_PRIME = 10;
	// average percentage of exact phrases in a document
	// calculated in goldStandardDoc.py
	const double PERFECT_DOC = 0.000606342178009;

	};
#endif //EECS398_SEARCH_SCORER_H
