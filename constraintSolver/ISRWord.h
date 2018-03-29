#pragma once

//#include "ISR.h"
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
#include "ISR.h"
using namespace std;


//Find occurrences of individual words


class ISRWord : public ISR
	{
	public:
		ISRWord ( char *word );

		vector< size_t > getSeekContents ( string fileName );

		unsigned GetDocumentCount ( );

		unsigned GetNumberOfOccurrences ( );

		// ISR* DocumentEnd;
		Location First ( );

		Location Next ( );

		Location nextDocument ( );

		Location Seek ( Location target );



		// ISR *GetDocumentISR( );

		Location GetEndDocument ( );
		Location currentLocation;
		char *term;
		char *masterIndex;
		vector< size_t > listOfChunks;
		vector< WordSeek > wordSeekLookupTable;
		size_t currentChunk;
		char *currentMemMap;

		//set member variables to all of the chunks that occur, update current chunk
		void getChunks ( );
		Location getCurrentLocation();

	private:
};


