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

using namespace std;


class StreamReader
	{
public:
	StreamReader ( )
		{ };

	virtual bool request ( ) = 0;

	virtual bool fillBuffer ( char *buf, size_t buf_size ) = 0;

	virtual bool checkStatus ( ) = 0;

	virtual string PageToString ( ) = 0;

	virtual ParsedUrl getUrl ( ) =0;

	virtual void closeReader ( ) = 0;
	};


//fix interface with Parsed URL to parser
//implement getUrl function so parser can just call that
//remove stale code from spider.cpp
