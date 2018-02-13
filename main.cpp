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


    ProducerConsumerQueue<string> urlFrontier;
    ProducerConsumerQueue<int> fileQueue;

    cout << "Pushed File\n";
    urlFrontier.Push("tests/cats.html");
    urlFrontier.Push("tests/store.html");


   unordered_map<string, int>* docMapLookUp = new unordered_map<string, int>();



    Crawler crawler(mode, &urlFrontier);

    crawler.SpawnSpiders(1 , docMapLookUp);

    crawler.WaitOnAllSpiders();



    //This part is a work in progress I was just trying to simulate the
    // parser and see if they could open and read the file

    cout << "Done Waiting\nQueue Size is: " << fileQueue.Size();
   auto top = fileQueue.Pop();
    char buf[100];
    auto ret = read(top, buf, 100);

    cout << "read val: " << ret;
    for(int i = 0; i < 100; i++){

        cout << buf[i];
    }

	
}