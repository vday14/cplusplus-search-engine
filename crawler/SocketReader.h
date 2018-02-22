//
// Created by Ben Bergkamp on 2/14/18.
//

#ifndef EECS398_SEARCH_SOCKETREADER_H
#define EECS398_SEARCH_SOCKETREADER_H

#include "StreamReader.h"


class SocketReader : public StreamReader
	{
public:
	SocketReader( ParsedUrl url_in ) : url(  url_in  ) { }
	virtual void fillBuffer();
	void httpRequest();
	void httpsRequest();


	//virtual void fillBuffer(char ssl);

private:
	ParsedUrl url;
	};


#endif //EECS398_SEARCH_SOCKETREADER_H
