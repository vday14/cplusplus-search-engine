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
	int numberOfSpiders = 3;

	opterr = true;
	int choice;
	int option_index = 0;
	option long_options[] = {
			{"mode",         optional_argument, nullptr, 'm'},
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


	ProducerConsumerQueue<ParsedUrl> *urlFrontier = new ProducerConsumerQueue<ParsedUrl>();

	char *seeds;
	if (mode == "local")
		seeds = util::getFileMap("/tests/localSeed.txt");
	else {
		seeds = util::getFileMap("/tests/webSeed.txt");
		SSL_library_init( );

	}

	string testFile;
	while (*seeds) {
		if (*seeds == '\n') {

			ParsedUrl url = ParsedUrl(testFile);
			cout << "Pushing: " << testFile << " to queue\n";
			urlFrontier->Push(url);
			testFile = "";
		} else
			testFile.push_back(*seeds);
		++seeds;
	}
	if (testFile != "") {
		cout << "Pushing: " << testFile << " to queue\n";
		ParsedUrl url = ParsedUrl(testFile);
		urlFrontier->Push(url);
	}
unordered_map < string, int > *docMapLookUp = new unordered_map < string, int >( );

Crawler crawler( mode, urlFrontier );

crawler.SpawnSpiders(numberOfSpiders , docMapLookUp);

crawler.WaitOnAllSpiders();

auto f = urlFrontier->Pop();
	int x = 0;
	delete urlFrontier;
}