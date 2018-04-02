//
// Created by Jake Close on 3/13/18.
//

#include "ISREndDoc.h"


ISREndDoc::ISREndDoc() {
    currentChunk = 0;
}

DocumentEnding ISREndDoc::next() {
    if(memMap == nullptr) {
        string fileName = util::GetCurrentWorkingDir() + "/constraintSolver/index-test-files/twitter/" + to_string(currentChunk) + ".txt";
        currentFile = open(fileName.c_str(), O_RDONLY);
        MMDiskHashTable de(util::GetCurrentWorkingDir() + "/constraintSolver/index-test-files/twitter/" + to_string(currentChunk) + "-seek.txt", 30, 8);
        memMap = (char*) mmap(nullptr, util::FileSize(currentFile), PROT_READ, MAP_PRIVATE, currentFile, 0);
        memMap += stoll(de.find("=docEnding"));
    }
    string currentOne;
    for(char* map = memMap; map < memMap + util::FileSize(currentFile); map++) {
        if(*map == '\0') {
            currentChunk++;
            memMap = nullptr;
            return DocumentEnding();
        }
        if(currentChunk == 5) {
            DocumentEnding a = DocumentEnding();
            a.url = "aaa";
            return a;
        }
        if(*map == '\n') {
            memMap = map;
            memMap++;
            break;
        }
        switch(*map) {
            case '[':
                currentDoc = DocumentEnding();
                break;
            case ']':
                currentDoc.docNumWords = stoll(currentOne);
                currentOne = "";
                break;
            case ',':
                if(currentDoc.url == "") {
                    currentDoc.url = currentOne;
                    currentOne = "";
                } else if(currentDoc.docEndPosition == 0) {
                    currentDoc.docEndPosition = stoll(currentOne);
                    currentOne = "";
                }
                break;
            case ' ':
                break;
            default:
                currentOne += *map;
                break;
        }
    }
    return currentDoc;
}

// open up current chunk wordseek mem map
// seek all possible keys for doc ending
// check bounds
void ISREndDoc::seek(Location target) {
    string key = "=docEnding";
    string value = "";
    int currentValueChunk = 0;
    bool found = false;
    pair<size_t, size_t> docEndingWordSeek;         // location, offset
    string input = "";
    while(!found) {
        string fileName = util::GetCurrentWorkingDir() +
                          "/constraintSolver/index-test-files/twitter/" +
                          to_string(currentChunk) + "-wordseek.txt";
        if(0 != access(fileName.c_str(), 0)) {
            return;
        }
        MMDiskHashTable currentWordSeek = MMDiskHashTable(fileName, 30, 168);
        value = currentWordSeek.find(key + to_string(currentValueChunk));
        cout << "searching through " << value << endl;
        for(auto comp : value) {
            switch(comp) {
                case '<':
                    docEndingWordSeek = pair<size_t, size_t>();
                    break;
                case '>':
                    docEndingWordSeek.second = stoll(input);
                    input = "";
                    break;
                case ',':
                    if(target < stoll(input) && target > docEndingWordSeek.first) {
                        found = true;
                        break;
                    }
                    docEndingWordSeek.first = stoll(input);
                    input = "";
                    break;
                default:
                    input += comp;
                    break;
            }
            if(found) {
                string fileName = util::GetCurrentWorkingDir() + "/constraintSolver/index-test-files/twitter/" + to_string(currentChunk) + ".txt";
                currentFile = open(fileName.c_str(), O_RDONLY);
                memMap = (char*) mmap(nullptr, util::FileSize(currentFile), PROT_READ, MAP_PRIVATE, currentFile, 0);
                memMap += docEndingWordSeek.second;
                cout << "found" << endl;
                return;
            }
        }
        currentChunk++;
    }
}

DocumentEnding ISREndDoc::getCurrentDoc() {
    return currentDoc;
}

Location ISREndDoc::GetStartingPositionOfDoc( )
    {
    return currentDoc.docEndPosition - currentDoc.docNumWords;
    }