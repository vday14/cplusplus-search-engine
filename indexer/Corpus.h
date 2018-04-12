#pragma once

#include <vector>
#include "../util/util.h"
#include "../DataStructures/DiskHashTable/MMDiskHashTable.h"
#include "WordInfo.h"
#include "Chunk.h"


class Corpus {

private:

    Corpus();

public:

    static Corpus& getInstance();

    WordInfo getWordInfo(string word);
    size_t numberChunks;
    size_t numberDocuments;
    size_t numberWords;
    std::vector<Chunk> chunks;
    MMDiskHashTable master;

};
