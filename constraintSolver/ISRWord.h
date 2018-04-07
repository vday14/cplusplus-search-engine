#pragma once

#include "ISR.h"
#include <iostream>
#include <vector>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "WordSeek.h"
#include "../util/util.h"
#include "../DataStructures/DiskHashTable/MMDiskHashTable.h"
#include "ISREndDoc.h"
using namespace std;


//Find occurrences of individual words


class ISRWord : public ISR
	{
	public:
		ISRWord ( string word );


		Location First ( ) ;
		Location Next ( ) ;
		Location Seek ( Location target ) override;
		ISREndDoc * GetEndDocument ( ) override;


		unsigned GetDocumentCount ( );

		unsigned GetNumberOfOccurrences ( );

		string GetTerm( );


	// ISR *GetDocumentISR( );

		string term;
		char *masterIndex;
		vector< size_t > listOfChunks;
		vector< WordSeek > wordSeekLookupTable;
		size_t currentChunk;
		char *currentMemMap;

		//set member variables to all of the chunks that occur, update current chunk
		void getChunks ( );
		Location getCurrentLocation();
		size_t getFrequency();
		size_t getDocFrequency();
		size_t getLastLocation();

		Location GetEndDocumentLocation() const;

private:
	void getWordSeek();
	
    size_t lastLocation;
    size_t docFrequency;
    size_t frequency;

};


