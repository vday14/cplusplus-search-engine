#pragma once

#include "../DataStructures/DiskHashTable/MMDiskHashTable.h"
#include "../util/util.h"
#include "IndexerConstants.h"

class Chunk {

public:

    Chunk(int number);
    MMDiskHashTable seeker;
    MMDiskHashTable wordSeek;
    size_t numberUniqueWords;
    size_t numberWords;
    size_t numberDocs;
    size_t lastLocation;

};