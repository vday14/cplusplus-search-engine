//
// Created by Jake Close on 3/13/18.
//

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

typedef size_t Location;  // Location 0 is the null location.
const Location MAX_Location = std::numeric_limits<unsigned>::max();

class ISR
	{

public:
	// Returns
	virtual Location First ( ) = 0;

	//Returns next post of a word given current location
	virtual Location Next ( ) = 0;


	//Calls seek onto one past the current end doc location
	//Return first instance of word at new document
	virtual Location NextDocument ( ) = 0;

	//Returns first instance of word after target location
	virtual Location Seek ( Location target ) = 0;


	//Returns the location of the end of the document
	virtual Location GetEndDocument ( ) = 0;





	Location currentLocation;
	ISREndDoc *DocumentEnd = new ISREndDoc ( );



	};


