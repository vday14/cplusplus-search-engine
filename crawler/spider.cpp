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
#include "../shared/documentMap.h"


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

		if ( shouldURLbeCrawled( currentUrl ))
			{
			bool success = writeDocToDisk(currentUrl);
			if ( success && cond )
				{


				StreamReader *reader = request( currentUrl );

				//parser.parse(reader);
				cond = false;
				}
			else
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



bool Spider::writeDocToDisk(string url)
	{
	Document d(url);
	int resultPosition = d.WriteToDocMap();
	if(resultPosition == -1) {
		return false;
	}

	this->docMapLookup->insert( std::pair < string, int >( url, resultPosition ));
	for ( auto it = this->docMapLookup->begin( ); it != this->docMapLookup->end( ); ++it )
		std::cout << it->first << " => " << it->second << '\n';

	return true;
	}

bool Spider::shouldURLbeCrawled( string url )
	{
	//search for url in doc cache
	auto locationOnDisk = this->docMapLookup->find( url );

	//if it doesnt find anything for that url key
	if ( locationOnDisk == this->docMapLookup->end( ))
		{
			return true;
		}
	else
		{
			//Just for testing
			Document::PrintDocMap(url, locationOnDisk->second);
		}
	return false;
	}


/*
returns true if fileMap was created, otherwise false
 Modifies the filemap to be a char* of the file of the url passed
*/

StreamReader* Spider::request( string url )
	{
	string localFile;

	StreamReader *newReader;
	if ( this->mode == "local" )
		{
		newReader = new LocalReader( url );
		}
	else if ( this->mode == "web" )
		{
		newReader = new SocketReader( url );
		}

	newReader->fillBuffer( );
	return newReader;
	}

int Spider::writeFileToDisk( char *fileContents, string locationOnDisk )
	{

	return util::writeToNewFileToLocation(fileContents, locationOnDisk);

	}


