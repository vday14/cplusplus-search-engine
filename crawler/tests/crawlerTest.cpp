//
// Created by Jake Close on 3/21/18.
//

#include "../crawler.h"
#include "../spider.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include "../../crawler/crawler.h"
#include <openssl/ssl.h>
#include <string>
#include <unordered_map>
#include "../../util/util.h"
#include <getopt.h>
#include "../../indexer/Indexer.h"



using DocIndex = const unordered_map< string, vector< unsigned long > >;

using namespace std;


int main ( int argc, char *argv[] )
	{

	string mode = "web";
	char *seeds;
	int numberOfSpiders = 1;
	unordered_map < size_t, int > *duplicateUrlMap = new unordered_map < size_t, int >( );
	UrlFrontier *urlFrontier = new UrlFrontier( );
	ProducerConsumerQueue < DocIndex * > *IndexerQueue = new ProducerConsumerQueue < DocIndex * >( );
	ProducerConsumerQueue< unordered_map<string , DocIndex * >  > *AnchorQueue = new ProducerConsumerQueue< unordered_map<string , DocIndex * >  >( );

	Indexer indexer( IndexerQueue , AnchorQueue);
	string path = util::GetCurrentWorkingDir() +"/crawler/tests/testSeeds.txt";
	/*
	seeds =  util::getFileMap( path );



	string testFile;
	while ( *seeds )
		{
		if ( *seeds == '\n' )
			{

			ParsedUrl url = ParsedUrl( testFile );
			cout << "Pushing: " << testFile << " to queue\n";
			urlFrontier->Push( url );
			testFile = "";
			}
		else
			testFile.push_back( *seeds );
		++seeds;
		}
	*/

	SSL_library_init( );
	//string url1 = "https://fivethirtyeight.com";
	//string url2 = "https:";

	string bad_url = "http-equiv=X-UA-Compatiblecontent=IE=edge,chrome=1";
	string bad_url2 ="http-equiv=Content-Type";
	string bad_url3 = "http-equiv=refresh content=1;url=/2.73.0/static/unsupp.html /><![endif]--><!--[if gt IE 9><!--><!--<![endif]--><title>White House says Trump continues to deny Stormy Daniels affair - CNNPolitics</title>";
	//ParsedUrl url = ParsedUrl(bad_url);
	ParsedUrl url1 =  ParsedUrl(bad_url3);
	ParsedUrl url2 =  ParsedUrl(bad_url2);
	urlFrontier->Push(url1);

	urlFrontier->Push(url2);
	indexer.StartThread( );

	Crawler crawler( mode, urlFrontier, IndexerQueue, AnchorQueue );
	atomic_bool *alive = new atomic_bool(true);

	crawler.SpawnSpiders( numberOfSpiders , alive, 10);

	crawler.WaitOnAllSpiders( );
	indexer.WaitForFinish( );


	auto f = urlFrontier->Pop( );
	int x = 0;
	delete urlFrontier;
	return 1;
	}