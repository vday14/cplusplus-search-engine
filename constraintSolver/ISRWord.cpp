
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
    MMDiskHashTable diskHashTable(util::GetCurrentWorkingDir() + "/constraintSolver/index-test-files/twitter/master.txt", 30, 168);
	string value = diskHashTable.find(term);
    string chunkInput = "";
    for(char val : value) {
        if(isnumber(val)) {
            chunkInput += val;
        } else if(val != '\t') {
            listOfChunks.push_back(stoll(chunkInput));
            chunkInput = "";
        }
    }
	frequency = stoll(chunkInput);
}

//Go to current chunk
//Look in seek dictionary for chunk (mem map, binary search)
//Have offset into chunk, find post seek to post, return value
//update ISR currentLocation
//set current memory map
//returns offset into corpus

Location ISRWord::First ( )
	{
	if(listOfChunks.empty()) {
		currentLocation = MAX_Location;
		return MAX_Location;

	}
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
	getWordSeek();
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
            currentLocation = MAX_Location;
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

void ISRWord::getWordSeek() {
	string currentChunkWordSeekFileLocation =
			util::GetCurrentWorkingDir( ) + "/constraintSolver/index-test-files/twitter/" + to_string( listOfChunks[ currentChunk ] ) +
			"-wordseek.txt";
	MMDiskHashTable wordSeek = MMDiskHashTable(currentChunkWordSeekFileLocation, 30, 168);
	string result = wordSeek.find(term);
	WordSeek wordDictionaryEntry;
	string token = "";
	for(char comp : result) {
		switch(comp) {
			case '<':
				wordDictionaryEntry = WordSeek();
				break;
			case '>':
				wordDictionaryEntry.seekOffset = stoll(token);
				wordSeekLookupTable.push_back(wordDictionaryEntry);
				token = "";
				break;
			case ',':
				wordDictionaryEntry.realLocation = stoll(token);
				token = "";
				break;
			default:
				token += comp;
		}
	}
}

//look thru each chunk
//check if absolute position at offset in chunk is less then chunk,
//check seek lookup table to find if offset+absulte is bigger than target
//if so, set location to that big chunk
//go to next chunk
Location ISRWord::Seek( Location target ) {
    if(!wordSeekLookupTable.empty()) {
        auto best = wordSeekLookupTable.front();
        for(auto entry : wordSeekLookupTable) {
            if(entry.realLocation < target) {
                best = entry;
            } else {
                string currentChunkFileLocation = util::GetCurrentWorkingDir() + "/constraintSolver/index-test-files/twitter/" + to_string(listOfChunks[currentChunk]) + ".txt";
                int currentChunkFile = open(currentChunkFileLocation.c_str(), O_RDONLY);
                ssize_t currentChunkFileSize = FileSize(currentChunkFile);
                currentMemMap = (char*) mmap(nullptr, currentChunkFileSize, PROT_READ, MAP_PRIVATE, currentChunkFile, 0);
                currentMemMap += best.seekOffset;
                currentLocation = best.realLocation;
                return best.realLocation;
            }
        }
    } else {
        while(Next() <= target) {
        }
        return currentLocation;
    }
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

