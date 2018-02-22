#ifndef indexer_h
#define indexer_h
#include "../ProducerConsumerQueue.h"
#include "../ProducerConsumerQueue.cpp"
#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>


/*

Objective: Pulls small dictionaries from the parser and merges them into the 
master index.

*/

using namespace std;

class Indexer {
    public:
        Indexer();
		void run();
		void verbose_run();
		void verbose_save();
		ProducerConsumerQueue<unordered_map<string, vector<int> > * > pointerToDictionaries;
    private:
        void save();
        void reset();
        unordered_map<string, vector<size_t> > masterDictionary;
        size_t indexedCount;
        size_t currentFile;
        size_t totalIndexed;
        size_t currentlyIndexed;
};

#endif /*indexer_h*/
