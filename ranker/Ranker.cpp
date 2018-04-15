#include "Ranker.h"
#include "Site.h"
#include "../constraintSolver/ISRWord.h"
#include "../constraintSolver/ISREndDoc.h"
#include "../shared/url.h"
#include <vector>
#include <queue>
#include <string>
#include <set>

/**
 * Ranker cstor
 *
 * @param query_in
 */
Ranker::Ranker( std::string query_in ) : query ( Query( query_in ) )
	{
	sortedDocs.resize(DOCS_TO_RETURN);
	};


/**
 * Adds a new site for the doc given as isrListInput
 *
 * @param isrListInput
 */
void Ranker::addDoc( vector<ISRWord> isrListInput )
	{
	assert( isrListInput.size( ) != 0 );
	std::string urlStr = isrListInput[ 0 ].DocumentEnd->getCurrentDoc ( ).url;

	if ( findStr("http://", urlStr) == urlStr.size( ) )
		urlStr = "http://" + urlStr;

	ParsedUrl url( urlStr );

	Query query( this->getQuery() );
	Site * newSite = new Site( url, query );

	//Websites[ url ] = newSite;
	for( auto isrWord: isrListInput)
		{
        //add .getDocFrequency
		string word = isrWord.term;
		newSite->wordData[ word ] = getData( isrWord );
		}

	selectivelyAddDocs( newSite );
	}

/**
 * Outputs the ranked sites to stout
 *
 */
void Ranker::printRankedSites()
	{
	cout << "----RANKED RESULTS----" << endl;
	unsigned long size  = runningRankedQueue.size();
	for( auto i = size; i > 0; --i )
		{
		Site * website = runningRankedQueue.top();
		runningRankedQueue.pop();
		cout << "URL: " << website->getUrl( ).getCompleteUrl() << std::endl;

		cout << "score: " << website->getScore( ) << std::endl;
		}
	}

/**
 * Returns the query
 *
 * @return Query
 */
Query Ranker::getQuery( )
	{
	return this->query;
	}

/**
 * Sets the data for each word
 *
 * @param isrWord
 * @return data
 */
data Ranker::getData( ISRWord isrWord )
	{

	data wordData;
    wordData.docFrequency = isrWord.getDocFrequency();
	wordData.frequency = getFrequency( &isrWord );
	wordData.offsets = getOffsets( &isrWord );


	return wordData;
	}

/**
 * Gets the frequency of a certain word
 *
 * @param isrWord
 * @return
 */
unsigned long Ranker::getFrequency ( ISRWord* isrWord )
	{
	ISREndDoc endDocs;
	vector<DocumentEnding> docEnds;

	unsigned long freq = 0;
	while ( isrWord->getCurrentLocation ( ) < isrWord->DocumentEnd->getCurrentDoc( ).docEndPosition )
		{
		isrWord->Next();
		++freq;
		}
	return freq;
	}

/**
 * Returns the offsets of the word
 *
 * @return
 */
std::vector < size_t > Ranker::getOffsets( ISRWord* isrWord )
	{
	std::vector < size_t > offsets;
	while ( isrWord->getCurrentLocation ( ) < isrWord->DocumentEnd->getCurrentDoc( ).docEndPosition )
		{
		offsets.push_back( isrWord->getCurrentLocation( ) );
		isrWord->Next();
		}
	return offsets;
	}


/**
 * Scores the document and only adds it to the returned list if it's score is greater than the smallest score
 *
 * @param doc
 */
void Ranker::selectivelyAddDocs( Site * doc)
	{
	double score;
	score = doc->getScore( );

	if( runningRankedQueue.size() < DOCS_TO_RETURN )
		{
		runningRankedQueue.push(doc);
		return;
		}
	else if( score <= runningRankedQueue.top( )->getScore ())
		{
		delete doc;
		}
	else
		{
		runningRankedQueue.pop();
		runningRankedQueue.push(doc);
		}

	}
/**
 * Ranker dstor
 */
Ranker::~Ranker()
	{
	for( auto i = Websites.begin( ); i != Websites.end( ); ++i )
		{
		delete i->second;
		}
	}


//	vector<size_t> locations;
//	set<string> urls;
// urls.insert ( url );

