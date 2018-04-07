//
// Created by Zane Dunnings on 4/2/18.
//

#include "Ranker.h"
#include "Site.h"
#include "../../constraintSolver/ISRWord.h"
#include "../../constraintSolver/ISREndDoc.h"
#include <vector>
#include <queue>
#include <string>
#include <set>

/***
 * TODO: Finalize how we want this to work
 * Initializes the ranker with the Word ISRs from the query, will most likely scale to add more input,
 * could possibly pull the information, depends on how much control we want
 */
void Ranker::init ( vector<ISRWord> isrListInput )
	{
	ISRList = isrListInput;
	}

/***
 * This will generate a map of the Site objects for each document
 * @return
 */
void Ranker::generateSiteList( )
	{
	//Iterate through IsrWord vector and fill in Site information
	for( auto isrWord = ISRList.begin(); isrWord < ISRList.end(); ++isrWord)
		{
		addWordtoSites( *isrWord );
		}
	}

//Create a new site with atttributes, or add word data to an existing site
void Ranker::addWordtoSites ( ISRWord isrWord )
	{

		string word = isrWord.term;
		auto url = isrWord.DocumentEnd->getCurrentDoc ( ).url;
		if( Websites.find( url ) != Websites.end( ) )
			{
			Websites[ url ]->wordData[ word ] = getData( isrWord );


			}
		else
			{
			Site * newSite = new Site();
			newSite->wordData[ word ] = getData( isrWord );
			newSite->url = url;
			Websites[ url ] = newSite;
			}
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
 * Pushes all of the sites onto the priorityQueue, and scores then before pushing them on
 * which puts them in their ranked order
 */
void Ranker::rank()
	{
	for( auto i = Websites.begin(); i != Websites.end( ); ++i)
		{
		i->second->getScore();
		WebsiteQueue.push( i->second );
		}
	}

void Ranker::printSites()
	{
	for( auto i = Websites.begin(); i != Websites.end(); ++i )
		{
		cout << "URL: " << i->second->url << std::endl;

		for( auto j = Websites[ i->second->url ]->wordData.begin( ); j != Websites[ i->second->url ]->wordData.end( ); ++j)
			{
			cout << j->first << ": " << j->second.frequency << std::endl;
			}
		}
	cout << "\n\n\n";
	}

void Ranker::printRankedSites()
	{
	cout << "----RANKED RESULTS----" << endl;

	int size  = WebsiteQueue.size();
	for( auto i = size; i > 0; --i )
		{
		Site * website = WebsiteQueue.top();
		WebsiteQueue.pop();
		cout << "URL: " << website->url << std::endl;

		for( auto j = Websites[ website->url ]->wordData.begin( ); j != Websites[ website->url ]->wordData.end( ); ++j)
			{
			cout << j->first << ": " << j->second.frequency << std::endl;
			}
		}
	}

//	vector<size_t> locations;
//	set<string> urls;
// urls.insert ( url );

