//
// Created by Ben Bergkamp on 4/16/18.
//


#pragma once

#include <string>
#include <iostream>
#include "../util/util.h"
#include <math.h>
#include <time.h>
#include <string.h>
#include "../util/stringProcessing.h"
#include <algorithm>
using namespace std;

#define GOV   ".gov"
#define COM   ".com"
#define EDU   ".edu"
#define ORG   ".org"
#define NET   ".net"
#define MIL   ".mil"
#define INT   ".int"


class ParsedUrl
	{
public:
	ParsedUrl();
	ParsedUrl ( string input_url );
	void printUrl ( );
	void setScore();
	string getDomain ( );
	string getService ( );
	string getCompleteUrl ( );
	string getHost ( );
	string getPath ( );
	double getScore ( );
	void updateScore( double time );
	string getAnchorText ( );
	void setAnchorText ( std::string anchorText );
	~ParsedUrl();
	bool isValid = true;

private:
	string CompleteUrl,
			Service,
			Host,
			Domain,
			Path,
			AnchorText;
	double Score = 0;
	char *pathBuffer;



	};


