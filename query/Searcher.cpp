//
// Created by Jake Close on 3/7/18.
//

#include "Searcher.h"
#include <iostream>

using namespace std;

/*
 * Searchs the index for the query
 *
 *
 */

void Searcher::search ( )
	{

	if (CompleteQuery == "-quit" ||CompleteQuery == "-q" )
		{
		cout << "Thank you for using C++lue search engine" << endl;
		exit( 0 );
		}
	else if ( CompleteQuery == "-help")
		{
		cout << "Manual" << endl;
		return;
		}
	else
		{

		queryParser.parse(CompleteQuery);

		ProducerConsumerQueue< pair< Location, Location> > *MatchQueue = new ProducerConsumerQueue< pair< Location, Location>  >( );
		Ranker * ranker = new Ranker( MatchQueue );
		ISRContainer container = ISRContainer( queryParser.queryTree , MatchQueue );
		ranker->addISR( container.toRanker );
		ranker->StartThread( );
		clock_t start = clock();
		container.Solve( );
		ranker->WaitForFinish( );
		clock_t end = clock();
		double time = (end - start) / (double) CLOCKS_PER_SEC;
		Results = ranker->getResultsForSiteJSON( );
		Results += "\"time\" : \" " + to_string(time)  + " \" ,  \"total_results\": \"" + to_string(ranker->numberOfTotalResults ) + "\" }" ;
		cout <<  Results << endl;
		delete MatchQueue;
		delete ranker;

		}



	return;

	}


/*
 *
 * Prints the top 10 results
 *
 */

void Searcher::printResults ( )
	{
	cout << " Generated XXX results in about XXX seconds " << endl;


	return;
	}


string Searcher::GetResults ( )
	{

	return Results;
	}