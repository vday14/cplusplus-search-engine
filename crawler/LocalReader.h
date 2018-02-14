//
// Created by Ben Bergkamp on 2/14/18.
//

#ifndef EECS398_SEARCH_LOCALREADER_H
#define EECS398_SEARCH_LOCALREADER_H

#include "StreamReader.h"

class LocalReader : public StreamReader
	{
	string fileName;
	void fillBuffer(){
		strcpy(buffer, util::getFileMap( fileName )) ;
		}
public:
	LocalReader( string url_in ) : fileName( url_in ) { }

	};

#endif //EECS398_SEARCH_LOCALREADER_H
