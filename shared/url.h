//
// Created by Jake Close on 2/8/18.
//

#pragma once

#include <string>
#include <iostream>
#include "../util/util.h"
//#include "../crawler/StreamReader.h"
//#include "../crawler/SocketReader.h"
using namespace std;

//
//class Url
//	{
//
//public:
//	std::string url;
//
//	Url( string url_in ) : url( url_in )
//		{ };
//
//
//	//Removes/ parses url
//	void clean();
//
//	//parses domain from url
//	string getDomain()
//		{
//		string domain;
//		string protocol = getProtocol();
//		int domainStart = protocol.size() + 3;
//		if(url [ domainStart ] == 'w' )
//			domainStart += 4;//starts with www.
//
//
//
//		for( int domainEnd = domainStart ; domainEnd < url.size() ; domainEnd++ )
//			{
//			if ( url[ domainEnd ] == '/'  || url[ domainEnd ] == ':')
//				return domain;
//			else
//				domain.push_back( url[ domainEnd ] );
//			}
//		}
//
//	//return .gov, .com, .edu
//	string getDomainType()
//		{
//		string domain = getDomain();
//		string type = "";
//
//		auto i = domain.end();
//		--i;
//		while(*i != '.')
//			{
//			type.push_back(( *i ));
//			--i;
//			}
//		reverse(type.begin(), type.end() );
//
//
//		return type;
//
//		}
//
//	/*
//	 * HTTP, HTTPS, MAILTO etc
//	*/
//	string getProtocol()
//		{
//		string protocol;
//		for ( int i = 0; i < url.size( ); i++ )
//			{
//			if( url [ i ] != ':' )
//				protocol.push_back( url [ i ] );
//			else
//				return protocol;
//			}
//
//
//		};
//
//	/*
//	 * Returns URL such that
//	 * http://www.example.com:80/path/to/myfile.html#SomewhereInTheDocument
//	 * becomes http://www.example.com:80/path/to/myfile.html
//	 */
//	void removeAnchor( ){
//		int i = 0;
//		string cleaned;
//		while( url[ i ] != '#')
//			cleaned.push_back( url [ i++ ] );
//
//		url = cleaned;
//		}
//	};








class ParsedUrl
	{
public:
	char  *CompleteUrl,
			*Service,
			*Host,
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

		const char Colon = ':', Slash = '/';
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

			// Whatever remains is the Path.
			Path = p;
			}
		else
			Host = Path = p;
		}

/*
	//check if path in url is in the robots txt
	void checkRobots()
		{
			string pathToRobots = util::GetCurrentWorkingDir() + '/' +  Service;
			int robotsFileD = util::getFileDescriptor(pathToRobots , "R");
			//File does not exist yet
			if(robotsFileD == -1)
				{
					robotsFileD = getRobots();
				}

			char* robotsTXT = util::getFileMap(robotsFileD);



		}



	//Makes request to get a new robots txt file, returns the file pointer
	int getRobots( )
		{

			StreamReader reader;
			string pathToRobots = util::GetCurrentWorkingDir() + '/' +  Service;
			reader = new SocketReader(CompleteUrl+ '/' + 'robots.txt');
			reader->fillBuffer();
			int fd = util::writeToNewFileToLocation( reader->buffer, pathToRobots);
			if( fd == -1)
				{
				cerr << "Error getting Robots.txt file " << endl;
				}
		return fd;

		return 1;
		};
 */
	~ParsedUrl( )
		{
		delete [ ] pathBuffer;
		}

private:
	char *pathBuffer;
	};