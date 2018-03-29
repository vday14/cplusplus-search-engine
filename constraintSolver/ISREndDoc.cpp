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

DocumentEnding ISREndDoc::getCurrentDoc() {
    return currentDoc;
}
