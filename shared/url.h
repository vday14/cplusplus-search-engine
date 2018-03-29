//
// Created by Jake Close on 2/8/18.
//

#pragma once

#include <string>
#include <iostream>
#include "../util/util.h"
#include <math.h>
//#include "../crawler/SocketReader.h"
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
	char  *CompleteUrl,
			*Service,
			*Host,
			*Domain,
			*Path;
	double Score;

	ParsedUrl( string input_url )
		{
		// Assumes url points to static text but
		// does not check.

		char *url = new char[input_url.length() + 1];
		strcpy(url, input_url.c_str());

		CompleteUrl = url;

		pathBuffer = new char[ strlen( url ) + 1 ];
		char *f, *t;
		for ( t = pathBuffer, f = url;  (*t++ = *f++); )
			;

		Service = pathBuffer;

		const char Colon = ':', Slash = '/', HashTag = '#', Period = '.';
		char *p;
		for ( p = pathBuffer;  *p && *p != Colon;  p++ )
			;

		if ( *p )
			{
			// Mark the end of the Service.
			*p++ = 0;

			if (*p == Slash)
				p++;
			if (*p == Slash)
				p++;

			Host = p;

			for ( ;  *p && *p != Slash;  p++ )
				;

			if ( *p )
				// Mark the end of the Host.
				*p++ = 0;

			//char * domainBuffer = new char[ 20 ];
			//get the domain:
			char *i = Host;
			for(; *i; i++){

				if(*i == Period)
					Domain = i;

				}





			// Whatever remains is the Path. // need to remove fragments

			Path = p;
			for ( ;  *p && *p != HashTag;  p++ )
				;

			if ( *p )
				// Mark the end of the Path, remove fragments.
				*p++ = 0;


			}
		else
			Host = Path = p;

		setScore();
		}

	void printUrl()
		{
		cout << "Complete URL: " << CompleteUrl << endl;
		cout << "Service: " << Service << endl;
		cout << "Host: " << Host << endl;
		cout << "Domain: " << Domain << endl;
		cout << "Path: " << Path << endl;
		cout << "Score: " << Score << endl;


		}

	void setScore(){
		double lengthOfUrl = strlen(CompleteUrl);
		Score += 4 * 1/ log( lengthOfUrl );

		if ( strcmp ( Domain , ORG ) )
			Score += 5;
		else if ( strcmp ( Domain , EDU ) )
			Score += 4;
		else if ( strcmp ( Domain , GOV ) )
			Score += 3;
		else if ( strcmp ( Domain , COM ) )
			Score += 2;
		else if ( strcmp ( Domain , NET ) )
			Score += 1;
		else if ( strcmp ( Domain , INT ) )
			Score += 1;
		else if ( strcmp ( Domain , MIL ) )
			Score += .5;
		}

	~ParsedUrl( )
		{
		pathBuffer = 0;
		delete [ ] pathBuffer;
		}

private:
	char *pathBuffer;
	};