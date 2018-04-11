#include "Corpus.h"

Corpus::Corpus() {

    numberChunks = stoll(master.find("=numberChunks"));
    numberDocuments = stoll(master.find("=totalDocsIndexed"));
    numberWords = stoll(master.find("=totalNumberIndexed"));
    for(int i = 0; i < numberChunks; i++) {
        chunks.push_back(Chunk(i));
        chunks[i].lastLocation = stoll(master.find("=chunk" + to_string(i)));
    }
}

WordInfo Corpus::getWordInfo(string word) {
    return WordInfo(master.find(word));
}

