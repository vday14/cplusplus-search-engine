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

		//This will toggle decoration off to test things lile '$russia $trump or #hillary'
		//queryParser.toggleDecorator( );
		queryParser.parse(CompleteQuery);
		ISRContainer container = ISRContainer( queryParser.queryTree );
		Results = container.Solve( );





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