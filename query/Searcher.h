//
// Created by Jake Close on 3/7/18.
//


#pragma once
#include "../query/queryLanguage/QueryParser.h"
#include "../constraintSolver/ISRContainer.h"
#include "../ranker/Ranker.h"
#include "../shared/ProducerConsumerQueue.h"
#include "../util/stringProcessing.h"
using namespace std;

class Searcher
	{

public:
	Searcher ( string query_in ) : CompleteQuery( query_in )
		{

		CompleteQuery = toLower(CompleteQuery);


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


