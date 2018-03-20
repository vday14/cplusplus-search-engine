//
// Created by Jake Close on 3/13/18.
//

#include "ISRWord.h"

using namespace std;

ISRWord::ISRWord(char* word) : term(word) {
    getChunks();
    currentChunk = 0;
    currentLocation = first();
}

// put into util file
vector<size_t> ISRWord::getSeekContents(string fileName) {
    int file = open(fileName.c_str(), O_RDONLY);
    ssize_t fileSize = FileSize(file);
    vector<size_t> contents;


    char* memMap = (char*) mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, file, 0);
   // char* memMap = util::getFileMap(fileName);
    string word = "";
    bool midWord = false;
    bool midFind = false;
    if(memMap != MAP_FAILED) {
        for(char* map = memMap; map < memMap + fileSize; map++) {
            if(midFind && isalpha(*map)) {
                break;
            }
            switch(*map) {
                case '\t':
                case '\n':
                case '\r':
                case ' ':
                    if (midFind && word != "") {
                        contents.push_back(stoll(word));
                        word = "";
                    } else if (midWord) {
                        midWord = false;
                        if(word == term) {
                            midFind = true;
                        }
                        word = "";
                    }
                    break;
                default:
                    word += *map;
                    midWord = true;
            }
        }
    }
    return contents;
}

void ISRWord::getChunks() {

    listOfChunks = getSeekContents("index-test-files/twitter/index-master.txt");
//    int chunkFile = open("index-test-files/twitter/index-master.txt", O_RDONLY);
//    ssize_t chunkFileSize = FileSize(chunkFile);
//    char* chunkMemMap = (char*) mmap(nullptr, chunkFileSize, PROT_READ, MAP_PRIVATE, chunkFile, 0);
//    string word = "";
//    bool midWord = false;
//    bool midChunkFind = false;
//    if(chunkMemMap != MAP_FAILED) {
//        for(char* map = chunkMemMap; map < chunkMemMap + chunkFileSize; map++) {
//            if(midChunkFind && isalpha(*map)) {
//                break;
//            }
//            switch(*map) {
//                case '\t':
//                case '\n':
//                case '\r':
//                case ' ':
//                    if (midChunkFind && word != "") {
//                        listOfChunks.push_back(stoll(word));
//                        word = "";
//                    } else if (midWord) {
//                        midWord = false;
//                        if(word == term) {
//                            midChunkFind = true;
//                        }
//                        word = "";
//                    }
//                    break;
//                default:
//                    word += *map;
//                    midWord = true;
//            }
//        }
//    }
}

//Go to current chunk
//Look in seek dictionary for chunk (mem map, binary search)
//Have offset into chunk, find post seek to post, return value
//update ISR currentLocation
//set current memory map
//returns offset into corpus

Location ISRWord::first() {
    if(listOfChunks.size() <= currentChunk) {
        exit(0);
    }
    string currentChunkSeekFileLocation = "index-test-files/twitter/index" + to_string(listOfChunks[currentChunk]) + "-seek.txt";
    vector<size_t> location = getSeekContents(currentChunkSeekFileLocation);
    string currentChunkFileLocation = "index-test-files/twitter/index" + to_string(listOfChunks[currentChunk]) + ".txt";
    int currentChunkFile = open(currentChunkFileLocation.c_str(), O_RDONLY);
    ssize_t currentChunkFileSize = FileSize(currentChunkFile);
    currentMemMap = (char*) mmap(nullptr, currentChunkFileSize, PROT_READ, MAP_PRIVATE, currentChunkFile, 0);
    currentMemMap += location[0];
    string firstLoc = "";
    while(*currentMemMap != ' ') {
        firstLoc += *currentMemMap;
        currentMemMap++;
    }
    currentMemMap++;
    return stoll(firstLoc);
}

//returns next absolute location in corpus
//looks at memory map
//if new line ( end of current list for that file
//move to next chunk, update chunk
//find new offset, return first location
//else
//find way to increment to next delta
//return new location

Location ISRWord::next() {
    if(*currentMemMap == '\n') {
        currentChunk++;
        currentLocation = first();
    } else {
        string delta = "";
        while(*currentMemMap != ' ') {
            delta += *currentMemMap;
            currentMemMap++;
        }
        currentLocation += stoll(delta);
        currentMemMap++;
    }
    return currentLocation;
}

//look thru each chunk
//check if absolute position at offset in chunk is less then chunk,
//check seek lookup table to find if offset+absulte is bigger than target
//if so, set location to that big chunk
//go to next chunk

Location ISRWord::seek( Location target ) {

}

