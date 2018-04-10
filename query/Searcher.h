//
// Created by Jake Close on 3/7/18.
//

#include "../query/queryLanguage/QueryParser.h"
#include "../constraintSolver/ISRContainer.h"
#pragma once

using namespace std;

class Searcher
	{

public:
	Searcher ( string query_in ) : CompleteQuery( query_in )
		{



		};

	void search ( );

	void printResults ( );

	string GetResults( );

private:
	string CompleteQuery;
	QueryParser queryParser;
	string Results;
	//ISRContainer container;


	};


