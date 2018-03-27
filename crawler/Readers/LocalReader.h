//
// Created by Ben Bergkamp on 2/14/18.
//

#pragma once

#include "StreamReader.h"

class LocalReader : public StreamReader
	{
public:

	LocalReader ( string filename ) : fileName( filename)
		{ }

	bool request ( );

	bool fillBuffer ( char *buf, size_t buf_size );

	ParsedUrl * getUrl ( );

	bool checkStatus ( );

	string PageToString ( );

	void closeReader ( );

	void setUrl(ParsedUrl url);

private:
	string fileName;
	ParsedUrl test_url;
	int fd;

	};

