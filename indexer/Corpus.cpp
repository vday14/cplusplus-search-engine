#include "Corpus.h"

Corpus::Corpus() {
    auto masterIndex = MMDiskHashTable(util::GetCurrentWorkingDir() + pathToIndexMaster, 30, 168);
    numDocuments = stoll(masterIndex.find("=totalDocsIndexed"));
    numWords = stoll(masterIndex.find("=totalNumberIndexed"));
    int currentChunk = 0;
    string chunkEnding = masterIndex.find("=chunk" + to_string(currentChunk));
    while(chunkEnding != "") {
        chunkEndings.push_back(stoll(chunkEnding));
        currentChunk++;
        chunkEnding = masterIndex.find("=chunk" + to_string(currentChunk));
    }
}

size_t Corpus::getNumDocuments() {
    return numDocuments;
}

size_t Corpus::getNumWords() {
    return numWords;
}

size_t Corpus::getNumChunks() {
    return chunkEndings.size();
}

size_t Corpus::getChunkEnding(size_t chunk) {
    return chunkEndings[chunk];
}

