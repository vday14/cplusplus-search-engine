#include "Ranker.h"
#include "Site.h"
#include "../constraintSolver/ISRWord.h"
#include "../constraintSolver/ISREndDoc.h"
#include <vector>
#include <queue>
#include <string>
#include <set>

/***
 * Adds a new site for the doc given as isrListInput
 * @param isrListInput
 */
void Ranker::addDoc( vector<ISRWord> isrListInput )
	{
	Site * newSite = new Site();
	string url;

	if( isrListInput.size( ) != 0 )
		url = isrListInput[0].DocumentEnd->getCurrentDoc ( ).url;

	newSite->url = url;
	//Websites[ url ] = newSite;
	for( auto isrWord: isrListInput)
		{
		string word = isrWord.term;
		newSite->wordData[ word ] = getData( isrWord );
		}

	selectivelyAddDocs( newSite );

	}

data Ranker::getData( ISRWord isrWord)
	{
	ISREndDoc endDocs;
	vector<DocumentEnding> docEnds;


	unsigned long freq = 0;

	//FixME just gets the word frequency, add more useful functions as we add heuristics

	while ( isrWord.getCurrentLocation ( ) < isrWord.DocumentEnd->getCurrentDoc().docEndPosition)
		{
		isrWord.Next();
		++freq;
		}

	data wordData;
	wordData.frequency = freq;

	return wordData;
	}

Ranker::~Ranker()
	{
	for( auto i = Websites.begin( ); i != Websites.end( ); ++i )
		{
		delete i->second;
		}
	}
/***
 * Scores the document and only adds it to the returned list if it's score is greater than the smallest score
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


void Ranker::printRankedSites()
	{
	cout << "----RANKED RESULTS----" << endl;
	unsigned long size  = runningRankedQueue.size();
	for( auto i = size; i > 0; --i )
		{
		Site * website = runningRankedQueue.top();
		runningRankedQueue.pop();
		cout << "URL: " << website->url << std::endl;

		for( auto j = website->wordData.begin( ); j != website->wordData.end( ); ++j)
			{
			cout << j->first << ": " << j->second.frequency << std::endl;
			}
		}
	}

//	vector<size_t> locations;
//	set<string> urls;
// urls.insert ( url );

