#include "Indexer.h"

Indexer::Indexer() {
}

void Indexer::run() {
    while(pointerToDictionaries.Size() != 0) {
        unordered_map<string, vector<int>>* dictionary = pointerToDictionaries.Pop();
        for(auto it : *dictionary) {
            for(auto location : it.second) {
                cout << location << endl;
            }
        }
    }
}