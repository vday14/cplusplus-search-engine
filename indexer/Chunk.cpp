#include "Chunk.h"

Chunk::Chunk(int number) {
    dictionary = MMDiskHashTable(util::GetCurrentWorkingDir() +
                               IndexerConstants::pathToIndex +
                               to_string(number) + "-dictionary.txt",
                               IndexerConstants::chunkWordSeekKeySize,
                               IndexerConstants::chunkWordSeekValueSize);
    string chunkFileName = util::GetCurrentWorkingDir() +
                           IndexerConstants::pathToIndex +
                           to_string(number) + ".txt";
    chunkFileHandle = open(chunkFileName.c_str(), O_RDONLY);
    numberUniqueWords = stoll(dictionary.find("=numberUniqueWords"));
    numberWords = stoll(dictionary.find("=numberWords"));
    numberDocs = stoll(dictionary.find("=numberDocs"));
}

char* Chunk::getChunkMap() {
    char* chunkMap = util::getFileMap(chunkFileHandle);
    return chunkMap;
}
