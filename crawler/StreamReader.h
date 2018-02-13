//
// Created by Jake Close on 2/13/18.
//

#pragma once

#include "../shared/url.h"
#include "../util/util.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <string>
#include <cassert>
class StreamReader
	{
	public:
		char *buffer;
		virtual void fillBuffer() = 0;


	StreamReader(){	};

	};





class SocketReader : public StreamReader
	{
	ParsedUrl url;
	void fillBuffer()
		{
		int s = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		assert( s != -1 );

		// Get the host address.

		struct hostent *host = gethostbyname( url.Host );
		assert( host );

		struct sockaddr_in address;
		memset( &address, 0, sizeof( address ) );
		address.sin_family = AF_INET;
		address.sin_port = htons( 80 );
		memcpy( &address.sin_addr, host->h_addr, host->h_length );

		// Connect to the host.

		int connectResult = connect( s, ( struct sockaddr * )&address,
											  sizeof( address ) );
		assert( connectResult == 0 );

		// Send a GET message for the desired page.

		string getMessage = "GET ";
		getMessage += url.CompleteUrl;
		getMessage += " HTTP/1.1\r\nHost: ";
		getMessage += url.Host;
		getMessage += "\r\nConnection: close\r\n\r\n";

		cout << getMessage << endl;
		send( s, getMessage.c_str( ), getMessage.length( ), 0 );

		// Read from the socket until there's no more data.

		char buffer[ 10240 ];
		int bytes;

		while ( ( bytes = recv( s, buffer, sizeof( buffer ), 0 ) ) > 0 )
			write( 1, buffer, bytes );

		close( s );
		}

public:
	SocketReader( string url_in ) : url( ParsedUrl( url_in ) ) { }




	};


class LocalReader : public StreamReader
	{
	string fileName;
	void fillBuffer(){
		strcpy(buffer, getFileMap( fileName )) ;
		}
public:
	LocalReader( string url_in ) : fileName( url_in ) { }

	};
