#include "Indexer.h"

Indexer::Indexer() {
    indexedCount = 0;
    currentFile = 0;
}

void Indexer::run() {
    while(pointerToDictionaries.Size() != 0) {
        if(indexedCount > 100000) {
            save();
            reset();
        }
        unordered_map<string, vector<int>> dictionary = *pointerToDictionaries.Pop();
        for(auto word : dictionary) {
            for(auto location : word.second) {
                indexedCount++;
                masterDictionary[word.first].push_back(location);
            }
        }
    }
}

void Indexer::save() {
    map<string, vector<int> > maps(masterDictionary.begin(), masterDictionary.end());
    ofstream file("index" + to_string(currentFile) + ".txt");
    for(auto word : maps) {
        file << word.first << endl;
        for(auto location : word.second) {
            file << location << " ";
        }
        file << endl;
    }
    file.close();
    currentFile++;
}

void Indexer::reset() {
    masterDictionary.clear();
    indexedCount = 0;
}
