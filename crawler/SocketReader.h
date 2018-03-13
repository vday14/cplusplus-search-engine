//
// Created by Ben Bergkamp on 2/14/18.
//

#pragma once

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


