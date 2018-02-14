//
// Created by Ben Bergkamp on 2/14/18.
//

#include "SocketReader.h"


void SocketReader::fillBuffer()
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

	cout << "Socket Reader is pulling from the web" << endl;

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
	return;
	}