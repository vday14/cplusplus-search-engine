#pragma once

#include <vector>
#include "../util/util.h"
#include "../DataStructures/DiskHashTable/MMDiskHashTable.h"

#define pathToIndexMaster "/constraintSolver/index-test-files/twitter/master.txt"

class Corpus {

public:

    Corpus();
    size_t getNumDocuments();
    size_t getNumWords();
    size_t getNumChunks();
    size_t getChunkEnding(size_t chunk);

private:

    size_t numDocuments;
    size_t numWords;
    std::vector<size_t> chunkEndings;

};
