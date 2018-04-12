//
// Created by Jake Close on 3/13/18.
//

#include "ISREndDoc.h"
#include "ISR.h"

ISREndDoc::ISREndDoc() {
    currentChunk = 0;
    openChunk(currentChunk);
}

DocumentEnding ISREndDoc::next() {
    if(memMap == nullptr || *memMap == '\0' ) {
        openChunk(++currentChunk);
    }
    string currentOne;
    for(char* map = memMap; map < memMap + util::FileSize(currentFileHandle); map++) {
        if(*map == '\0') {
            currentChunk++;
            memMap = nullptr;
            return DocumentEnding();
        }
        if(*map == '\n') {
            memMap = map;
            memMap++;
            break;
        }
        switch(*map) {
            case '[':
                currentDoc = DocumentEnding();
                break;
            case ']':
                currentDoc.docNumWords = stoll(currentOne);
                currentOne = "";
                break;
            case ',':
                if(currentDoc.url == "") {
                    currentDoc.url = currentOne;
                    currentOne = "";
                } else if(currentDoc.docEndPosition == 0) {
                    currentDoc.docEndPosition = stoll(currentOne);
                    currentOne = "";
                }
                break;
            case ' ':
                break;
            default:
                currentOne += *map;
                break;
        }
    }


    return currentDoc;
}

void ISREndDoc::openChunk(int chunk) {
    assert(chunk >= 0 && chunk < corpus.chunks.size());
    currentChunk = chunk;
    seekTable.clear();
    memMap = corpus.chunks[chunk].getChunkMap();
    currentFileHandle = corpus.chunks[chunk].chunkFileHandle;
    memMap += stoll(corpus.chunks[chunk].seeker.find("=docEnding"));

    WordSeek entry = WordSeek();
    int currentSeekLookup = 0;
    string input = "";
    string value = corpus.chunks[chunk].wordSeek.find("=docEnding" + to_string(currentSeekLookup));
    while(value != "") {
        for (auto comp : value) {
            switch (comp) {
                case '<':
                    entry = WordSeek();
                    break;
                case '>':
                    entry.seekOffset = stoll(input);
                    seekTable.push_back(entry);
                    input = "";
                    break;
                case ',':
                    entry.realLocation = stoll(input);
                    input = "";
                    break;
                default:
                    input += comp;
                    break;
            }
        }
        currentSeekLookup++;
        value = corpus.chunks[chunk].wordSeek.find("=docEnding" + to_string(currentSeekLookup));
    }
}

void ISREndDoc::seek(Location target) {
    if(target == MAX_Location) {
        return;
    }
    int chunk = currentChunk;
    if(target < corpus.chunks[0].lastLocation) {
        chunk = 0;
    } else {
        while (target > corpus.chunks[chunk].lastLocation) {
            chunk++;
        }
    }

    if(chunk != currentChunk)
        openChunk(chunk);

    if(!seekTable.empty()) {
        WordSeek last = seekTable.front();
        if (target > last.realLocation) {
            for (int i = 1; i < seekTable.size(); i++) {
                if (seekTable[i].realLocation > target && last.realLocation <= target) {
                    break;
                }
                last = seekTable[i];
            }
            memMap = corpus.chunks[chunk].getChunkMap();
            memMap += last.seekOffset;
        }
    }
    while(target > (next().docEndPosition - 1));
}


//void ISREndDoc::seek(Location target) {
//    string key = "=docEnding";
//    string value = "";
//    bool found = false;
//    pair<size_t, size_t> docEndingWordSeek = {0, 0};         // location, offset
//    size_t tempLocation = 0;
//    string input = "";
//    bool init = false;
//    bool breakout = false;
//	bool between = false;
//	 size_t foundChunk;
//    while(!found) {
//        string fileName = util::GetCurrentWorkingDir() +
//                          IndexerConstants::pathToIndex +
//                          to_string(currentChunk) + "-wordseek.txt";
//        if(0 != access(fileName.c_str(), 0)) {
//            currentChunk--;
//            break;
//        }
//        MMDiskHashTable currentWordSeek = MMDiskHashTable(fileName, 30, 168);
//        int currentValueChunk = 0;
//        value = currentWordSeek.find(key + to_string(currentValueChunk));
//        while(value.compare("") != 0) {
//            //cout << "searching through " << key + to_string(currentValueChunk) << endl;
//            for (auto comp : value) {
//                switch (comp) {
//                    case '<':
//                        break;
//                    case '>':
//                        if (target < tempLocation && target > docEndingWordSeek.first)
//									{
//                            if(!init) {
//                                breakout = true;
//                                break;
//                            }
//									breakout = true;
//                            found = true;
//									foundChunk = between ? currentChunk - 1 : currentChunk   ;
//                            break;
//                        	}
//							 	between = false;
//                        init = true;
//                        docEndingWordSeek.first = tempLocation;
//                        docEndingWordSeek.second = stoll(input);
//                        input = "";
//                        break;
//                    case ',':
//                        tempLocation = stoll(input);
//                        input = "";
//                        break;
//                    default:
//                        input += comp;
//                        break;
//                }
//                if (found) {
//                    string fileName = util::GetCurrentWorkingDir() + IndexerConstants::pathToIndex + to_string(foundChunk) + ".txt";
//                    currentFile = open(fileName.c_str(), O_RDONLY);
//                    memMap = (char *) mmap(nullptr, util::FileSize(currentFile), PROT_READ, MAP_PRIVATE, currentFile,
//                                           0);
//                    memMap += docEndingWordSeek.second;
//                }
//                if(breakout) {
//                    break;
//                }
//            }
//            if(breakout) {
//                break;
//            }
//            currentValueChunk++;
//            value = currentWordSeek.find(key + to_string(currentValueChunk));
//        }
//        if(breakout) {
//            break;
//        }
//        currentChunk++;
//		  between = true;
//    }
//
//    while(target > (next().docEndPosition - 1)) {
//    }
//	//next();
//}

DocumentEnding ISREndDoc::getCurrentDoc() {
    return currentDoc;
}

Location ISREndDoc::GetStartingPositionOfDoc( ) {
    return currentDoc.docEndPosition - currentDoc.docNumWords - 1;
}