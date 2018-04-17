#include "spider.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../shared/Document.h"
#include "../parser/Parser.h"
#include "Readers/HttpsReader.h"
#include "Readers/HttpReader.h"
#include "Readers/LocalReader.h"
#include "../parser/Parser.h"
#include "UrlFrontier.h"


using DocIndex = const unordered_map< string, vector< unsigned long > >;

// FIND A BETTER PLACE TO PUT THIS FUNCTION
/*
 *
 * Factory function to create the proper stream reader
 *
 */
StreamReader *SR_factory ( ParsedUrl * url, string mode )
	{
	string localFile;

	StreamReader *newReader = nullptr;
	if ( mode == "local" )
	{
		newReader = new LocalReader( url->getCompleteUrl() );
	}
	else if ( mode == "web" )
	{
		if ( url->getService() == "http" )
		{
			newReader = new HttpReader( url );
		}
		else if ( url->getService() == "https" )
		{
			newReader = new HttpsReader( url );
		}
		else
		{
			cerr << "Error reading service type\n";
			cerr << "Service Type: " << url->getService() << "\n";
		}
	}

	return newReader;
	}

void printDocIndex ( DocIndex *dict )
	{
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

	}
/*
 * Hash function
 *
 */

size_t Spider::hash ( const char *s )
	{
	// http://www.cse.yorku.ca/~oz/hash.html
	size_t h = 5381;
	int c;
	while ( ( c = *s++ ) )
		h = ( ( h << 5 ) + h ) + c;
	return h;
	}

/*
 *
 * Gets a parsed url from the url frontier
 *
 */

ParsedUrl Spider::getUrl ( )
	{
	return urlFrontier->Pop( );
	}

/*
 *
 * Main function spider runs
 *
 * continue while atomic bool alive or has crawled X amount of docs
 * gets the url off the queue
 * creates a relevent stream reader
 * attempts to download page
 * if successful, pass page to parsed
 * parser creates a dict which is then passed to the indexer
 */

void Spider::run ( )
	{
	std::cout << "Spider is crawling" << endl;
	int cond = 0;
	ParsedUrl currentUrl;


	while (*alive && cond < docs_to_crawl)
	{
		bool not_empty = urlFrontier->try_pop(currentUrl);

		if(not_empty) {
			size_t docID = hash(currentUrl.getCompleteUrl().c_str());
			if (shouldURLbeCrawled(docID)) {
				StreamReader *reader = SR_factory(&currentUrl, this->mode);
				if (reader) {
					bool success = reader->request();
					if (success) {
						//cout << "Parsing " << currentUrl.getCompleteUrl();
						DocIndex *dict = parser.execute(reader);
						IndexerQueue->Push(dict);

						reader->closeReader();
						//delete dict;

						cond++;
					}
				}


				delete reader;


			}
		}
	}
	cout << "Spider has finished running " << endl;
	return;
	}


//Make the atomic bool false
void Spider::kill()
	{
	*(this->alive) = false;
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


bool Spider::writeDocToDisk ( ParsedUrl url )
	{
	/*
	Document d( url );
	int resultPosition = d.WriteToDocMap( );
	if ( resultPosition == -1 )
		{
		return false;
		}

	this->docMapLookup->insert( std::pair< string, int >( url.CompleteUrl, resultPosition ) );
	for ( auto it = this->docMapLookup->begin( ); it != this->docMapLookup->end( ); ++it )
		{
		std::cout << it->first << " => " << it->second << '\n';
		}
	*/
	return true;
	}

/*
 *
 * Takes a parsed url, checks if its in the local in memory hash table of documents return false
 * If url was crawled but past a certain point, reindexs or does not exist , indexes the doc
 * and returns true
 */

bool Spider::shouldURLbeCrawled ( size_t docID )
	{

	/*
	if ( this->duplicateUrlMap->find( docID ) != this->duplicateUrlMap->end( ) )
		{
		return false;
		}
	else
		{
		this->duplicateUrlMap->insert( std::make_pair( docID, 1 ) );
		return true;
		}
	 */
	return true;
	}

/*
//check if path in url is in the robots txt
bool Spider::checkRobots ( ParsedUrl url )
	{
	string pathToRobots = util::GetCurrentWorkingDir( ) + "/robots/" + string( url.Host, strlen( url.Host ) ) + ".txt";
	int robotsFileD = util::getFileDescriptor( pathToRobots, "R" );
	//File does not exist yet
	if ( robotsFileD == -1 )
		{
		robotsFileD = getRobots( url );
		}

	char *robotsTXT = util::getFileMap( robotsFileD );
	return 1;
	}


//Makes request to get a new robots txt file, returns the file pointer
int Spider::getRobots ( ParsedUrl url )
	{


	string pathToDiskRobots =
			util::GetCurrentWorkingDir( ) + "/robots/" + string( url.Host, strlen( url.Host ) ) + ".txt";
	string pathToWebRobots = "https://" + string( url.Host, strlen( url.Host ) ) + "/robots.txt";
	//string(url.Service, strlen(url.Service))+
	SocketReader *reader = new SocketReader( pathToWebRobots );
	reader->fillBuffer( );

	if ( reader->buffer != NULL )
		{
		int fd = util::writeToNewFileToLocation( reader->buffer, pathToDiskRobots );
		if ( fd == -1 )
			cerr << "Error getting Robots.txt file " << endl;

		return fd;
		}

	cerr << "issue filling buffer from robots.txt" << endl;
	return -1;

	}
*/

//request function that handles sending over get request via socket or trying to open file

//Error handling




