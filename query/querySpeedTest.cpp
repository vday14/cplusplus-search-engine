//
// Created by Jake Close on 4/15/18.
//

#include <iostream>
#include "Searcher.h"

using namespace std;


int main( int argc, char *argv[] )
	{


	vector<string> queries;
	queries.push_back("trump");
	queries.push_back("boston");
	queries.push_back("red");
	queries.push_back("russia");
	queries.push_back("china");
	queries.push_back("espn");
	queries.push_back("sports");
	queries.push_back("movies");
	queries.push_back("electric");
	queries.push_back("tesla");
	queries.push_back("washington");
	queries.push_back("nytimes");
	queries.push_back("boston");
	queries.push_back("white");






	string fileName = util::GetCurrentWorkingDir( ) + "/query/queryResults.txt";

	if ( remove( fileName.c_str( )) != 0 )
		perror( "Error deleting file" );
	else
		puts( "File successfully deleted" );
	int file = open( fileName.c_str( ), O_CREAT | O_WRONLY, S_IRWXU );

	string open = "{\"data\" : [";
	string closed = "] }";
	write( file, open.c_str( ), strlen( open.c_str( )  ));

	for(int i = 0 ; i < queries.size( ) ; ++i )
			{
			auto q = queries[ i ];
			cout << q << endl;
			Searcher searchEngine( q );
			cout << "Results" << endl;
			searchEngine.search( );
			string results;
			if( i == queries.size ( ) - 1  )
				results = searchEngine.GetResults( );
			else
				results  = searchEngine.GetResults( ) + ",";

			write( file, results.c_str( ), strlen( results.c_str( )  ));

			cout << "Please enter another search " << endl;
			}

	write( file, closed.c_str( ), strlen( closed.c_str( )  ));
	return 0;





	}