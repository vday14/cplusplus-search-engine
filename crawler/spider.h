#pragma once


#include<string>
#include <pthread.h>
#include <fstream>
#include "../shared/ProducerConsumerQueue.h"
#include "../shared/ThreadClass.h"
#include<iostream>
#include <unordered_map>
#include "StreamReader.h"

using namespace std;


class Spider : public ThreadClass
	{

public:

	Spider( string mode_in, ProducerConsumerQueue < string > *url_q_in , unordered_map<string, int> *doc_map_lookup_in)
			: mode( mode_in ), urlFrontier( url_q_in ) , docMapLookup(doc_map_lookup_in)
		{ };


	//Takes a url off of the url frontier
	string getUrl();

	virtual void FuncToRun();

	//Makes request to given url
	// if successful, writes file to disk, stores location to memeber value
	// else return false and error information, retry if necessary
	StreamReader* request( string url );

	//Where to write to disk? What type of data are we reading in?
	int writeFileToDisk( char *fileContents, string locationOnDisk );


	void markURLSeen( string URL );


	bool shouldURLbeCrawled( string URL );

private:

	int locationOnDisk;
	ProducerConsumerQueue < string > *urlFrontier;
	string mode;
	unordered_map<string, int> *docMapLookup;


	};