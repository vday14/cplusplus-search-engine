//
// Created by Jake Close on 2/13/18.
//

#pragma once

#include "../../shared/url.h"
#include "../../util/util.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <string>
#include <cassert>
#include <openssl/ssl.h>



class StreamReader
	{
public:
	StreamReader() {};

	virtual void request() = 0;
	virtual bool fillBuffer(char * buf, size_t buf_size) = 0;
	virtual void closeReader() = 0;

	};

/*
StreamReader* SR_factory(ParsedUrl url, string mode)
	{
	string localFile;

	StreamReader *newReader = nullptr
	;
	if ( mode == "local" )
	{
		newReader = new LocalReader( url.CompleteUrl );
	}
	else if ( mode == "web" )
	{
		if(url.Service == "http") {
			newReader = new HttpReader(url);
		}
		else if(url.Service == "https"){
			newReader = new HttpsReader(url);
		}
	}

	return newReader;
	}
 */