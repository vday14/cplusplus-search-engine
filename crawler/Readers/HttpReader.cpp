//
// Created by Ben Bergkamp on 3/13/18.
//

#include "HttpReader.h"


void HttpReader::request()
	{
	sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	assert( sock != -1 );

	// Get the host address.

	struct hostent *host = gethostbyname( url.Host );
	assert( host );

	struct sockaddr_in address;
	memset( &address, 0, sizeof( address ) );
	address.sin_family = AF_INET;
	address.sin_port = htons( 80 );
	memcpy( &address.sin_addr, host->h_addr, host->h_length );

	// Connect to the host.

	int connectResult = connect( sock, ( struct sockaddr * )&address,
								 sizeof( address ) );
	assert( connectResult == 0 );

	// Send a GET message for the desired page.

	cout << "Socket Reader is pulling from the web" << endl;

	string getMessage = "GET ";
	getMessage += url.CompleteUrl;
	getMessage += " HTTP/1.1\r\nHost: ";
	getMessage += url.Host;
	getMessage += "\r\nConnection: close\r\n\r\n";

	cout << getMessage << endl;
	send( sock, getMessage.c_str( ), getMessage.length( ), 0 );

	}

bool HttpReader::fillBuffer(char * buf, size_t buf_size)
	{
	return (recv( sock, buf, buf_size, 0 ) == buf_size);
	}

void HttpReader::closeReader()
	{
	close( sock );
	}