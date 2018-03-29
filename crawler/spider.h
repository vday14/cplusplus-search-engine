#pragma once


#include<string>
#include <pthread.h>
#include <fstream>
#include "../shared/ProducerConsumerQueue.h"
#include "../shared/ThreadClass.h"
#include <iostream>
#include <unordered_map>
#include "Readers/StreamReader.h"
#include "../util/util.h"
#include "../parser/Parser.h"

using namespace std;

using DocIndex = const unordered_map< string, vector< unsigned long > >;

class Spider : public ThreadClass
	{

public:

	Spider ( string mode_in,
				UrlFrontier  *url_q_in,
	         ProducerConsumerQueue< DocIndex * > *doc_index_queue_in
	)
			: mode( mode_in ),
			  urlFrontier( url_q_in ),
			  parser( url_q_in ),
			  IndexerQueue( doc_index_queue_in )
		{

		};


	//Takes a url off of the url frontier
	ParsedUrl * getUrl ( );

	virtual void run ( );

	bool writeDocToDisk ( ParsedUrl url );

	bool shouldURLbeCrawled ( size_t docId );

	size_t hash ( const char *s );


	void kill ( );

	//int getRobots(ParsedUrl url );
	bool checkRobots ( ParsedUrl url );

private:

	int locationOnDisk;
	UrlFrontier *urlFrontier;
	ProducerConsumerQueue< DocIndex * > *IndexerQueue;
	string mode;
	Parser parser;
	bool alive = true;

	};