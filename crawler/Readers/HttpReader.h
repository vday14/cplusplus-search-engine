//
// Created by Ben Bergkamp on 3/13/18.
//
#pragma once

#include "StreamReader.h"

class HttpReader : public StreamReader
	{
public:

	HttpReader ( ParsedUrl * url_in ) : url( url_in )
		{ }

	~HttpReader();
	bool request ( );

	bool fillBuffer ( char *buf, size_t buf_size );

	bool checkStatus ( );

	string PageToString ( );

	ParsedUrl * getUrl ( );

	void closeReader ( );


private:

	ParsedUrl * url;
	int sock;

	};
