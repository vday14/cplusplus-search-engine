//
// Created by Ben Bergkamp on 2/14/18.
//

#pragma once

#include "StreamReader.h"

class LocalReader : public StreamReader
	{
	string fileName;
	bool fillBuffer(char * buf, size_t buf_size){

		//FIXME
		strcpy(buf, util::getFileMap( fileName )) ;
		return true;
		//FIXME

		}
public:
	LocalReader( string url_in ) : fileName( url_in ) { }

	};

