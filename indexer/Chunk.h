#pragma once

#include <vector>
#include "../DataStructures/DiskHashTable/MMDiskHashTable.h"
#include "../util/util.h"
#include "IndexerConstants.h"

class Chunk {

public:

    Chunk(int number);
    char* getChunkMap();

    int chunkFileHandle;
    MMDiskHashTable dictionary;
    size_t numberUniqueWords;
    size_t numberWords;
    size_t numberDocs;
    size_t lastLocation;

};