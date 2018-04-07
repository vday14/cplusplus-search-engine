//
// Created by Jake Close on 3/13/18.
//
//segs with globe

#pragma once

//#include "Post.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits>
#include "ISREndDoc.h"
#include "../indexer/Corpus.h"
#define pathToIndex "/constraintSolver/index-test-files/twitter/"
//#define pathToIndex "/buildIndex/"


//#define pathToIndex "/constraintSolver/index-test-files/twitter/"
//#define pathToIndex "/build/"
typedef size_t Location;  // Location 0 is the null location.
const Location MAX_Location = std::numeric_limits<unsigned>::max();

class ISR
	{

public:
	// Returns

	//Returns next post of a word given current location
	//virtual Location Next ( ) = 0;


	//Calls seek onto one past the current end doc location
	//Return first instance of word at new document
	void NextDocument ( ) {

		currentLocation = Seek( GetEndDocument()->getCurrentDoc().docEndPosition + 1);

		}


	Location GetISRToBeginningOfDocument( )
		{
		return GetEndDocument()->getCurrentDoc().docEndPosition - GetEndDocument()->getCurrentDoc().docNumWords;

		}

	//Returns first instance of word after target location
	virtual Location Seek ( Location target ) = 0;


	//Returns the location of the end of the document
	virtual ISREndDoc * GetEndDocument ( ) = 0;


	Location GetCurrentLocation ( )
		{
		return currentLocation;
		}


	Location currentLocation = 0;
	ISREndDoc *DocumentEnd = new ISREndDoc ( );



	};


