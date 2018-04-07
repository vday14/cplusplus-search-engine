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

private:
	string CompleteQuery;
	QueryParser queryParser;
	//ISRContainer container;


	};


