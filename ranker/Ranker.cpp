
#include "Ranker.h"
#include "Site.h"
#include "../constraintSolver/ISRWord.h"
#include "../constraintSolver/ISREndDoc.h"
#include "../shared/url.h"
#include <vector>
#include <queue>
#include <string>
#include <set>


Ranker::Ranker( )
	{ }
/**
 * Ranker cstor
 *
 * @param query_in
 */
Ranker::Ranker( std::string query_in ) : query ( Query( query_in ) )
	{
	sortedDocs.resize(DOCS_TO_RETURN);
	};


void Ranker::addQuery( std::string query_in )
	{
	this->query = Query( query_in );
	}
/***
 * Adds a new site for the doc given as isrListInput
 *
 * @param isrListInput
 */
void Ranker::addDoc( Location BoFDoc,  Location EndOfDocument )
	{

	//cout << "B of location :: " << endl;
	assert( isrListInput.size( ) != 0 );

	Query query( this->getQuery() );
	Site *newSite = nullptr;
	string url;
	string title;

	for ( auto isrWord: isrListInput )
		{

		isrWord->Seek( BoFDoc);

		if( isrWord->currentLocation  < EndOfDocument && isrWord->currentLocation > BoFDoc)
			{
			if ( url == "" )
				{
				url = isrWord->GetEndDocument( )->getCurrentDoc( ).url;
				title = isrWord->GetEndDocument()->getCurrentDoc().title;
				newSite = new Site( url, query , title );
				}
			string word = isrWord->term;
			url = isrWord->GetEndDocument( )->getCurrentDoc( ).url;
			//cout << "Ranker adding url :: " << url << endl;
			//cout << "Current location " << isrWord->currentLocation << endl;

			newSite->wordData[ word ] = getData( *isrWord );

			}
		}
	if(newSite != nullptr )
		selectivelyAddDocs( newSite );

	//assert(newSite != nullptr);


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
		cout << "URL: " << website->getUrl( ) << std::endl;
		cout << "Title: " << website->getTitle( ) << std::endl;
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
	ISREndDoc endDocs;
	std::vector < size_t > offsets;
	vector<DocumentEnding> docEnds;

	unsigned long freq = 0;
	while ( isrWord.getCurrentLocation ( ) < isrWord.DocumentEnd->getCurrentDoc( ).docEndPosition )
		{
		offsets.push_back( isrWord.getCurrentLocation( ) );
		isrWord.Next();
		++freq;
		}
	wordData.frequency = freq;
	wordData.offsets = offsets;
	return wordData;
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

string Ranker::getResultsForSiteJSON( )
	{
	orderResults( );
	string results = " { \"results\" : [ ";



	for( int i = 0; i < sortedDocs.size( ) ; ++i )
		{
		Site * site = sortedDocs[ i ];
		results += "{ \"site\": \"" + site->getUrl( )
					  + "\", \"score\": \"" + to_string( site->getScore( ) ) + "\" , \"title\" : \" "+ site->getTitle() + "\" }";
		if(i != (sortedDocs.size( ) - 1) )
			results += ",";

		}
	results += " ]  , ";
	return results;
	}


void Ranker::orderResults()
	{
	deque < Site * > stack;
	while ( !runningRankedQueue.empty( ))
		{
		stack.push_back( runningRankedQueue.top( ));
		runningRankedQueue.pop( );
		}

	while ( !stack.empty( ))
		{
		sortedDocs.push_back( stack.back( ));
		stack.pop_back( );
		}
	}

void Ranker::addISR( vector<ISRWord*> isr_in )
	{
	isrListInput = isr_in;

	}

//	vector<size_t> locations;
//	set<string> urls;
// urls.insert ( url );


//	vector<size_t> locations;
//	set<string> urls;
// urls.insert ( url );

