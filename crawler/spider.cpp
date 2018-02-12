//
// Created by Ben Bergkamp on 1/31/18.
//

#include "spider.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../util/util.h"

#include <unistd.h>
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

		shouldURLbeCrawled( currentUrl );


		if ( request( currentUrl, fileMap ))
			{
			// markURLSeen( currentUrl );

			//parser.parse(fileMap);
			cond = false;
			} else
			{
			cerr << "Error connecting";
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

	auto locationOnDisk = this->docMapLookup->find(url);

	if ( locationOnDisk == this->docMapLookup->end() )
		{
		cerr << "Url Not Found In Cache Lookup";
		int file = getFileDescriptor( "/Users/jakeclose/Desktop/398/project/eecs398-search/docMap.txt" );
		if ( file )
			{
			size_t seekPosition = FileSize( file );
			off_t resultPosition = lseek( file, seekPosition, SEEK_SET );

			if ( resultPosition == -1 )
				{
				cerr << "Could not seek to " << seekPosition <<
					  ", error = " << errno;
				return errno;
				}

			cout << "Current docMap position on disk" << endl;
			cout << resultPosition << endl;




			}
		else
			cerr << "Error opening docMap" << endl;


		}


	else
		std::cout << locationOnDisk->first << " is " << locationOnDisk->second;




	}




/*
returns true if fileMap was created, otherwise false
 Modifies the filemap to be a char* of the file of the url passed
*/
bool Spider::request( string url, char *fileMap )
	{
	string localFile;
	if ( this->mode == "local" )
		{
		/*
		char cwd[1024];
		getcwd(cwd, sizeof(cwd));

		char dir[1024];
		for(int i = 0; i < 1024; i++)
			{
				if(cwd[ i ] == 'c' && cwd[ i +1 ] == 'm'){
					for(int j = 0; j < url.size() -1 ; j++){
							dir[j  + i] = url [ j];
						}

					break;

					}

				dir[i] = cwd[i];


			}
		localFile = dir;
		 */
		//string localFile = dir + url;
		fileMap = getFileMap( url );
		if ( fileMap != nullptr )
			return true;
		}
	return false;
	}

int Spider::writeFileToDisk( char *fileContents, string locationOnDisk )
	{

	return writeToNewFileToLocation( fileContents, locationOnDisk );

	}


