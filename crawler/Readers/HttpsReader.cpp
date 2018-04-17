
#include "HttpsReader.h"

std::runtime_error HTTPSconnectionError( "Error connecting HTTPS to url" );

bool HttpsReader::request ( )
	{
	try
	{
		struct hostent *host = gethostbyname( url->getHost().c_str() );

		if ( host == nullptr )
			throw HTTPSconnectionError;

		if( url->getService() != "https")
			throw HTTPSconnectionError;

		assert( host );
		struct sockaddr_in address;
		memset( &address, 0, sizeof( address ) );
		address.sin_family = AF_INET;
		address.sin_port = htons( 443 );
		memcpy( &address.sin_addr, host->h_addr, host->h_length );

		// Create a TCP/IP socket.

		sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if(sock == -1)
			throw HTTPSconnectionError;

		assert( sock != -1 );

		// Connect the socket to the host address.

		int connectResult = connect( sock, ( struct sockaddr * ) &address,
									 sizeof( address ) );

		if(connectResult == -1)
			throw HTTPSconnectionError;

		assert( connectResult == 0 );

		// set timeout val before binding the ssl to the sock
		struct timeval tv;
		tv.tv_sec = 10;
		tv.tv_usec = 0;
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

		// Build an SSL layer and set it to read/write
		// to the socket we've connected.

		ctx = SSL_CTX_new( SSLv23_method( ) );

		assert( ctx );
		ssl = SSL_new( ctx );
		assert( ssl );

		SSL_set_fd( ssl, sock );

		// Establish an SSL connection.

		int sslConnectResult = SSL_connect( ssl );
		if ( sslConnectResult != 1 )
			throw HTTPSconnectionError;
		assert( sslConnectResult == 1 );

		// Send a GET message for the desired page through the SSL.

		string getMessage = "GET ";
		getMessage += url->getCompleteUrl();
		getMessage += " HTTP/1.1\r\nHost: ";
		getMessage += url->getHost();
		getMessage += "\r\nConnection: close\r\n\r\n";

		//cout << getMessage << endl;
		SSL_write( ssl, getMessage.c_str( ), getMessage.length( ) );

		bool isSuccess = checkStatus( );
		return isSuccess;
	}
	catch ( std::exception & e )
	{
		cerr << "Error trying to connect to Host" << url->getCompleteUrl() <<  endl;
		return false;
	}
	}

bool HttpsReader::fillBuffer ( char *buf, size_t buf_size )
	{
	return ( SSL_read( ssl, buf, buf_size ) == buf_size );
	}

string HttpsReader::PageToString ( )
	{

	string temp = "";
	char buf[10240];
	int bytes = 0;

	while ( ( bytes = SSL_read( ssl, buf, 10240 ) ) > 0 )
	{
		temp += string( buf, bytes );
	}
	return temp;
	}

bool HttpsReader::checkStatus ( )
	{
	string code = "";
	char buff[12];
	int bytes = 0;

	bytes = SSL_read( ssl, buff, 12 );


	if ( strncmp( buff, "HTTP/1.1 200", 11 ) == 0 )
		return true;
	else if(strncmp(buff, "HTTP/1.0 400", 11 ) == 0 || strncmp(buff, "HTTP/1.1 400", 11 )  )
		return true;
	else if(strncmp(buff, "HTTP/1.1 302", 11 ) == 0)
	{
		cerr << "URL REDIRECTION" << endl;
		return false;
	}
	cerr << "Bad Request of TYPE::  " << buff << endl;
	return false;

	}


ParsedUrl * HttpsReader::getUrl ( )
	{
	return url;
	}

void HttpsReader::closeReader ( )
	{

	SSL_shutdown( ssl );
	SSL_free( ssl );
	SSL_CTX_free( ctx );
	close( sock );
	}



