//
// Created by Jake Close on 3/13/18.
//

#include "ISREndDoc.h"


ISREndDoc::ISREndDoc() {
    currentChunk = 0;
}

DocumentEnding ISREndDoc::next() {
    if(memMap == nullptr) {
        string fileName = util::GetCurrentWorkingDir() + "/constraintSolver/index-test-files/twitter/index" + to_string(currentChunk) + ".txt";
        currentFile = open(fileName.c_str(), O_RDONLY);
        vector<size_t> contents = getSeekContents();
        memMap = (char*) mmap(nullptr, util::FileSize(currentFile), PROT_READ, MAP_PRIVATE, currentFile, 0);
        memMap += contents[0];
    }
    string currentOne;
    for(char* map = memMap; map < memMap + util::FileSize(currentFile); map++) {
        if(*map == '\0') {
            currentChunk++;
            memMap = nullptr;
            return DocumentEnding();
        }
        if(currentChunk == 8) {
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

DocumentEnding ISREndDoc::getCurrentDoc() {
    return currentDoc;
}

vector<size_t> ISREndDoc::getSeekContents() {
    string fileName = util::GetCurrentWorkingDir() + "/constraintSolver/index-test-files/twitter/index" + to_string(currentChunk) + "-seek.txt";
    int file = open(fileName.c_str(), O_RDONLY);
    ssize_t fileSize = util::FileSize(file);
    vector<size_t> contents;


    char* memMap = (char*) mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, file, 0);
    // char* memMap = util::getFileMap(fileName);
    string word = "";
    bool midWord = false;
    bool midFind = false;
    if(memMap != MAP_FAILED) {
        for(char* map = memMap; map < memMap + fileSize; map++) {
            if(midFind && isalpha(*map)) {
                break;
            }
            switch(*map) {
                case '\n':
                case '\r':
                case '\t':
                case ' ':
                    if (midFind && word != "") {
                        contents.push_back(stoll(word));
                        word = "";
                    } else if (midWord) {
                        midWord = false;
                        if(word == "=docEnding") {
                            midFind = true;
                        }
                        word = "";
                    }
                    break;
                default:
                    word += *map;
                    midWord = true;
            }
        }
    }
    return contents;
}