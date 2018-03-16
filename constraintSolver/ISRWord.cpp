//
// Created by Jake Close on 3/13/18.
//

#include "ISRWord.h"



void ISRWord::getChunks()
	{
	//Memory map  master index file

	//Binary search thru memory map until you find word

	//Get list of chunks that you need

	//set current chunk



	}


Location ISRWord::First()
	{


		//Go to current chunk

		//Look in seek dictionary for chunk (mem map, binary search)

		//Have offset into chunk, find post seek to post, return value
		//update ISR currentLocation
		//set current memory map
		//returns offset into corpus



	}
//returns next absolute location in corpus

Location ISRWord::Next()
	{

	//looks at memory map

	//if new line ( end of current list for that file

	//move to next chunk, update chunk
	//find new offset, return first location


	//else
	//find way to increment to next delta
	//return new location



	}

Location ISRWord::Seek( Location target )
	{
	//look thru each chunk
	//check if absolute position at offset in chunk is less then chunk,
	//check seek lookup table to find if offset+absulte is bigger than target
		//if so, set location to that big chunk
	//go to next chunk

	}

