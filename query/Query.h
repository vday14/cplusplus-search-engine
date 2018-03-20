//
// Created by Jake Close on 3/7/18.
//

#pragma once

using namespace std;

class QueryParser
	{

public:
	QueryParser ( const char *query_in ) : CompleteQuery( query_in )
		{ };

	void search ( );

	void printResults ( );

private:
	const char *CompleteQuery;

	};


