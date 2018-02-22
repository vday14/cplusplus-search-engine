//
//  main.cpp
//



#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include "crawler/crawler.h"
#include <string>
//#include "crawler/CrawlerStatistics.h"
#include <unordered_map>
#include "util/util.h"
#include <getopt.h>


#define PATH_TO_BLACKLIST = '/bin/blacklist.txt'
#define PATH_TO_VISITED_URL = 'bin/urls.txt'
#define PATH_TO_HTML_DIR = 'bin/html/'
#define PATH_TO_INDEX = 'bin/index/wordIDX'
#define PATH_TO_DOC_INDEX = 'bin/index/docIDX'


using namespace std;


int main( int argc, char *argv[] )
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

	opterr = true;
	int choice;
	int option_index = 0;
	option long_options[] = {
			{"mode", optional_argument, nullptr, 'm'},
			{"num_crawlers", optional_argument, nullptr, 'c'}

	};

	while ((choice = getopt_long(argc, argv, "m:c:", long_options, &option_index)) != -1) {
		switch (choice) {
			case 'm':

				mode = optarg;
				if (mode != "web" && mode != "local") {
					cerr << "Unknown input option";
					exit(1);
				}
				break;

			case 'c':

				numberOfSpiders = atoi(optarg);
				if (numberOfSpiders > 100) {
					cerr << "Too many crawlers!";
					exit(1);
				}
				break;

			default:
				cerr << "Unknown input option";
				exit(1);

		}
	}
	bool restoreFromLog;


	ProducerConsumerQueue < string > urlFrontier;

	char *seeds;
	if ( mode == "local" )
		seeds = util::getFileMap( "/tests/localSeed.txt" );
	else
		seeds = util::getFileMap( "/tests/webSeed.txt" );

	string testFile;
	while ( *seeds )
		{
		if ( *seeds == '\n')
			{
			urlFrontier.Push(testFile);
			testFile = "";
			}

		else
			testFile.push_back(*seeds);
		++seeds;
	}
	urlFrontier.Push(testFile);
//urlFrontier.Push("tests/store.html");


unordered_map < string, int > *docMapLookUp = new unordered_map < string, int >( );
	cout << "-- INDEX IS BUILDING -- " << endl;
	cout << "BUILDING FROM " << mode << endl;
	cout << "RUNNING " << numberOfSpiders << " CRAWLERS " << endl;
Crawler crawler( mode, &urlFrontier );

crawler.SpawnSpiders(numberOfSpiders , docMapLookUp);

crawler.

WaitOnAllSpiders();


}