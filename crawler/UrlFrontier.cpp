//
// Created by Jake Close on 3/26/18.
//

#include "UrlFrontier.h"
#include "../util/Tokenizer.h"


//checks the current url to see if should be crawled
//first, checks if the exact url has already seen
//if so , doesnt add to the frontier
//then checks if the host has been seen
//if it has, it checks how long ago it was
// gets that difference and then updates the time score so it
// goes back in the queue
// then adds both to the url map and the host map


bool UrlFrontier::checkUrl( ParsedUrl url )
	{
	/*
	if( Blacklist.find(  url.getCompleteUrl(  )  ) != Blacklist.end( ) )
		return false;
	*/
	if( RestrictedHosts.find( url.getHost(  )) == RestrictedHosts.end( ) )
		return false;

	//Looks to see if the complete url already exists, if so return
	if ( this->duplicateUrlMap->find( url.getCompleteUrl( )) != this->duplicateUrlMap->end( ))
		{
		return false;
		/*
		//update the anchor text
		if ( !url.getAnchorText( ).empty( ) || url.getAnchorText( ) != "")
			{
			pthread_mutex_lock( &m );
			(*duplicateUrlMap)[ url.getCompleteUrl( ) ][ url.getAnchorText( ) ]++;
			pthread_mutex_unlock( &m );
			}
		 */
		//add the new

		}

	else
		{
		pthread_mutex_lock( &m );
		(*duplicateUrlMap)[ url.getCompleteUrl( ) ][ url.getAnchorText( ) ] = 1;
		pthread_mutex_unlock( &m );
		return true;
		}
	}


void UrlFrontier::Push( ParsedUrl url )
	{
	//if the url has been seen? if so, dont add it
	if ( url.isValid )
		{

		if ( checkUrl( url ))
			{

			pthread_mutex_lock( &m );

			RestrictedHosts[ url.getHost ( ) ]->push( url );
			//cout << "Pushing " << url.getHost( ) << endl;
			//cout << RestrictedHosts[ url.getHost ( ) ]->size( ) << endl;
			//if ( RestrictedHosts[ url.getHost ( ) ]->size( ) == 1 )
			//	{
			//	pthread_cond_broadcast( &consumer_cv );
			//	}

			pthread_mutex_unlock( &m );
			}
		}
	}


bool UrlFrontier::try_pop( ParsedUrl& result )
	{

	gettimeofday(&now, NULL);
	timeToWait.tv_sec = now.tv_sec + 1;
	timeToWait.tv_nsec = (now.tv_usec+1000UL*100)*1000UL;

	int retval;
	pthread_mutex_lock(&m);

	string currentHost = RoundRobinHosts[ (GlobalCounter++) % numHost];
	//priority_queue<ParsedUrl , std::vector<ParsedUrl>, ComparisonClass>* currentQ = ;

	//cout << "Popping Current Host  " << currentHost << ".i Current Number of urls in queue " << currentQ->size( ) << endl;
	while( RestrictedHosts[ currentHost ]->empty( ) ) {
		retval = pthread_cond_timedwait(&consumer_cv, &m, &timeToWait);
		if(retval != 0){
			//fprintf(stderr, "pthread_cond_timedwait %s\n",
			//		strerror(retval));
			cerr << "Host queue is empty: " << currentHost  << endl;
			pthread_mutex_unlock(&m);
			return false;
		}
	}

	result = std::move(RestrictedHosts[ currentHost ]->top());
	//cout << "Popping " << result.getCompleteUrl( ) << endl;
	//cout << result.getCompleteUrl( ) << endl;
	RestrictedHosts[ currentHost ]->pop();

	pthread_mutex_unlock(&m);
	return true;
	}

/*
ParsedUrl UrlFrontier::Pop()
	{

	pthread_mutex_lock( &m );

	while ( queue.empty( ) == true )
		{
		pthread_cond_wait( &consumer_cv, &m );
		}

	ParsedUrl front = queue.top( );
	queue.pop( );

	pthread_mutex_unlock( &m );

	return front;

	}

size_t UrlFrontier::Size()
	{
	pthread_mutex_lock( &m );
	size_t size = queue.size( );
	pthread_mutex_unlock( &m );
	return size;
	}
 */

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime()
	{
	time_t now = time( 0 );
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime( &now );
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime( buf, sizeof( buf ), "%Y-%m-%d.%X", &tstruct );

	return buf;
	}


void UrlFrontier::writeDataToDisk()
	{


	cout << "Writing queue to disk" << endl;

	string fileName = util::GetCurrentWorkingDir( ) + "/build/savedQueue.txt";

	if ( remove( fileName.c_str( )) != 0 )
		perror( "Error deleting file" );
	else
		puts( "File successfully deleted" );
	int file = open( fileName.c_str( ), O_CREAT | O_WRONLY, S_IRWXU );

	pthread_mutex_lock( &m );

	for(auto host : RoundRobinHosts )
		{
		priority_queue<ParsedUrl , std::vector<ParsedUrl>, ComparisonClass>* currentQ = RestrictedHosts[ host ];

		while ( !currentQ->empty( ))
			{
			ParsedUrl url = currentQ->top( );
			currentQ->pop( );
			string url_disk = url.getCompleteUrl() + "\n";
			write( file, url_disk.c_str( ), strlen( url_disk.c_str( )  ));

			}
		pthread_mutex_unlock( &m );


		}
	close( file );



	return;
	}


void UrlFrontier::readDataFromDisk( )
	{

	cout << "Read queue from disk" << endl;

	string fileName = "/build/savedQueue.txt";

	char *files = util::getFileMap( fileName );

	string testFile;
	while ( *files )
		{
		if ( *files == '\n' )
			{

			ParsedUrl url(testFile);
			cout << "Pushing: " << testFile << " to queue\n";
			Push( url );
			testFile = "";
			}
		else
			testFile.push_back( *files );

		++files;
		}
	}


void UrlFrontier::readBlackList()
	{

	string blackListFile = "/crawler/blacklist.txt";
	char *hosts = util::getFileMap( blackListFile );

	string toBlackList;
	while ( *hosts )
		{
		if ( *hosts == '\n' )
			{

			Blacklist.insert(toBlackList);
			toBlackList = "";
			}
		else
			toBlackList.push_back( *hosts );

		++hosts;
		}
	}

void UrlFrontier::readHosts()
	{

	string hostsFile = "/crawler/seeds.txt";
	char *hosts = util::getFileMap( hostsFile );

	string toRestrict;
	while ( *hosts )
		{
		if ( *hosts == '\n' )
			{
			ParsedUrl url  = ParsedUrl( toRestrict );
			if( RestrictedHosts.find( url.getHost() ) == RestrictedHosts.end( ) )
				{
				RoundRobinHosts.push_back( url.getHost( ));
				RestrictedHosts[ url.getHost( ) ] = new priority_queue < ParsedUrl, std::vector < ParsedUrl >, ComparisonClass >;
				}
				//RestrictedHosts[ url.getHost( ) ]->push( url );
			toRestrict = "";
			}
		else
			toRestrict.push_back( *hosts );

		++hosts;
		}

	numHost = RoundRobinHosts.size( );
	}





void UrlFrontier::printAnchorTable()
	{
	Tokenizer tokenizer;
	unsigned long offset = 0;

	for ( auto const &ent1 : *duplicateUrlMap )
		{
		auto const &outer_key = ent1.first;
		auto const &inner_map = ent1.second;
		for ( auto const &ent2 : inner_map )
			{

				auto const &inner_key = ent2.first;
				auto const &inner_value = ent2.second;
			if( ! inner_key.empty() )
				{
				cout << "url: " << outer_key << endl;
				cout << "anchor text : " << inner_key << endl;
				cout << "count " << inner_value << endl;

				}
			else
				cout << "url: " << outer_key << " has no anchor text " << endl;

			}

		}

	}
