//
// Created by Jake Close on 2/13/18.
//

#pragma once

#include "../shared/url.h"
#include "../util/util.h"
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
	virtual void fillBuffer() = 0;
	//virtual void close() = 0;
	//virtual void request();
	char *buffer;

	};