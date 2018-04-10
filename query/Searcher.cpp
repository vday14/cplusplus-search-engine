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
		ISRContainer container = ISRContainer( queryParser.queryTree );
		container.Solve( );




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