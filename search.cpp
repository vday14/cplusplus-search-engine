//
// Created by Jake Close on 3/7/18.
//

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "query/Searcher.h"


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
			Searcher searchEngine( q );
			cout << "Results" << endl;
			searchEngine.search( );
			//query->printResults( );
			cout << "Please enter another search " << endl;
			}


		}


	return 0;

	}