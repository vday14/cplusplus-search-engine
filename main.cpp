//
//  main.cpp
//



#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <queue>
#include "crawler/crawler.h"
#include <string>
#include <ProducerConsumerQueue.h>
#include <ProducerConsumerQueue.cpp>


#define PATH_TO_BLACKLIST = '/bin/blacklist.txt'
#define PATH_TO_VISITED_URL = 'bin/urls.txt'
#define PATH_TO_HTML_DIR = 'bin/html/'
#define PATH_TO_INDEX = 'bin/index/wordIDX'
#define PATH_TO_DOC_INDEX = 'bin/index/docIDX'


using namespace std;


int main(int argc, const char * argv[])
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
    string mode = "local";
    // Seed urls?
    string seed;
    //
    int numberOfSpiders;
    int numberOfParsers;
    bool restoreFromLog;


    ProducerConsumerQueue urlFrontier;
    ProducerConsumerQueue fileQueue;

    urlFrontier.Push("tests/cats.html");


    Crawler crawler(mode, &urlFrontier, &fileQueue );

    crawler.spawnSpiders(1);

    // crawler.houseKeeper();





	
}