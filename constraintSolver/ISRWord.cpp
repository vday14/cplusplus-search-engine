
#include <string>
#include "ISRWord.h"

size_t FileSize(int f) {
    struct stat fileInfo;
    fstat( f, &fileInfo);
    return fileInfo.st_size;
}

ISRWord::ISRWord ( char *word ) {
	term = new char[strlen(word)];
	strcpy(term, word);

	getChunks( );
	currentChunk = 0;
	currentLocation = First( );
}

void ISRWord::getChunks() {
    MMDiskHashTable diskHashTable(util::GetCurrentWorkingDir() + "/constraintSolver/index-test-files/twitter/index-master.txt", 30, 168);
    string value = diskHashTable.find(term);
    string chunkInput = "";
    for(char val : value) {
        if(isnumber(val)) {
            chunkInput += val;
        } else {
            listOfChunks.push_back(stoll(chunkInput));
            chunkInput = "";
        }
    }
}

//Go to current chunk
//Look in seek dictionary for chunk (mem map, binary search)
//Have offset into chunk, find post seek to post, return value
//update ISR currentLocation
//set current memory map
//returns offset into corpus

Location ISRWord::First ( )
	{
	string currentChunkSeekFileLocation =
			util::GetCurrentWorkingDir( ) + "/constraintSolver/index-test-files/twitter/" + to_string( listOfChunks[ currentChunk ] ) +
			"-seek.txt";
    MMDiskHashTable currentChunkSeekFileHashTable = MMDiskHashTable(currentChunkSeekFileLocation, 30, 8);
    string loc = currentChunkSeekFileHashTable.find(term);
	string currentChunkFileLocation =
			util::GetCurrentWorkingDir( ) + "/constraintSolver/index-test-files/twitter/" + to_string( listOfChunks[ currentChunk ] ) +
			".txt";
	int currentChunkFile = open( currentChunkFileLocation.c_str( ), O_RDONLY );
	ssize_t currentChunkFileSize = FileSize( currentChunkFile );
	currentMemMap = ( char * ) mmap( nullptr, currentChunkFileSize, PROT_READ, MAP_PRIVATE, currentChunkFile, 0 );
	currentMemMap += stoll(loc);
    string firstLoc = "";
	while ( *currentMemMap != ' ' ) {
		firstLoc += *currentMemMap;
		currentMemMap++;
    }
	currentMemMap++;
	return stoll( firstLoc );
	}

//returns next absolute location in corpus
//looks at memory map
//if new line ( end of current list for that file
//move to next chunk, update chunk
//find new offset, return first location
//else
//find way to increment to next delta
//return new location

Location ISRWord::Next ( )
	{
	if ( *currentMemMap == '\n' )
		{
		currentChunk++;
        if(listOfChunks.size( ) <= currentChunk)
            {
            currentLocation = 9999999999999;
            return currentLocation;
            }

            currentLocation = First( );
        }
	else
		{
		string delta = "";
		while ( *currentMemMap != ' ' )
			{
			delta += *currentMemMap;
			currentMemMap++;
			}
		currentLocation += stoll( delta );
		currentMemMap++;
		}
	return currentLocation;
	}

Location ISRWord::getCurrentLocation() {
    return currentLocation;
}

//look thru each chunk
//check if absolute position at offset in chunk is less then chunk,
//check seek lookup table to find if offset+absulte is bigger than target
//if so, set location to that big chunk
//go to next chunk
Location ISRWord::Seek( Location target ) {
//    if(!wordSeekLookupTable.empty()) {
//        auto best = wordSeekLookupTable.front();
//        for(auto entry : wordSeekLookupTable) {
//            if(entry.realLocation < target) {
//                best = entry;
//            } else {
//                string currentChunkFileLocation = util::GetCurrentWorkingDir() + "/constraintSolver/index-test-files/twitter/index" + to_string(listOfChunks[currentChunk]) + ".txt";
//                int currentChunkFile = open(currentChunkFileLocation.c_str(), O_RDONLY);
//                ssize_t currentChunkFileSize = FileSize(currentChunkFile);
//                currentMemMap = (char*) mmap(nullptr, currentChunkFileSize, PROT_READ, MAP_PRIVATE, currentChunkFile, 0);
//                currentMemMap += best.seekOffset;
//                currentLocation = best.realLocation;
//                return best.realLocation;
//            }
//        }
//    } else {
//        while(Next() <= target) {
//        }
//        return currentLocation;
//    }
}


Location ISRWord::NextDocument()
	{
	//FixMe
	Location x;
	return x;
	}

Location ISRWord::GetEndDocument()
	{
	//Fixme
	Location x;
	return x;
	}

