//
// Created by Ben Bergkamp on 2/14/18.
//

#include "SocketReader.h"

char * GetArbitrarySizeBuffer(SSL* ssl)
	{

	int buf_size = 10240;
	int current_size = buf_size;
	char* ssl_buffer = new char[buf_size];
	char* front = ssl_buffer;
	int bytes;

	while ( ( bytes = SSL_read( ssl, front, buf_size ) ) > 0 )
	{

		current_size  += buf_size;
		char *temp = new char[current_size];
		strcpy(temp, ssl_buffer);

		front = temp + strlen(ssl_buffer);
		delete[] ssl_buffer;
		ssl_buffer = temp;
	}

	return ssl_buffer;
	}


char * GetArbitrarySizeBuffer(int s )
	{

	int buf_size = 10240;
	int current_size = buf_size;
	char* http_buff = new char[buf_size];
	char* front = http_buff;
	int bytes;

	while ( ( bytes = recv( s, front, buf_size, 0 ) ) > 0 )
		{

		current_size  += buf_size;
		char *temp = new char[current_size];
		strcpy(temp, http_buff);

		front = temp + strlen(http_buff);
		delete[] http_buff;
		http_buff = temp;

		}

	return http_buff;
	}




void SocketReader::httpRequest()
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

	char HTTPbuffer[ 10240 ];
	int bytes;


	while ( ( bytes = recv( s, buffer, sizeof( buffer ), 0 ) ) > 0 )
		write( 1, buffer, bytes );

	buffer = GetArbitrarySizeBuffer(s);

	close( s );
	return;
	}


void SocketReader::httpsRequest(){

	struct hostent *host = gethostbyname( url.Host );
	assert( host );

	struct sockaddr_in address;
	memset( &address, 0, sizeof( address ) );
	address.sin_family = AF_INET;
	address.sin_port = htons( 443 );
	memcpy( &address.sin_addr, host->h_addr, host->h_length );

	// Create a TCP/IP socket.

	int s = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	assert( s != -1 );

	// Connect the socket to the host address.

	int connectResult = connect( s, ( struct sockaddr * )&address,
										  sizeof( address ) );
	assert( connectResult == 0 );

	// Build an SSL layer and set it to read/write
	// to the socket we've connected.


	SSL_library_init( );

	SSL_CTX *ctx = SSL_CTX_new( SSLv23_method( ) );
	assert( ctx );
	SSL *ssl = SSL_new( ctx );
	assert( ssl );

	SSL_set_fd( ssl, s );

	// Establish an SSL connection.

	int sslConnectResult = SSL_connect( ssl );
	assert( sslConnectResult == 1 );

	// Send a GET message for the desired page through the SSL.

	string getMessage = "GET ";
	getMessage += url.CompleteUrl;
	getMessage += " HTTP/1.1\r\nHost: ";
	getMessage += url.Host;
	getMessage += "\r\nConnection: close\r\n\r\n";

	cout << getMessage << endl;
	SSL_write( ssl, getMessage.c_str( ), getMessage.length( ) );

	// Read from the SSL until there's no more data.

	buffer = GetArbitrarySizeBuffer(ssl);

	SSL_shutdown( ssl );
	SSL_free( ssl );
	SSL_CTX_free( ctx );
	close( s );


	}





void SocketReader::fillBuffer(  )
	{
	if ( !strcmp(url.Service , "http" ) )
			httpRequest();
	else
			httpsRequest();


	}