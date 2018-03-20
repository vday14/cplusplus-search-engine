//
// Created by Ben Bergkamp on 2/14/18.
//

#pragma once

#include "StreamReader.h"

class LocalReader : public StreamReader
	{
public:

	LocalReader ( string url_in ) : fileName( url_in )
		{ }

	bool request ( );

	bool fillBuffer ( char *buf, size_t buf_size );

	bool checkStatus ( );

	string PageToString ( );

	ParsedUrl getUrl ( );

	void closeReader ( );

private:
	string fileName;

	};

