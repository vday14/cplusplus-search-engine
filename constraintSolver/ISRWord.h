//
// Created by Jake Close on 3/13/18.
//

#pragma once

//#include "ISR.h"
#include <vector>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../util/util.h"


size_t FileSize(int f) {
    struct stat fileInfo;
    fstat( f, &fileInfo);
    return fileInfo.st_size;
}

using namespace std;

//Find occurrences of individual words

typedef size_t Location;

class ISRWord
	{
public:
        ISRWord(char* word);
        vector<size_t> getSeekContents(string fileName);
        unsigned GetDocumentCount( );
		unsigned GetNumberOfOccurrences( );
		// ISR* DocumentEnd;
        Location first( );
        Location next( );
        Location nextDocument( );
        Location seek( Location target);


        // ISR *GetDocumentISR( );

        Location GetEndDocument( );
	    Location currentLocation;
		char* term;
		char* masterIndex;
		vector<size_t> listOfChunks;
		size_t currentChunk;
		char* currentMemMap;

		//set member variables to all of the chunks that occur, update current chunk
        void getChunks();


private:
};


