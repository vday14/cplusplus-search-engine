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

	if( Blacklist.find(  url.getCompleteUrl(  )  ) != Blacklist.end( ) )
		return false;

	if( RestrictedHosts.find( url.getHost(  )) == RestrictedHosts.end( ) )
		return false;

	//if( RestrictedHosts[ url.getHost ( ) ] > 500 )
	//	return false;



	//Looks to see if the complete url already exists, if so return
	if ( this->duplicateUrlMap->find( url.getCompleteUrl( )) != this->duplicateUrlMap->end( ))
		{
		//update the anchor text
		if ( !url.getAnchorText( ).empty( ) || url.getAnchorText( ) != "")
			{
			pthread_mutex_lock( &m );
			(*duplicateUrlMap)[ url.getCompleteUrl( ) ][ url.getAnchorText( ) ]++;
			pthread_mutex_unlock( &m );
			}
		//add the new
		return false;
		}


	else
		{
		time_t now;
		time( &now );
		double difference = 0;
		//Has the domain been seen?
		if ( this->domainMap->find( url.getHost( )) != this->domainMap->end( ))
			{
			//get the last time it was seen and find the time difference
			time_t lastSeen = this->domainMap->at( url.getHost( ));
			difference = difftime( now, lastSeen );
			if ( difference == 0 )
				difference = .01;
			else
				difference = difference / 100;
			//url.updateScore( difference );

			pthread_mutex_lock( &m );
			(*domainMap)[ url.getHost( ) ] = now;
			pthread_mutex_unlock( &m );

			}
		else
			{
			pthread_mutex_lock( &m );
			this->domainMap->insert( std::make_pair( url.getHost( ), now ));   //otherwise add to the map the current time
			pthread_mutex_unlock( &m );


			}


		//add url to the duplicate url map
		pthread_mutex_lock( &m );
		(*duplicateUrlMap)[ url.getCompleteUrl( ) ][ url.getAnchorText( ) ] = 1;
		pthread_mutex_unlock( &m );

		pthread_mutex_lock( &m );
		RestrictedHosts[ url.getHost ( ) ]++;
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

			queue.push( url );

			if ( queue.size( ) == 1 )
				{
				pthread_cond_broadcast( &consumer_cv );
				}

			pthread_mutex_unlock( &m );
			}
		}
	}

bool UrlFrontier::try_pop( ParsedUrl& result )
	{

	gettimeofday(&now, NULL);
	timeToWait.tv_sec = now.tv_sec + 5;
	timeToWait.tv_nsec = (now.tv_usec+1000UL*100)*1000UL;

	int retval;

	pthread_mutex_lock(&m);

	while(queue.empty()){
		retval = pthread_cond_timedwait(&consumer_cv, &m, &timeToWait);
		if(retval != 0){
			fprintf(stderr, "pthread_cond_timedwait %s\n",
					strerror(retval));
			pthread_mutex_unlock(&m);
			return false;
		}
	}

	result = std::move(queue.top());
	queue.pop();

	pthread_mutex_unlock(&m);
	return true;
	}


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


	while ( !queue.empty( ))
		{
		ParsedUrl url = queue.top( );
		queue.pop( );
		string url_disk = url.getCompleteUrl() + "\n";
		write( file, url_disk.c_str( ), strlen( url_disk.c_str( )  ));

		}
	pthread_mutex_unlock( &m );

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
			RestrictedHosts[ url.getHost( ) ] = 0;
			toRestrict = "";
			}
		else
			toRestrict.push_back( *hosts );

		++hosts;
		}
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
