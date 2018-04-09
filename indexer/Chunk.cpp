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
    string chunkFileName = util::GetCurrentWorkingDir() +
                           IndexerConstants::pathToIndex +
                           to_string(number) + ".txt";
    chunkFileHandle = open(chunkFileName.c_str(), O_RDONLY);
    chunkMap = util::getFileMap(chunkFileHandle);
    numberUniqueWords = stoll(seeker.find("=numberUniqueWords"));
    numberWords = stoll(seeker.find("=numberWords"));
    numberDocs = stoll(seeker.find("=numberDocs"));
}
