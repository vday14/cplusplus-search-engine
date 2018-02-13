//
// Created by Jake Close on 2/8/18.
//

#pragma once

#include <string>
#include <iostream>
using namespace std;
class Url
	{

public:
	std::string url;

	Url( string url_in ) : url( url_in )
		{ };


	//Removes/ parses url
	void clean();

	//parses domain from url
	string getDomain()
		{
		string domain;
		string protocol = getProtocol();
		int domainStart = protocol.size() + 3;
		if(url [ domainStart ] == 'w' )
			domainStart += 4;//starts with www.



		for( int domainEnd = domainStart ; domainEnd < url.size() ; domainEnd++ )
			{
			if ( url[ domainEnd ] == '/'  || url[ domainEnd ] == ':')
				return domain;
			else
				domain.push_back( url[ domainEnd ] );
			}
		}


	string getDomainType()
		{
		string domain = getDomain();
		string type;

		//.gov, .com, .edu
		auto i = domain.end();

		while(*i != '.')
			{
			type.push_back(( *i ));
			--i;
			}
		reverse(type.begin(), type.end() );


		return type;

		}

	/*
	 * HTTP, HTTPS, MAILTO etc
	*/
	string getProtocol()
		{
		string protocol;
		for ( int i = 0; i < url.size( ); i++ )
			{
			if( url [ i ] != ':' )
				protocol.push_back( url [ i ] );
			else
				return protocol;
			}


		};

	/*
	 * Returns URL such that
	 * http://www.example.com:80/path/to/myfile.html#SomewhereInTheDocument
	 * becomes http://www.example.com:80/path/to/myfile.html
	 */
	void removeAnchor( ){
		int i = 0;
		string cleaned;
		while( url[ i ] != '#')
			cleaned.push_back( url [ i++ ] );

		url = cleaned;
		}





	};


