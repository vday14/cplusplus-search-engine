//
// Created by Ben Bergkamp on 2/14/18.
//

#ifndef EECS398_SEARCH_SOCKETREADER_H
#define EECS398_SEARCH_SOCKETREADER_H

#include "StreamReader.h"


class SocketReader : public StreamReader
	{
public:
	SocketReader( string url_in ) : url( ParsedUrl( url_in ) ) { }
	virtual void fillBuffer();

	//virtual void fillBuffer(char ssl);

private:
	ParsedUrl url;
	};


#endif //EECS398_SEARCH_SOCKETREADER_H
