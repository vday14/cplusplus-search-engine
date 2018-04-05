//
//  main.cpp
//



#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include "crawler/crawler.h"
#include <openssl/ssl.h>
#include <string>
//#include "crawler/CrawlerStatistics.h"
#include <unordered_map>
#include "util/util.h"
#include <getopt.h>
#include "indexer/Indexer.h"
#include "crawler/UrlFrontier.h"
#include <csignal>
#include <iostream>
#include <chrono>
#include <future>
#include <ctime>
using DocIndex = const unordered_map< string, vector< unsigned long > >;

using namespace std;

string wait_for_user_input()
	{
	std::string answer;
	std::cin >> answer;
	return answer; ;
	}



void signalHandler( int signum ) {
	cout << "Interrupt signal (" << signum << ") received.\n";
	cout << "Ending the Index build" << endl;
	// cleanup and close up stuff here
	// terminate program

	exit(signum);
	}




int main ( int argc, char *argv[] )
	{
	/*
	 *
	 * Settings Flags to control program on start up
	 * to be read in via command line with default settings
	 *
	 * string :  Mode : Getting content from the web vs local
	 *
	 * string : Seed : filename of list of starting urls
	 *
	 * int  : numberOfSpiders: # of spiders crawler spawns
	 *
	 * int  : numberOfParsers:  # of parsers  spawned
	 *
	 * bool : restoreFromLog: bool represeting if the program should load from saved state
	 */

	//



	string mode = "web";
	int numberOfSpiders = 1;
	bool restart = false;
	double DocsToCrawl = 0;
	opterr = true;
	int choice;
	int option_index = 0;
	option long_options[] = {
			{ "mode",         optional_argument, nullptr, 'm' },
			{ "num_crawlers", optional_argument, nullptr, 'c' },
			{ "docsToCrawl", optional_argument, nullptr, 'd' },
			{ "from_restart", optional_argument, nullptr, 'r' }

	};

	while ( ( choice = getopt_long( argc, argv, "m:c:d:r", long_options, &option_index ) ) != -1 )
		{
		switch ( choice )
			{
			case 'm':

				mode = optarg;
				if ( mode != "web" && mode != "local" )
					{
					cerr << "Unknown input option";
					exit( 1 );
					}
				break;

			case 'c':

				numberOfSpiders = atoi( optarg );
				if ( numberOfSpiders > 100 )
					{
					cerr << "Too many crawlers!";
					exit( 1 );
					}
				break;
			case 'r':

				restart = true;
				break;

			case 'd':

				DocsToCrawl = atoi(optarg);
				break;

			default:
				cerr << "Unknown input option";
				exit( 1 );

			}
		}
	bool restoreFromLog;



	UrlFrontier *urlFrontier = new UrlFrontier();
	ProducerConsumerQueue< DocIndex * > *IndexerQueue = new ProducerConsumerQueue< DocIndex * >( );
	ProducerConsumerQueue< unordered_map<string , DocIndex * >  > *AnchorQueue = new ProducerConsumerQueue< unordered_map<string , DocIndex * >  >( );


	char *seeds;
	if ( mode == "local" )
		seeds = util::getFileMap( "/tests/localSeed.txt" );
	else
		{
		seeds = util::getFileMap( "/tests/webSeed.txt" );
		SSL_library_init( );
		}

	if(restart == false)
		{
		string testFile;
		while ( *seeds )
			{
			if ( *seeds == '\n' )
				{

				ParsedUrl * url = new ParsedUrl( testFile );
				cout << "Pushing: " << testFile << " to queue\n";
				urlFrontier->Push( url );
				testFile = "";
				}
			else
				testFile.push_back( *seeds );
			++seeds;
			}
		if ( testFile != "" )
			{
			cout << "Pushing: " << testFile << " to queue\n";
			ParsedUrl * url = new ParsedUrl( testFile );
			urlFrontier->Push( url );
			}
		}
	else
		urlFrontier->readDataFromDisk();




	Indexer indexer( IndexerQueue , AnchorQueue );
	indexer.StartThread( );

	Crawler *crawler = new Crawler( mode, urlFrontier, IndexerQueue, AnchorQueue );
	atomic_bool *alive = new atomic_bool(true);
	crawler->SpawnSpiders( numberOfSpiders , alive);


	string input;
	clock_t start = clock();

	if(DocsToCrawl > 0 )
		{
		cout << "Crawling 100,000 documents for each spider" << endl;
		crawler->WaitOnAllSpiders( );
		crawler->passAnchorTextToIndex( );
		indexer.Kill();
		indexer.WaitForFinish( );
		urlFrontier->writeDataToDisk();
		delete urlFrontier;
		delete IndexerQueue;

		cout << "Indexer has finished running " << endl;
		clock_t end = clock();
		cout << "Time to complete build: " << (end - start) / (double) CLOCKS_PER_SEC << endl;

		return 0;

		}


	while(true)
		{
		cout << "press enter to quit\n" << std::endl ;
		//getline (cin, input);
		cin >> input;
		if(input == "q")
			{

			cout << "Shutting down the indexer  " << endl ;
			crawler->KillAllSpiders();
			crawler->WaitOnAllSpiders( );
			indexer.Kill();
			indexer.WaitForFinish( );
			urlFrontier->writeDataToDisk();

			delete urlFrontier;
			delete IndexerQueue;

			cout << "Indexer has finished running " << endl;
			clock_t end = clock();
			cout << "Time to complete build: " << (end - start) / (double) CLOCKS_PER_SEC << endl;

			return 0;

			}

		}

	}