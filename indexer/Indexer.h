#ifndef indexer_h
#define indexer_h
#include "../ProducerConsumerQueue.h"
#include "../ProducerConsumerQueue.cpp"
#include "DocumentEnding.h"
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

TODO:
 Use deltas between the offsets
 Save with UTF-8 encoding
 Concrete block size - 100MB per block?
 Save document endings and other relevant metadata?

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
		unordered_map<string, vector<size_t> > lastOne;

        vector<DocumentEnding> docEndings;

        size_t indexedCount;
        size_t currentFile;
        size_t totalIndexed;
        size_t currentlyIndexed;

        size_t currentBlockNumberWords;
        size_t currentBlockNumberDocs;
};

#endif /*indexer_h*/
