//
// Created by Jake Close on 3/7/18.
//

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "query/Query.h"


using namespace std;


int main( int argc, char *argv[] )
	{


	cout << " --- WELCOME EECS 398 SEARCH ENGINE --- " << endl;
	cout << endl;
	cout << "What would you like to know?  " << endl;
	cout << endl;
	cout << "type -q to exit or -help for more information" << endl;
	string q;



	while(true)
		{

		while ( getline( cin, q ) && !q.empty( ))
			{
			QueryParser *query = new QueryParser( q.c_str( ));
			query->search( );
			query->printResults( );
			}

		}


	return 0;

	}