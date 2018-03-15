//
// Created by Jake Close on 3/13/18.
//

#pragma once

#include "ISR.h"

//Find occurrences of individual words

class ISRWord : ISR
	{
	public:
		unsigned GetDocumentCount( );
		unsigned GetNumberOfOccurrences( );
		ISR* DocumentEnd;
		// Returns
		virtual Location First( );

		//Returns next post of a word given current location
		virtual Location Next( );

		//Calls seek onto one past the current end doc location
		//Return first instance of word at new document
		virtual Location NextDocument( );
		//Returns first instance of word after target location
		virtual Location Seek( Location target);


		virtual ISR *GetDocumentISR( );

		//Returns the location of the end of the document
		virtual Location GetEndDocument( );

		//Current location of word on disk
		Location currentLocation;
		char* term;
		char* masterIndex;
		vector<size_t> listOfChunks;
		size_t currentChunk;
		char* currentMemMap;

		//set member variables to all of the chunks that occur, update current chunk
		virtual getChunks();



	ISRWord(char * term_in ) : term( term_in )
			{
				getChunks();
				currentLocation = First();


			}
	};


