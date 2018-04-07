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
void Ranker::init ( vector<ISRWord> query )
	{
	inputQuery = query;
	}

/***
 * This will perform the "sorting" and return a list of ranked URLS
 * @return
 */
vector< string > Ranker::rank ( )
	{
	ISREndDoc endDocs;
	vector<size_t> locations;
	vector<DocumentEnding> docEnds;
	set<string> urls;

	for( auto queryWord = inputQuery.begin(); queryWord < inputQuery.end(); ++queryWord)
		{
		while ( queryWord->getCurrentLocation ( ) != MAX_Location )
			{
			auto url = queryWord->DocumentEnd->getCurrentDoc ( ).url;
			urls.insert ( url );
			queryWord->NextDocument ( );

			}
		}
	}