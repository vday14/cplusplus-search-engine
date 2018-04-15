#include "ISRWord.h"

/**
 * Makes an index stream reader for a word - an easy way to traverse the index and return locations in the corpus that
 * correspond to the term.
 * @param word The term to read from the index.
 */
ISRWord::ISRWord ( string word )
    {
	term = word;
	info = corpus.getWordInfo( word );

	if( info.chunks.size( ) == 0 )
	    {
		currentLocation = MAX_Location;
		return;
        }

	currentIndex = 0;
	justSwitched = false;
	openChunk( currentIndex );
	DocumentEnd->seek( currentLocation );
    }

/**
 * Opens a chunk and reads in the first location of the word corresponding to that chunk.
 * @param index An index into the words chunk list - a way to keep track of the chunks that the word is in.
 * @return The first location that is in the file.
 */
Location ISRWord::openChunk (int index)
	{
	if( info.chunks.empty( ) )
	    {
		currentLocation = MAX_Location;
		return MAX_Location;
	    }
	assert( index >= 0 && index < info.chunks.size( ) );

	MMDiskHashTable& currentChunkSeekFile = corpus.chunks[ info.chunks[ currentIndex ] ].seeker;
    string loc = currentChunkSeekFile.find( term );

    currentMemMap = corpus.chunks[ info.chunks [ currentIndex ] ].getChunkMap( );
	currentMemMap += stoll(loc);

//    string firstLoc = "";
//	while ( *currentMemMap != ' ' )
//        {
//		firstLoc += *currentMemMap;
//		currentMemMap++;
//        }
//
//	currentMemMap++;
	wordSeekLookupTable.clear();
	getWordSeek( );
	Next();
    DocumentEnd->openChunk( info.chunks[currentIndex] );
    justSwitched = true;
	return currentLocation;
	}

/**
 * Goes to the next entry in the postings list.
 * @return The current location (after moving to the next entry).
 */
Location ISRWord::Next ( )
	{
	if( justSwitched )
		{
		justSwitched = false;
		return currentLocation;
		}
	if ( currentMemMap == nullptr || *currentMemMap == '\n' || *currentMemMap == '\0' )
		{
		currentIndex++;
        if( info.chunks.size( ) <= currentIndex )
            {
			currentLocation = MAX_Location;
			return MAX_Location;
            }
		openChunk( currentIndex );
        }
	else
		{
		string termDocFreq = "";
		if(*currentMemMap == '[') {
			currentMemMap++;
			currentDocWordFreq = 0;
			while(*currentMemMap != ']') {
				termDocFreq += *currentMemMap;
				currentMemMap++;
			}
			currentDocWordFreq = stoi(termDocFreq);
			currentMemMap += 2;
		}
		string delta = "";
		while ( *currentMemMap != ' ' && *currentMemMap != '\0' )
			{
			delta += *currentMemMap;
			currentMemMap++;
			}
		if( delta.empty( ) )
			{
            currentLocation = MAX_Location;
			return MAX_Location;
			}
		currentLocation += stoll( delta );
		currentMemMap++;
		}
	return currentLocation;
	}

Location ISRWord::getCurrentLocation ( )
	{
    return currentLocation;
    }

size_t ISRWord::getFrequency ( )
	{
	return info.frequency;
	}

size_t ISRWord::getDocFrequency ( )
	{
	return info.docFrequency;
	}

size_t ISRWord::getLastLocation ( )
	{
	return info.lastLocation;
	}

void ISRWord::getWordSeek ( ) {
	MMDiskHashTable &wordSeek = corpus.chunks[info.chunks[currentIndex]].wordSeek;
	int currentPartition = 0;
	string result = wordSeek.find(term + to_string(currentPartition));

	while (result != "") {
		WordSeek wordDictionaryEntry;
		string token = "";
		for (char comp : result) {
			switch (comp) {
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
		currentPartition++;
		result = wordSeek.find(term + to_string(currentPartition));
	}
}

//look thru each chunk
//check if absolute position at offset in chunk is less then chunk,
//check seek lookup table to find if offset+absulte is bigger than target
//if so, set location to that big chunk
//go to next chunk
Location ISRWord::Seek ( Location target )
	{
	 if(target <= currentLocation)
		 return currentLocation;
	 if(target > getLastLocation())
	     return MAX_Location;

	 int chunk = currentIndex;

	 if(*currentMemMap == '\n')
	     chunk++;

	 if(target < corpus.chunks[info.chunks[0]].lastLocation)
	     chunk = 0;
	 else
	 	 {
	     if(chunk >= info.chunks.size())
	         chunk--;
	     while(target > corpus.chunks[info.chunks[chunk]].lastLocation)
	         chunk++;
	     }


	 if(currentIndex != chunk )
	 	{
        currentIndex = chunk;
        openChunk(chunk);
     	}

	if(!wordSeekLookupTable.empty())
        {
            auto best = wordSeekLookupTable.front( );
            if(target > best.seekOffset)
                {
                for (auto entry : wordSeekLookupTable)
                    {
                    if (entry.seekOffset < target)
                        best = entry;
                    else
                        break;
                    }
                currentMemMap = corpus.chunks[ info.chunks[ currentIndex ] ].getChunkMap( );
                currentMemMap += best.realLocation;
                currentLocation = best.seekOffset;
                }
		}

	while ( Next( ) <= target );

	DocumentEnd->seek( currentLocation );
	return currentLocation;
}



//Returns the location of the last item in the document you're currently at
Location ISRWord::GetEndDocumentLocation () const
	{
	return DocumentEnd->getCurrentDoc().docEndPosition;
	}

ISREndDoc * ISRWord::GetEndDocument()
	{
	return DocumentEnd;
	}

string ISRWord::GetTerm()
	{
	return string(this->term);
	}

unsigned int ISRWord::GetNumWordsInCurrentDoc ( )
	{
	return DocumentEnd->GetNumWordsInDoc();
	}