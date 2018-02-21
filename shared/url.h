//
// Created by Jake Close on 2/8/18.
//

#pragma once

#include <string>
#include <iostream>
#include "../util/util.h"
//#include "../crawler/SocketReader.h"
using namespace std;








class ParsedUrl
	{
public:
	char  *CompleteUrl,
			*Service,
			*Host,
			*Domain,
			*Path;

	ParsedUrl( string input_url )
		{
		// Assumes url points to static text but
		// does not check.

		char *url = new char[input_url.length() + 1];
		strcpy(url, input_url.c_str());

		CompleteUrl = url;

		pathBuffer = new char[ strlen( url ) + 1 ];
		char *f, *t;
		for ( t = pathBuffer, f = url;  *t++ = *f++; )
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
			for(int i = strlen(Host); Host[i] != Period; i--){
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
		}

	void printUrl()
		{
		cout << "Complete URL: " << CompleteUrl << endl;
		cout << "Service: " << Service << endl;
		cout << "Host: " << Host << endl;
		cout << "Path: " << Path << endl;


		}



	~ParsedUrl( )
		{
		delete [ ] pathBuffer;
		}

private:
	char *pathBuffer;
	};