#pragma once

#include <vector>
#include "../util/util.h"
#include "../DataStructures/DiskHashTable/MMDiskHashTable.h"


#define pathToIndexMaster "/constraintSolver/index-test-files/twitter/master.txt"
#include "WordInfo.h"
#include "Chunk.h"


class Corpus {

public:

    Corpus();

    WordInfo getWordInfo(string word);
    size_t numberChunks;
    size_t numberDocuments;
    size_t numberWords;
    std::vector<Chunk> chunks;
    MMDiskHashTable master = MMDiskHashTable(util::GetCurrentWorkingDir() +
                                             IndexerConstants::pathToIndex +
                                             "master.txt",
                                             IndexerConstants::masterKeySize,
                                             IndexerConstants::masterValueSize);
};
