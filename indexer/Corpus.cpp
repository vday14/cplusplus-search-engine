#include "Corpus.h"

Corpus::Corpus() {
    master = MMDiskHashTable(util::GetCurrentWorkingDir() +
                      IndexerConstants::pathToIndex +
                      "master.txt",
                      IndexerConstants::masterKeySize,
                      IndexerConstants::masterValueSize);
    numberChunks = stoll(master.find("=numberChunks"));
    numberDocuments = stoll(master.find("=totalDocsIndexed"));
    numberWords = stoll(master.find("=totalNumberIndexed"));
    for(int i = 0; i < numberChunks; i++) {
        chunks.push_back(Chunk(i));
        chunks[i].lastLocation = stoll(master.find("=chunk" + to_string(i)));
    }
}

Corpus& Corpus::getInstance() {
    static Corpus corpus = Corpus();
    return corpus;
}

WordInfo Corpus::getWordInfo(string word) {
    return WordInfo(master.find(word));
}

