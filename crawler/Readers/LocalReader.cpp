//
// Created by Ben Bergkamp on 3/13/18.
//

#include "LocalReader.h"


void LocalReader::request()
	{
	//FIXME
	//open the file?
	}

bool LocalReader::fillBuffer(char * buf, size_t buf_size){

	//FIXME
	strcpy(buf, util::getFileMap( fileName )) ;
	return true;

	}

void LocalReader::closeReader()
	{
	//FIXME
	//close the file?
	}