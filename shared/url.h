
#pragma once

#include <string>
#include <iostream>
#include "../util/util.h"
#include <math.h>
#include <time.h>
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
private:
	string CompleteUrl,
			Service,
			Host,
			Domain,
			Path,
			AnchorText;
	double Score = 0;


public:


	ParsedUrl() {}

	ParsedUrl ( string input_url )
		{
		// Assumes url points to static text but
		// does not check.
		try
			{

			char *temp_CompleteUrl,
					*temp_Service,
					*temp_Host,
					*temp_Domain,
					*temp_Path,
					*temp_AnchorText,
					*temp_pathBuffer;

			//intialize anchor text to ""
			char *null = new char[2];
			strcpy( null, string( "" ).c_str( ) );
			temp_AnchorText = null;

			char *url = new char[input_url.length( ) + 1];
			strcpy( url, input_url.c_str( ) );

			temp_CompleteUrl = url;

			temp_pathBuffer = new char[strlen( url ) + 1];
			char *f, *t;
			for ( t = temp_pathBuffer, f = url; ( *t++ = *f++ ); );

			temp_Service = temp_pathBuffer;


					const char Colon = ':', Slash = '/', HashTag = '#', Period = '.';
					char *p;
					for ( p = temp_pathBuffer; *p && *p != Colon; p++ );

					if ( *p )
					{
						// Mark the end of the Service.
						*p++ = 0;

						if ( *p == Slash )
							p++;
						if ( *p == Slash )
							p++;

						temp_Host = p;

						for ( ; *p && *p != Slash; p++ );

						if ( *p )
							// Mark the end of the Host.
							*p++ = 0;

						//char * domainBuffer = new char[ 20 ];
						//get the domain:
						char *i = temp_Host;
						temp_Domain = nullptr;
						if(i)
						{
							for ( ; *i; i++ )
							{
								if ( *i == Period )
									temp_Domain = i;
							}
						}

						// Whatever remains is the Path. // need to remove fragments

						temp_Path = p;
						for ( ; *p && *p != HashTag; p++ );

						if ( *p )
							// Mark the end of the Path, remove fragments.
							*p++ = 0;
					}
					else
						temp_Host = temp_Path = p;


					CompleteUrl = string(temp_CompleteUrl, strlen(temp_CompleteUrl));
					Service = string(temp_Service, strlen(temp_Service));
					Host = string(temp_Host, strlen(temp_Host));

			if(Service == "http" || Service == "https")
				{
					if(  temp_Domain != nullptr )
						Domain = string(temp_Domain, strlen(temp_Domain));

					Path = string(temp_Path, strlen(temp_Path));
					AnchorText = string(temp_AnchorText, strlen(temp_AnchorText));
					pathBuffer = temp_pathBuffer;

					setScore( );
				}
			else
				isValid = false;



			}
		catch (exception e)
			{
			cerr << "Error constructing a ParsedUrl from string url "<< endl;


			}

		}

	void printUrl ( )
		{
		cout << "Complete URL: " << CompleteUrl << endl;
		cout << "Service: " << Service << endl;
		cout << "Host: " << Host << endl;
		cout << "Domain: " << Domain << endl;
		cout << "Path: " << Path << endl;
		cout << "Score: " << Score << endl;


		}

	void setScore()
		{
		double lengthOfUrl = CompleteUrl.length();
		Score +=  1/ ( lengthOfUrl );

		if(lengthOfUrl > 4)
		{

			if(this->Domain.length() )

			{
				if ( strcmp ( Domain.c_str() , ORG ) )
					Score += .5;
				else if ( strcmp ( Domain.c_str() , EDU ) )
					Score += 1;
				else if ( strcmp ( Domain.c_str() , GOV ) )
					Score += 1;
				else if ( strcmp ( Domain.c_str() , COM ) )
					Score += 2;
				else if ( strcmp ( Domain.c_str() , NET ) )
					Score += 3;
				else if ( strcmp ( Domain.c_str() , INT ) )
					Score += 4;
				else if ( strcmp ( Domain.c_str() , MIL ) )
					Score += 5;
			}

		}
		}

	std::string getDomain ( )
		{
		return Domain;
		}

	std::string getService ( )
		{
		return Service;
		}

	std::string getCompleteUrl ( )
		{
		return CompleteUrl;
		}

	std::string getHost ( )
		{
		return Host;
		}

	std::string getPath ( )
		{
		return Path;
		}


	double getScore ( )
		{
		return Score;
		}

	void updateScore( double time )
		{

		Score +=   time;
		}

	std::string getAnchorText ( )
		{
		return AnchorText;
		}

	void setAnchorText ( std::string anchorText )
		{
		AnchorText = anchorText;
		}


	~ParsedUrl ( )
		{
		pathBuffer = 0;
		delete[] pathBuffer;
		}

	bool isValid = true;
private:
	char *pathBuffer;
	};