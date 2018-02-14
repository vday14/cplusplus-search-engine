//
// Created by Ben Bergkamp on 1/31/18.
//

#include "spider.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include "../util/util.h"

#include "LocalReader.h"
#include "SocketReader.h"

namespace filepath
	{
		const char* DOC_MAP = "/docMap.txt";
	}


string Spider::getUrl()
	{
	return urlFrontier->Pop( );
	}

void Spider::FuncToRun()
	{

	std::cout << "Spider is crawling" << endl;
	bool cond = true;


	while ( cond )
		{

		string currentUrl = getUrl( );
		char *fileMap;

		bool toCrawl = shouldURLbeCrawled( currentUrl );
		if(toCrawl)
			//url has not been seen
			{
			if ( cond )
				{
				// markURLSeen( currentUrl );
				//StreamReader* reader = request( currentUrl );
				//parser.parse(fileMap);
				cond = false;
				} else
				{
				cerr << "Error connecting";
				}


			}


		}
	}

/*
Takes a URL. Hashes it. Checks if the url is in the docMapLookup. If it is, check file on disk to see if its been crawled successfully
 if it has been indexed, (check last time index, maybe reindex?) return false (ignore this url)

 if its not in the docMapLookup, get the current size of the docMap on disk, then calculate new location for this docObjec
 create a doc object, find a new place, write the document contents to spot. Write the spot to the cache. Return true

*/

bool Spider::shouldURLbeCrawled( string url )
	{
	//search for url in doc cache
	auto locationOnDisk = this->docMapLookup->find(url);

	//if it doesnt find anything for that url key
	if ( locationOnDisk == this->docMapLookup->end() )
		{
		//cerr << "Url Not Found In Cache Lookup" << endl;
		//get file descriptor for the docMap on disk
			string loc = util::GetCurrentWorkingDir() + filepath::DOC_MAP;
		int file = util::getFileDescriptor( loc.c_str(), "W" );
		//check if its available
		if ( file == -1 )
			cerr << "Error opening docMap" << endl;
		else
			{
			//get the current size of the docMap
			size_t seekPosition = util::FileSize( file );
			//seack to the end of the file
			off_t resultPosition = lseek( file, seekPosition, SEEK_SET );

			if ( resultPosition == -1 )
				{
				cerr << "Could not seek to " << seekPosition <<
					  ", error = " << errno;
				return errno;
				}
			cout << "Current docMap position on disk" << endl;
			cout << resultPosition << endl;

			size_t success = write( file, "Hello World!\n", 14 );
			if ( success == -1 )
				{
				cerr << "Error writing document object to document map" << endl;
				}


			this->docMapLookup->insert( std::pair < string, int >( url, resultPosition ));
			for ( auto it = this->docMapLookup->begin( ); it != this->docMapLookup->end( ); ++it )
				std::cout << it->first << " => " << it->second << '\n';

			close( file );

			}
		}



	else
		{
		//maps url id -> location on disk (where to seek too)

		std::cout << locationOnDisk->first << " is " << locationOnDisk->second;

			string loc = util::GetCurrentWorkingDir() + filepath::DOC_MAP;
		int file = util::getFileDescriptor( loc.c_str(), "R" );
		//check if its available
		if ( file )
			{
			size_t seekPosition = locationOnDisk->second;
			off_t resultPosition = lseek( file, seekPosition, SEEK_SET );
			int bytes = 14;
			if ( bytes >0 )
				{
				char *buffer = new char[ bytes ];
				ssize_t bytesRead;
				if ( bytesRead = read( file, buffer, bytes ) )
					write( 1, buffer, bytesRead );
				else
					{
					cerr << "Could not read " << bytes << " bytes at position " <<
																									resultPosition << ", error = " << errno;
					return errno;
					}
				}
			//
			return false;
			}

		return false;

		}

	}




/*
returns true if fileMap was created, otherwise false
 Modifies the filemap to be a char* of the file of the url passed
*/

StreamReader* Spider::request( string url )
	{
	string localFile;

	StreamReader* newReader;
	if ( this->mode == "local" )
		{
		newReader = new LocalReader( url );
		}
	else if (this->mode == "web")
		{
		newReader = new SocketReader( url );
		}

	newReader->fillBuffer();
	return newReader;
	}

int Spider::writeFileToDisk( char *fileContents, string locationOnDisk )
	{

	return util::writeToNewFileToLocation(fileContents, locationOnDisk);

	}


