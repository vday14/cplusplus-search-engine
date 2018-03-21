//
// Created by Jake Close on 3/7/18.
//

#include "Query.h"
#include <iostream>

using namespace std;

/*
 * Searchs the index for the query
 *
 *
 */

void QueryParser::search ( )
	{

	if ( strcmp( CompleteQuery, "-quit" ) == 0 )
		{
		cout << "Thank you for using C++lue search engine" << endl;
		exit( 0 );
		}
	else if ( strcmp( CompleteQuery, "-help" ) == 0 )
		{
		cout << "Manual" << endl;
		return;
		}


	return;

	}


/*
 *
 * Prints the top 10 results
 *
 */

void QueryParser::printResults ( )
	{
	cout << " Generated XXX results in about XXX seconds " << endl;


	return;
	}