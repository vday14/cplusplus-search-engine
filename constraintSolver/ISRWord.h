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


		Location First ( ) override;
		Location Next ( ) override;
		Location NextDocument ( ) override;
		Location Seek ( Location target ) override;
		ISREndDoc * GetEndDocument ( ) override;


		unsigned GetDocumentCount ( );

		unsigned GetNumberOfOccurrences ( );

		string GetTerm( );
		ISR * GetISRToBeginningOfDocument ( ) ;


	// ISR *GetDocumentISR( );

		string term;
		char *masterIndex;
		vector< size_t > listOfChunks;
		size_t frequency;
		vector< WordSeek > wordSeekLookupTable;
		size_t currentChunk;
		char *currentMemMap;


		//set member variables to all of the chunks that occur, update current chunk
		void getChunks ( );
		Location getCurrentLocation();

	private:
	void getWordSeek();

	size_t getFrequency();
};


