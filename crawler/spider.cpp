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


