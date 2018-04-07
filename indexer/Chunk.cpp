#include "Chunk.h"

Chunk::Chunk(int number) {
    seeker = MMDiskHashTable(util::GetCurrentWorkingDir() +
                             IndexerConstants::pathToIndex +
                             to_string(number) + "-seek.txt",
                             IndexerConstants::chunkSeekKeySize,
                             IndexerConstants::chunkSeekValueSize);
    wordSeek = MMDiskHashTable(util::GetCurrentWorkingDir() +
                               IndexerConstants::pathToIndex +
                               to_string(number) + "-wordseek.txt",
                               IndexerConstants::chunkWordSeekKeySize,
                               IndexerConstants::chunkWordSeekValueSize);
    numberUniqueWords = stoll(seeker.find("=numberUniqueWords"));
    numberWords = stoll(seeker.find("=numberWords"));
    numberDocs = stoll(seeker.find("=numberDocs"));
}
