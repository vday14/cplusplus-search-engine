// Linux tiny HTTP server.
// Nicole Hamilton  nham@umich.edu

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <string>

#include <cassert>
//using namespace std;
//  Multipurpose Internet Mail Extensions (MIME) types

struct MimetypeMap
	{
	const char *Extension,
			*Mimetype;
	};

const MimetypeMap MimeTable[] =
		{
				// List of some of the most common MIME types.
				// https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Complete_list_of_MIME_types
				".aac", "audio/aac",
				".abw", "application/x-abiword",
				".arc", "application/octet-stream",
				".avi", "video/x-msvideo",
				".azw", "application/vnd.amazon.ebook",
				".bin", "application/octet-stream",
				".bz", "application/x-bzip",
				".bz2", "application/x-bzip2",
				".csh", "application/x-csh",
				".css", "text/css",
				".csv", "text/csv",
				".doc", "application/msword",
				".docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document",
				".eot", "application/vnd.ms-fontobject",
				".epub", "application/epub+zip",
				".gif", "image/gif",
				".htm", "text/html",
				".html", "text/html",
				".ico", "image/x-icon",
				".ics", "text/calendar",
				".jar", "application/java-archive",
				".jpeg", "image/jpeg",
				".jpg", "image/jpeg",
				".js", "application/javascript",
				".json", "application/json",
				".mid", "audio/midi",
				".midi", "audio/midi",
				".mpeg", "video/mpeg",
				".mpkg", "application/vnd.apple.installer+xml",
				".odp", "application/vnd.oasis.opendocument.presentation",
				".ods", "application/vnd.oasis.opendocument.spreadsheet",
				".odt", "application/vnd.oasis.opendocument.text",
				".oga", "audio/ogg",
				".ogv", "video/ogg",
				".ogx", "application/ogg",
				".otf", "font/otf",
				".png", "image/png",
				".pdf", "application/pdf",
				".ppt", "application/vnd.ms-powerpoint",
				".pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation",
				".rar", "application/x-rar-compressed",
				".rtf", "application/rtf",
				".sh", "application/x-sh",
				".svg", "image/svg+xml",
				".swf", "application/x-shockwave-flash",
				".tar", "application/x-tar",
				".tif", "image/tiff",
				".tiff", "image/tiff",
				".ts", "application/typescript",
				".ttf", "font/ttf",
				".vsd", "application/vnd.visio",
				".wav", "audio/x-wav",
				".weba", "audio/webm",
				".webm", "video/webm",
				".webp", "image/webp",
				".woff", "font/woff",
				".woff2", "font/woff2",
				".xhtml", "application/xhtml+xml",
				".xls", "application/vnd.ms-excel",
				".xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet",
				".xml", "application/xml",
				".xul", "application/vnd.mozilla.xul+xml",
				".zip", "application/zip",
				".3gp", "video/3gpp",
				".3g2", "video/3gpp2",
				".7z", "application/x-7z-compressed"
		};

const char *Mimetype( const std::string filename )
	{
	const char *begin = filename.c_str( ),
			*p = begin + filename.length( ) - 1;
	// Scan back from the end for an extension.
	while ( p >= begin && *p != '.' )
		p--;
	if ( *p == '.' )
		{
		// Found an extension.  Skip over the dot, then
		// binary search for a matching mimetype.

		p++;
		int i = 0, j = sizeof( MimeTable ) / sizeof( MimetypeMap ) - 1;
		while ( i <= j )
			{
			int mid = (i + j) / 2,
					compare = strcasecmp( p, MimeTable[ mid ].Extension + 1 );
			if ( compare == 0 )
				return MimeTable[ mid ].Mimetype;
			if ( compare < 0 )
				j = mid - 1;
			else
				i = mid + 1;
			}
		}

	// Anything not matched is an "octet-stream", treated
	// as an unknown binary, which can be downloaded.
	return "application/octet-stream";
	}

char *ParseGetRequest( char *request )
	{
	// If it's a GET request, null-terminate and
	// return the URL.

	if ( strncmp( request, "GET ", 4 ) == 0 )
		{
		// Skip the get and any additional white space.
		for ( request += 4; *request == ' '; request++ );

		// Now have the start of the URL.
		char *p;
		for ( p = request; *p != ' '; p++ );
		*p = 0;  // null-terminate the URL.

		return request;   // Return the URL.

		}
	return nullptr;   // Not a GET request.
	}


char *RootDirectory;


off_t FileSize( int f )
	{
	struct stat fileInfo;
	fstat( f, &fileInfo );
	return fileInfo.st_size;
	}


void *Talk( void *p )
	{
	// Look for a GET message, then reply with the
	// requested file.

	char buffer[10240];
	int bytes;
	int *pp = (int *) p, s = *pp;
	delete pp;

	std::cout << "Starting recv, s = " << s << std::endl;

	while ((bytes = recv( s, buffer, sizeof( buffer ) - 1, 0 )) > 0 )
		{
		buffer[ bytes ] = 0;
		std::cout << "Request received, s = " << s << std::endl;
		std::cout << buffer << std::endl;
		char *fullUrl = ParseGetRequest( buffer );
		std::string potentialSearch = std::string( fullUrl, strlen( fullUrl ));
		if ( fullUrl )
			{
			std::cout << "Requested url = " << fullUrl << std::endl;
			std::string search = "/search";


			if ( potentialSearch.compare(0,7, "/search") == 0)
				{

				std::cout << "---Making a search GET---" << std::endl;
				potentialSearch = potentialSearch.erase(0, 8);
				std::cout << potentialSearch << std::endl;

				}
			else
				{

				std::string completePath = "";
				std::string Root = std::string( RootDirectory, strlen( RootDirectory ));
				std::string cwd = getenv( "PWD" );
				completePath = cwd + Root + fullUrl;


				//completePath += fullUrl;
				std::cout << "Reqested file = " << completePath << std::endl;

				int f = open( completePath.c_str( ), O_RDONLY );

				if ( f != -1 )
					{
					off_t filesize = FileSize( f );
					std::string okMessage = "HTTP/1.1 200 OK\r\n"
							"Content-Length: ";
					okMessage += std::to_string( filesize );
					okMessage += "\r\nConnection: close\r\nContent-Type: ";
					okMessage += Mimetype( completePath );
					okMessage += "\r\n\r\n";

					std::cout << "Sending" << std::endl;
					std::cout << okMessage;

					send( s, okMessage.c_str( ), okMessage.length( ), 0 );

					while ( bytes = read( f, buffer, sizeof( buffer )))
						send( s, buffer, bytes, 0 );

					close( f );
					}
				else
					{
					std::string fileNotFound = "HTTP/1.1 404 Not Found\r\n"
							"Content-Length: 0\r\n"
							"Connection: close\r\n\r\n";
					send( s, fileNotFound.c_str( ), fileNotFound.length( ), 0 );
					}
				}
			}
		}
	close( s );
	}


void PrintAddress( const sockaddr_in *s, const size_t saLength )
	{
	const struct in_addr *ip = &s->sin_addr;
	uint32_t a = ntohl( ip->s_addr );

	std::cout << "Host address length = " << saLength << " bytes" << std::endl;
	std::cout << "Family = " << s->sin_family <<
				 ", port = " << ntohs( s->sin_port ) <<
				 ", address = " << (a >> 24) << '.' <<
				 ((a >> 16) & 0xff) << '.' <<
				 ((a >> 8) & 0xff) << '.' <<
				 (a & 0xff) << std::endl;
	}


int main( int argc, char **argv )
	{
	if ( argc != 3 )
		{
		std::cerr << "Usage:  LinuxTinyServer port rootdirectory" << std::endl;
		return 1;
		}

	int port = atoi( argv[ 1 ] );
	RootDirectory = argv[ 2 ];

	// Create TCP/IP sockets for listening and talking.

	struct sockaddr_in listenAddress, talkAddress;
	socklen_t talkAddressLength;
	int listenSocket, talkSocket;

	memset( &listenAddress, 0, sizeof( listenAddress ));
	memset( &talkAddress, 0, sizeof( talkAddress ));

	listenAddress.sin_family = AF_INET;
	listenAddress.sin_port = htons( port );
	listenAddress.sin_addr.s_addr = htonl( INADDR_ANY );

	listenSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	assert( listenSocket != -1 );

	int bindResult = bind( listenSocket, (sockaddr *) &listenAddress, sizeof( listenAddress ));
	assert( bindResult == 0 );

	int listenResult = listen( listenSocket, SOMAXCONN );
	assert( listenResult == 0 );

	std::cout << "Listening" << std::endl;
	PrintAddress( &listenAddress, sizeof( listenAddress ));

	while ((talkAddressLength = sizeof( talkAddress ),
			talkSocket = accept( listenSocket, (sockaddr *) &talkAddress,
										&talkAddressLength )) && talkSocket != -1 )
		{
		std::cout << "Connection accepted, talkSocket = " << talkSocket << std::endl;
		PrintAddress( &talkAddress, talkAddressLength );
		pthread_t child;
		pthread_create( &child, nullptr, Talk, new int( talkSocket ));
		}

	close( listenSocket );
	}
