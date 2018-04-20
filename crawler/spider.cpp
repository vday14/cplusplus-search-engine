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


using DocIndex = const unordered_map < string, vector < unsigned long > >;

// FIND A BETTER PLACE TO PUT THIS FUNCTION
/*
 *
 * Factory function to create the proper stream reader
 *
 */
StreamReader *SR_factory( ParsedUrl *url, string mode )
	{
	string localFile;

	StreamReader *newReader = nullptr;
	if ( mode == "local" )
		{
		newReader = new LocalReader( url->getCompleteUrl( ));
		}
	else if ( mode == "web" )
		{
		if ( url->getService( ) == "http" )
			{
			newReader = new HttpReader( url );
			}
		else if ( url->getService( ) == "https" )
			{
			newReader = new HttpsReader( url );
			}
		else
			{
			cerr << "Error reading service type\n";
			cerr << "Service Type: " << url->getService( ) << "\n";
			}
		}

	return newReader;
	}

void printDocIndex( DocIndex *dict )
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

size_t Spider::hash( const char *s )
	{
	// http://www.cse.yorku.ca/~oz/hash.html
	size_t h = 5381;
	int c;
	while ((c = *s++))
		h = ((h << 5) + h) + c;
	return h;
	}

/*
 *
 * Gets a parsed url from the url frontier
 *
 */

ParsedUrl Spider::getUrl()
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

void Spider::run()
	{
	std::cout << "Spider is crawling" << endl;
	int cond = 0;
	ParsedUrl currentUrl;


	while ( *alive )
		{

		bool not_empty = urlFrontier->try_pop( currentUrl );

		if ( not_empty )
			{

			StreamReader *reader = SR_factory( &currentUrl, this->mode );
			if ( reader )
				{
				bool success = reader->request( );
				if ( success )
					{
					DocIndex *dict = parser.execute( reader );
					IndexerQueue->Push( dict );

					cond++;
					}

				}
			reader->closeReader( );
			reader = 0;
			delete reader;


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




//request function that handles sending over get request via socket or trying to open file

//Error handling




