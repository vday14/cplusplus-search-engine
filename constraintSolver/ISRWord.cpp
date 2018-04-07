
#include <string>
#include "ISRWord.h"


size_t FileSize(int f) {
    struct stat fileInfo;
    fstat( f, &fileInfo);
    return fileInfo.st_size;
}

ISRWord::ISRWord ( string word ) {
	term = word;
	frequency = 0;

	getChunks( );
	if(listOfChunks.size( ) == 0)
		{
		currentLocation = MAX_Location;
		return;
		}
	currentChunk = 0;
	currentLocation = First( );
	DocumentEnd->seek( currentLocation );



}

void ISRWord::getChunks() {
    MMDiskHashTable diskHashTable(util::GetCurrentWorkingDir() + pathToIndex + "master.txt" , 30, 168);
	string value = diskHashTable.find(term);
	int part = 0;
    string chunkInput = "";
    for(char val : value) {
        if(isnumber(val)) {
            chunkInput += val;
        } else if(val == ' ') {
            listOfChunks.push_back(stoll(chunkInput));
            chunkInput = "";
        }  else if(val == '\t' && chunkInput != "") {
        	if(part == 0) {
        		frequency = stoll(chunkInput);
        	} else if(part == 1) {
        		lastLocation = stoll(chunkInput);
        	}
        	part++;
        	chunkInput = "";
        }
    }
    if(chunkInput != "") {
		docFrequency = stoll(chunkInput);
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
	if(listOfChunks.empty()) {
		currentLocation = MAX_Location;
		return MAX_Location;

	}
	string currentChunkSeekFileLocation =
			util::GetCurrentWorkingDir( ) + pathToIndex + to_string( listOfChunks[ currentChunk ] ) +
			"-seek.txt";
    MMDiskHashTable currentChunkSeekFileHashTable = MMDiskHashTable(currentChunkSeekFileLocation, 30, 8);
    string loc = currentChunkSeekFileHashTable.find(term);
	string currentChunkFileLocation =
			util::GetCurrentWorkingDir( ) + pathToIndex + to_string( listOfChunks[ currentChunk ] ) +
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
	 currentLocation = stoll( firstLoc );
	return currentLocation;

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


	//DocumentEnd->seek( currentLocation );
	return currentLocation;
	}

Location ISRWord::getCurrentLocation() {
    return currentLocation;
}

size_t ISRWord::getFrequency() {
	return frequency;
}

size_t ISRWord::getDocFrequency() {
	return docFrequency;
}

size_t ISRWord::getLastLocation() {
	return lastLocation;
}

void ISRWord::getWordSeek() {
	string currentChunkWordSeekFileLocation =
			util::GetCurrentWorkingDir( ) + pathToIndex + to_string( listOfChunks[ currentChunk ] ) +
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
Location ISRWord::Seek( Location target )
	{

	if(target == 124924)
		cout << "Bug target "<< endl;
	 if(target <= currentLocation)
		 return currentLocation;

	size_t lastBest = currentChunk;
	//iterate through the chunks in corpus
	while(currentChunk < listOfChunks.size( ) )
		{
		//find a potential chunk
		Location potentialChunk = listOfChunks[ currentChunk ];

		if(target < corpus.chunks[ potentialChunk  ].lastLocation   )
			{
			lastBest = currentChunk;
			currentChunk++;
			}
			//if past point larger
		else
			currentChunk = lastBest;
			break;

		}
	//have best chunk, initalize files
	First();


	if(!wordSeekLookupTable.empty())
		{
		auto best = wordSeekLookupTable.front( );
		for ( auto entry : wordSeekLookupTable )
			{
			if ( entry.realLocation < target )
				best = entry;
			else
				break;
			}

		currentMemMap += best.seekOffset;
		currentLocation = best.realLocation;

		}

		while(Next() <= target);


	DocumentEnd->seek( currentLocation);
	return currentLocation;







			/*
			 if(!wordSeekLookupTable.empty()) {
				  auto best = wordSeekLookupTable.front();
				  for(auto entry : wordSeekLookupTable) {
						if(entry.realLocation < target) {
							 best = entry;
						} else {
							 string currentChunkFileLocation = util::GetCurrentWorkingDir() + pathToIndex + to_string(listOfChunks[currentChunk]) + ".txt";
							 int currentChunkFile = open(currentChunkFileLocation.c_str(), O_RDONLY);
							 ssize_t currentChunkFileSize = FileSize(currentChunkFile);
							 currentMemMap = (char*) mmap(nullptr, currentChunkFileSize, PROT_READ, MAP_PRIVATE, currentChunkFile, 0);
							 currentMemMap += best.seekOffset;
							 currentLocation = best.realLocation;
							if((DocumentEnd->getCurrentDoc().docEndPosition - DocumentEnd->getCurrentDoc().docNumWords) < currentLocation){
								cerr << "PROBLEM" << endl;
								exit(0);
								}
							 DocumentEnd->seek( currentLocation );

							 return best.realLocation;
						}

				  }
				 cout << "End of for loop"<< endl;
			 } else {
				  while(Next() <= target) {
					cout << "NEXTING" << endl;
				  }

				 cout << "never gets here " << endl;
				if( currentLocation == MAX_Location)
					return MAX_Location;

				 DocumentEnd->seek( currentLocation );
				 return currentLocation;
				 */
}



//Returns the location of the last item in the document you're currently at
Location ISRWord::GetEndDocumentLocation () const
	{
	return DocumentEnd->getCurrentDoc().docEndPosition;
	}

ISREndDoc * ISRWord::GetEndDocument()
	{
	//Fixme
	return DocumentEnd;
	}




string ISRWord::GetTerm()
	{

	return string(this->term);
	}

