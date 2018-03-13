#include "Indexer.h"

Indexer::Indexer() {
    indexedCount = 0;
    currentFile = 0;
    totalIndexed = 0;
    currentlyIndexed = 0;

    currentBlockNumberWords = 0;
    currentBlockNumberDocs = 0;
}

void Indexer::run() {
    while(pointerToDictionaries.Size() != 0) {
        unordered_map<string, vector<int>>* dictionary = pointerToDictionaries.Pop();
        currentBlockNumberDocs++;
        for(auto word : *dictionary) {
            indexedCount += word.second.size();
            totalIndexed += word.second.size();
            currentBlockNumberWords += word.second.size();
            for(auto location : word.second) {
                masterDictionary[word.first].push_back(currentlyIndexed + location);
            }
        }
        if(currentBlockNumberWords >= 300000) {
            save();
            reset();
        }
        currentlyIndexed += indexedCount;
        indexedCount = 0;
    }
    save();
}

void Indexer::verbose_run() {
    while(pointerToDictionaries.Size() != 0) {
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
    map<string, vector<size_t> > maps(masterDictionary.begin(), masterDictionary.end());
    map<string, size_t> seeker;
    string fileName = "index" + to_string(currentFile) + ".txt";
    int file = open(fileName.c_str(), O_CREAT | O_WRONLY, S_IRWXU);
    // TODO: these should really be c strings
    string header = "===STATS===\n";
    string uniqueWords = "unique words: " + to_string(masterDictionary.size()) + "\n";
    string numberWords = "number words: " + to_string(currentBlockNumberWords) + "\n";
    string numberDocs = "number docs: " + to_string(currentBlockNumberDocs) + "\n";
    string footer = "===SEEK===\n";
    write(file, header.c_str(), strlen(header.c_str()));
    write(file, uniqueWords.c_str(), strlen(uniqueWords.c_str()));
    write(file, numberWords.c_str(), strlen(numberWords.c_str()));
    write(file, numberDocs.c_str(), strlen(numberDocs.c_str()));
    write(file, footer.c_str(), strlen(footer.c_str()));

    for(auto word : maps) {
        string wordBreak = word.first + "\n";
        write(file, wordBreak.c_str(), strlen(wordBreak.c_str()));
        for(auto location : word.second) {
            string locationSpace = to_string(location) + " ";
            write(file, locationSpace.c_str(), strlen(locationSpace.c_str()));
        }
        seeker[word.first] = 013;
        write(file, "\n", 1);
    }

    // TODO: seek dictionary
    string seekFileName = "index" + to_string(currentFile) + "-seek.txt";
    int seekFile = open(seekFileName.c_str(), O_CREAT | O_WRONLY, S_IRWXU);
    for(auto word : seeker) {
        string line = word.first + " " + to_string(word.second) + "\n";
        write(seekFile, line.c_str(), strlen(line.c_str()));
    }

    close(file);
    currentFile++;
}

void Indexer::verbose_save() {
    map<string, vector<size_t> > maps(masterDictionary.begin(), masterDictionary.end());
    for(auto word : maps) {
        cout << word.first << endl;
        for(auto location : word.second) {
            cout << location << " ";
            }
	    cout << endl;
        }
    currentFile++;
    }

void Indexer::reset() {
    unordered_map<string, vector<size_t>> lastOne;

    for(auto bucket : masterDictionary) {
        lastOne[bucket.first].push_back(bucket.second.back());
    }

    this->lastOne = lastOne;
    masterDictionary.clear();

    currentBlockNumberWords = 0;
    currentBlockNumberDocs = 0;
}
