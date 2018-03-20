//
// Created by Ben Bergkamp on 1/31/18.
//




#include "spider.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <unistd.h>

#include "LocalReader.h"
#include "SocketReader.h"
#include "../shared/Document.h"
#include "../parser/Parser.h"

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


ParsedUrl Spider::getUrl()
	{
	return urlFrontier->Pop( );
	}

void Spider::FuncToRun()
	{

	std::cout << "Spider is crawling" << endl;
	bool cond = true;


	while ( cond )
		{


		// ParsedUrl stringUrl = getUrl( );	//get url from url frontier
		char *fileMap;
		ParsedUrl currentUrl = getUrl();
		//url has not seen before or time since seen is past certain criteria
		if ( shouldURLbeCrawled( currentUrl ))
			{
			//bool success = writeDocToDisk(currentUrl);
			//if ( success && cond )
			if(cond)
				{


				StreamReader *reader = request( currentUrl );
				size_t docID = hash(currentUrl.CompleteUrl);
				if(this->duplicateUrlMap->find(docID) != this->duplicateUrlMap->end()){
					continue;
					}
				else
					{
					this->duplicateUrlMap->insert(std::make_pair(docID, 1));
					}


				string localPath = util::GetCurrentWorkingDir( );
				// don't include debug in file path
				auto debug = findPrev( "cmake-build-debug", localPath.begin( ) + localPath.size( ) - 1, localPath.begin( ) );
				if ( *debug != '\0' )
					{
					localPath = subStr( localPath.begin( ), debug - 1 );
					}

				string pathToDisk = localPath + "/crawlerOutput/" + to_string(docID)+ ".txt";
				int fd = util::writeToNewFileToLocation( reader->buffer, pathToDisk);

				Document document ( currentUrl, reader->buffer );
				auto dict = parser.execute ( &document );
				
				cout << "docID: " << docID << endl;


				for ( auto it = dict->begin( ); it != dict->end( ); it++ )
					{
					cout << it->first << " : ";
					for ( int i = 0; i < it->second.size( ); ++i )
						{
						cout << it->second[ i ] << " ";
						}
					cout << std::endl;
					}
				cout << std::endl;
				delete dict;
				dict = nullptr;
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


/*
 * Takes in a parsed url,  creates a document object, writes information about the document to disk
 *  returns the begining position of the document on disk, stores that into the in memory lookup hash table
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

/*
 *
 * Takes a parsed url, checks if its in the local in memory hash table of documents return false
 * If url was crawled but past a certain point, reindexs or does not exist , indexes the doc
 * and returns true
 */


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

// make this become a stream reader factory
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

	//remove fill buffer/ change to get request
	newReader->fillBuffer( );
	return newReader;
	}

//request function that handles sending over get request via socket or trying to open file

//Error handling




