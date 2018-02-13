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
        unordered_map<string, vector<int>>* dictionary = pointerToDictionaries.Pop();
        for(auto word : *dictionary) {
            for(auto location : word.second) {
                indexedCount++;
                masterDictionary[word.first].push_back(location);
            }
        }
    }
}

void Indexer::save() {
    map<string, vector<int> > maps(masterDictionary.begin(), masterDictionary.end());
    string fileName = "index" + to_string(currentFile) + ".txt";
    int file = open(fileName.c_str(), O_CREAT | O_WRONLY, S_IRWXU);
    for(auto word : maps) {
        string wordBreak = word.first + "\n";
        write(file, wordBreak.c_str(), strlen(wordBreak.c_str()));
        for(auto location : word.second) {
            string locationSpace = to_string(location) + " ";
            write(file, locationSpace.c_str(), strlen(locationSpace.c_str()));
        }
        write(file, "\n", 1);
    }
    close(file);
    currentFile++;
}

void Indexer::reset() {
    masterDictionary.clear();
    indexedCount = 0;
}
