
#include "Document.h"

string Document::DocToString ( )
	{
	return string( docString, strlen( docString ) ) + "\n";
	}

int Document::WriteToDocMap ( )
	{

	pthread_mutex_lock( &docMap_mutex );

	//for now just write url

	string loc = util::GetCurrentWorkingDir( ) + filepath::DOC_MAP;
	int file = util::getFileDescriptor( loc.c_str( ), "W" );
	off_t resultPosition = 0;

	try
		{
		//check if its available
		if ( file == -1 )
			{
			throw ( "error opening docMap" );
			}
		else
			{
			//get the current size of the docMap
			size_t seekPosition = util::FileSize( file );
			//seek to the end of the file
			resultPosition = lseek( file, seekPosition, SEEK_SET );

			if ( resultPosition == -1 )
				{
				throw ( "Could not seek" );
				}
			cout << "Current docMap position on disk" << endl;
			cout << resultPosition << endl;

			size_t success = write( file, this->DocToString( ).c_str( ),
			                        strlen( this->DocToString( ).c_str( ) ) );
			if ( success == -1 )
				{
				throw ( "Error writing document object to document map" );
				}
			}
		}
	catch ( const char *str )
		{
		cerr << str << endl;
		close( file );
		pthread_mutex_unlock( &docMap_mutex );
		return -1;
		}
	close( file );
	pthread_mutex_unlock( &docMap_mutex );
	return resultPosition;
	}


ParsedUrl Document::getUrl ( )
	{
	return this->url;
	}


void Document::PrintDocMap ( string url, int location )
	{
	pthread_mutex_lock( &docMap_mutex );

	std::cout << url << " is " << location;

	string loc = util::GetCurrentWorkingDir( ) + filepath::DOC_MAP;
	int file = util::getFileDescriptor( loc.c_str( ), "R" );


	//check if its available
	if ( file )
		{
		off_t resultPosition = lseek( file, ( size_t ) location, SEEK_SET );
		int bytes = 14;
		if ( bytes > 0 )
			{
			char *buffer = new char[bytes];
			ssize_t bytesRead;
			if ( ( bytesRead = read( file, buffer, bytes ) ) )
				write( 1, buffer, bytesRead );
			else
				{
				cerr << "Could not read " << bytes << " bytes at position " <<
				     resultPosition << ", error = " << errno;
				pthread_mutex_unlock( &docMap_mutex );
				return;
				}
			}

		}
	pthread_mutex_unlock( &docMap_mutex );
	return;

	};