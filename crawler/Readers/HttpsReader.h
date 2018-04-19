//
// Created by Ben Bergkamp on 3/13/18.
//

#pragma once

#include "StreamReader.h"

class HttpsReader : public StreamReader
	{
public:

	HttpsReader ( ParsedUrl * url_in ) : url( url_in )
		{ }

	~HttpsReader();
	bool request ( );

	bool fillBuffer ( char *buf, size_t buf_size );

	string PageToString ( );

	ParsedUrl * getUrl ( );

	void closeReader ( );

	bool checkStatus ( );

private:
	ParsedUrl * url;
	int sock;
	SSL *ssl;
	SSL_CTX *ctx;
	};
