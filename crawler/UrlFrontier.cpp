//
// Created by Jake Close on 3/26/18.
//

#include "urlFrontier.h"


//checks the current url to see if should be crawled
//first, checks if the exact url has already seen
//if so , doesnt add to the frontier
//then checks if the host has been seen
//if it has, it checks how long ago it was
// gets that difference and then updates the time score so it
// goes back in the queue
// then adds both to the url map and the host map


void UrlFrontier::checkUrl(ParsedUrl* url)
	{

	//Looks to see if the complete url already exists, if so return
	if ( this->duplicateUrlMap->find( url->getCompleteUrl() ) != this->duplicateUrlMap->end( ) )
		return ;

	else
		{
		time_t now;
		time( &now );
		double difference = 0;
		//Has the domain been seen?
		if ( this->domainMap->find( url->getHost( )) != this->domainMap->end( ))
			{
			//get the last time it was seen and find the time difference
			time_t lastSeen = this->domainMap->at( url->getHost( ));
			difference =  difftime( now , lastSeen);
			if(difference == 0)
				difference = 5 ;
			else
				difference =  difference/10;
			url->updateScore( difference );

			}
		else
			this->domainMap->insert( std::make_pair( url->getHost( ), now ));   //otherwise add to the map the current time


		//add url to the duplicate url map
		this->duplicateUrlMap->insert( url->getCompleteUrl( ) );
		return;
		}
	}


void UrlFrontier::Push( ParsedUrl * url )
	{
	//if the url has been seen? if so, dont add it

		checkUrl(url);


		//set the value of the last time the domain was seen to score
		//url.setTime(difference);
		//url.setScore();
		pthread_mutex_lock( &m );

		queue.push( url );

		if ( queue.size( ) == 1 )
			{
			pthread_cond_broadcast( &consumer_cv );
			}

		pthread_mutex_unlock( &m );
	}





ParsedUrl * UrlFrontier::Pop()
	{


	pthread_mutex_lock( &m );

	while ( queue.empty( ) == true )
		{
		pthread_cond_wait( &consumer_cv, &m );
		}

	ParsedUrl * front = queue.top( );
	queue.pop( );

	pthread_mutex_unlock( &m );

	return front;

	}

size_t UrlFrontier::Size ( )
	{
	pthread_mutex_lock( &m );
	size_t size = queue.size( );
	pthread_mutex_unlock( &m );
	return size;
	}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
	}


void UrlFrontier::writeDataToDisk( )
	{


	cout << "Writing queue to disk" << endl;

	string fileName = util::GetCurrentWorkingDir( )  + "/crawler/savedQueue.txt";

	if( remove( fileName.c_str() ) != 0 )
		perror( "Error deleting file" );
	else
		puts( "File successfully deleted" );
		int file = open( fileName.c_str( ), O_CREAT | O_WRONLY, S_IRWXU );

	pthread_mutex_lock( &m );
	string currentTime = currentDateTime();
	write( file, currentTime.c_str( ), strlen( currentTime.c_str( ) ) );

	while(! queue.empty() )
		{
		ParsedUrl * url = queue.top( );
		queue.pop( );
		write( file, url->getCompleteUrl().c_str( ), strlen( url->getCompleteUrl().c_str( ) ) );
		url = 0;
		delete url;
		}
	pthread_mutex_unlock( &m );

	close( file );

	return;
	}
