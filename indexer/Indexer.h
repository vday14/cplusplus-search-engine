#include "../ProducerConsumerQueue.h"
#include "../ProducerConsumerQueue.cpp"
#include <unordered_map>
#include <vector>
#include <iostream>

/*

Objective: Pulls small dictionaries from the parser and merges them into the 
master index.

*/

using namespace std;

class Indexer {
    public:
        Indexer();
        void run();
        ProducerConsumerQueue<unordered_map<string, vector<int> >*> pointerToDictionaries;
private:
};