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
			difference =  difftime( now ,lastSeen);
			if(difference == 0)
				difference = 5;
			else
				difference = 1/difference;
			url->updateScore( difference );

			}
		else
			this->domainMap->insert( std::make_pair( url->getHost( ), now ));   //otherwise add to the map the current time


		//add url to the duplicate url map
		this->duplicateUrlMap->insert( std::make_pair( url->getCompleteUrl( ), 1 ));
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
