#pragma once

#include <iostream>
#include <string>

using namespace std;

class DocumentEnding
	{
public:

	DocumentEnding ( )
		{
		docEndPosition = 0;
		docNumWords = 0;
		url = "";
		title = "";
		}

	size_t docEndPosition;
	size_t docNumWords;
	string url;
	string title;
	};