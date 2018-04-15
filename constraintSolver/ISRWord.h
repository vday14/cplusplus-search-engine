#pragma once

#include "ISR.h"
#include <iostream>
#include <vector>
#include <fcntl.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "WordSeek.h"
#include "../indexer/Corpus.h"
#include "../util/util.h"
#include "../DataStructures/DiskHashTable/MMDiskHashTable.h"
#include "ISREndDoc.h"

using namespace std;

class ISRWord : public ISR
	{
public:
    ISRWord ( string word );
    Location openChunk( int chunk );
    Location Next ( ) ;
    Location Seek ( Location target ) override;
    ISREndDoc * GetEndDocument ( ) override;

	unsigned int GetNumWordsInCurrentDoc( );



    unsigned GetDocumentCount ( );

    unsigned GetNumberOfOccurrences ( );

    string GetTerm( );


// ISR *GetDocumentISR( );

    string term;
    vector< WordSeek > wordSeekLookupTable;
    int currentIndex;
    char *currentMemMap;

    //set member variables to all of the chunks that occur, update current chunk
    Location getCurrentLocation();
    size_t getFrequency();
    size_t getDocFrequency();
    size_t getLastLocation();

    Location GetEndDocumentLocation() const;

private:
	void getWordSeek();

	bool justSwitched;
	WordInfo info;
	int currentDocWordFreq;
	Corpus corpus = Corpus::getInstance();


	};


