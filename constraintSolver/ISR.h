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

typedef size_t Location;  // Location 0 is the null location.

class ISR
	{

public:
	//
	ISR *DocumentEnd;

	// Returns
	virtual Location First ( );

	//Returns next post of a word given current location
	virtual Location Next ( );


	//Calls seek onto one past the current end doc location
	//Return first instance of word at new document
	virtual Location NextDocument ( );

	//Returns first instance of word after target location
	virtual Location Seek ( Location target );


	//Returns the location of the end of the document
	virtual Location GetEndDocument ( );


	Location currentLocation;


	};


