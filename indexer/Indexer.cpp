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
        unordered_map<string, vector<int> >* dictionary = pointerToDictionaries.Pop();
        DocumentEnding docEnd = DocumentEnding();
        currentBlockNumberDocs++;
        for(auto word : *dictionary) {
            indexedCount += word.second.size();
            totalIndexed += word.second.size();
            currentBlockNumberWords += word.second.size();
            if(word.first.at(0) == '=') {
                docEnd.url = word.first.substr(1, word.first.length());
                continue;
            }
            for(auto location : word.second) {
                masterDictionary[word.first].push_back(currentlyIndexed + location);
            }
        }
        currentlyIndexed += indexedCount;
        docEnd.docEndPosition = currentlyIndexed;
        docEnd.docNumWords = indexedCount;
        docEndings.push_back(docEnd);
        if(currentBlockNumberWords >= 300000) {
            save();
            reset();
        }
        indexedCount = 0;
    }
    save();
    reset();
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
    string footer = "===========\n";
    write(file, header.c_str(), strlen(header.c_str()));
    write(file, uniqueWords.c_str(), strlen(uniqueWords.c_str()));
    write(file, numberWords.c_str(), strlen(numberWords.c_str()));
    write(file, numberDocs.c_str(), strlen(numberDocs.c_str()));
    write(file, footer.c_str(), strlen(footer.c_str()));
    // REALLY GROSS HACK
    int seekOffset = strlen(header.c_str()) +
                     strlen(numberDocs.c_str()) +
                     strlen(numberWords.c_str()) +
                     strlen(uniqueWords.c_str()) +
                     strlen(footer.c_str());


    bool first = true;

    for(auto word : maps) {
        if(first) { //REALLY BAD HACKK
            first = false;
            seeker[word.first] = seekOffset;
        } else {
            seeker[word.first] = seekOffset;
        }
//        string wordBreak = word.first + "\n";
//        write(file, wordBreak.c_str(), strlen(wordBreak.c_str()));
//        seekOffset += strlen(wordBreak.c_str());
        bool first = true;
        size_t lastOne = 0;
        for(auto location : word.second) {
            if(first) {
                string locationSpace = to_string(location) + " ";
                write(file, locationSpace.c_str(), strlen(locationSpace.c_str()));
                seekOffset += strlen(locationSpace.c_str());
                first = false;
            } else {
                size_t delta = location - lastOne;
                string deltaSpace = to_string(delta) + " ";
                write(file, deltaSpace.c_str(), strlen(deltaSpace.c_str()));
                seekOffset += strlen(deltaSpace.c_str());
            }
            lastOne = location;
        }
        write(file, "\n", 1);
        seekOffset += 1;
    }

    string docEndingHeader = "===Document Endings===\n";
    write(file, docEndingHeader.c_str(), strlen(docEndingHeader.c_str()));

    for(auto ending : docEndings) {
        string docEndString = "[" +
                ending.url + ", " +
                to_string(ending.docEndPosition) + ", " +
                to_string(ending.docNumWords) + "]\n";
        write(file, docEndString.c_str(), strlen(docEndString.c_str()));
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
    unordered_map<string, vector<size_t> > lastOne;

    for(auto bucket : masterDictionary) {
        lastOne[bucket.first].push_back(bucket.second.back());
    }

    this->lastOne = lastOne;
    masterDictionary.clear();

    docEndings.clear();

    currentBlockNumberWords = 0;
    currentBlockNumberDocs = 0;
}
