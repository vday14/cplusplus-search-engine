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

size_t Spider::hash(const char * s){
	{
		// http://www.cse.yorku.ca/~oz/hash.html
		size_t h = 5381;
		int c;
		while ((c = *s++))
			h = ((h << 5) + h) + c;
		return h;
	}
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


		string stringUrl = getUrl( );	//get url from url frontier
		char *fileMap;
		ParsedUrl currentUrl = ParsedUrl(stringUrl);
		//url has not seen before or time since seen is past certain criteria
		if ( shouldURLbeCrawled( currentUrl ))
			{
			bool success = writeDocToDisk(currentUrl);
			if ( success && cond )
				{


				StreamReader *reader = request( currentUrl );
				size_t docID = hash(currentUrl.CompleteUrl);
				string pathToDisk = util::GetCurrentWorkingDir() + "/crawlerOutput/" + to_string(docID)+ ".txt";
				int fd = util::writeToNewFileToLocation( reader->buffer, pathToDisk);

				//parser.parse(reader);
				cond = true;
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



bool Spider::writeDocToDisk(ParsedUrl url)
	{
	Document d(url);
	int resultPosition = d.WriteToDocMap();
	if(resultPosition == -1) {
		return false;
	}

	this->docMapLookup->insert( std::pair < string, int >( url.CompleteUrl, resultPosition ));
	for ( auto it = this->docMapLookup->begin( ); it != this->docMapLookup->end( ); ++it )
		std::cout << it->first << " => " << it->second << '\n';

	return true;
	}



bool Spider::shouldURLbeCrawled( ParsedUrl url )
	{
	//search for url in doc cache
	auto locationOnDisk = this->docMapLookup->find( url.CompleteUrl );

	//bool protectedByRobots = checkRobots( url );
	//if it doesnt find anything for that url key
	if ( locationOnDisk == this->docMapLookup->end( ))
		{
			return true;
		}
	else
		{
			//Just for testing
			Document::PrintDocMap(url.CompleteUrl, locationOnDisk->second);
		}
	return false;
	}


//check if path in url is in the robots txt
bool Spider::checkRobots(ParsedUrl url)
	{
	string pathToRobots = util::GetCurrentWorkingDir() + "/robots/" +  string(url.Host, strlen(url.Host)) + ".txt";
	int robotsFileD = util::getFileDescriptor(pathToRobots , "R");
	//File does not exist yet
	if(robotsFileD == -1)
		{
		robotsFileD = getRobots(url);
		}

	char* robotsTXT = util::getFileMap(robotsFileD);
	return 1;
	}



//Makes request to get a new robots txt file, returns the file pointer
int Spider::getRobots(ParsedUrl url )
	{


	string pathToDiskRobots = util::GetCurrentWorkingDir() + "/robots/" +  string(url.Host, strlen(url.Host)) + ".txt";
	string pathToWebRobots =  "https://" + string(url.Host, strlen(url.Host)) + "/robots.txt";
	//string(url.Service, strlen(url.Service))+
	SocketReader *reader = new SocketReader(pathToWebRobots);
	reader->fillBuffer();

	if(reader->buffer != NULL)
		{
		int fd = util::writeToNewFileToLocation( reader->buffer, pathToDiskRobots);
		if( fd == -1)
			cerr << "Error getting Robots.txt file " << endl;

		return fd;
		}

	cerr << "issue filling buffer from robots.txt" << endl;
	return -1;



	};

/*
returns true if fileMap was created, otherwise false
 Modifies the filemap to be a char* of the file of the url passed
*/

StreamReader* Spider::request( ParsedUrl url )
	{
	string localFile;

	StreamReader *newReader;
	if ( this->mode == "local" )
		{
		newReader = new LocalReader( url.CompleteUrl );
		}
	else if ( this->mode == "web" )
		{
		newReader = new SocketReader( url );
		}

	newReader->fillBuffer( );
	return newReader;
	}



