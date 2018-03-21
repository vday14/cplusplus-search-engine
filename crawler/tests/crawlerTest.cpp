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
	ProducerConsumerQueue < ParsedUrl > *urlFrontier = new ProducerConsumerQueue < ParsedUrl >( );
	ProducerConsumerQueue < DocIndex * > *IndexerQueue = new ProducerConsumerQueue < DocIndex * >( );
	Indexer indexer( IndexerQueue );
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
	ParsedUrl url = ParsedUrl("http://www.boston.com/cars/specials/herb_chambers_cjd/ram_millbury.htmlhttp://www.jimmyfund.org/ways-to-give/corporate-engagement/cause-marketing/participating-companies/herb-chambers-automotive-family/");
	urlFrontier->Push(url);

	indexer.StartThread( );

	Crawler crawler( mode, urlFrontier, IndexerQueue );
	crawler.SpawnSpiders( numberOfSpiders , duplicateUrlMap );

	crawler.WaitOnAllSpiders( );
	indexer.WaitForFinish( );


	auto f = urlFrontier->Pop( );
	int x = 0;
	delete urlFrontier;
	return 1;
	}