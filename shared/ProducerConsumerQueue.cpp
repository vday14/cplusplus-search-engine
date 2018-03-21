//
// Created by Ben Bergkamp on 1/25/18.
//

#include "ProducerConsumerQueue.h"

template< class T >
void ProducerConsumerQueue< T >::Push ( T obj )
	{
	pthread_mutex_lock( &m );

	queue.push( obj );

	if ( queue.size( ) == 1 )
		{
		pthread_cond_broadcast( &consumer_cv );
		}

	pthread_mutex_unlock( &m );
	}

template< class T >
T ProducerConsumerQueue< T >::Pop ( )
	{
	pthread_mutex_lock( &m );

	while ( queue.empty( ) == true )
		{
		pthread_cond_wait( &consumer_cv, &m );
		}

	T front = queue.front( );
	queue.pop( );

	pthread_mutex_unlock( &m );

	return front;
	}

template< class T >
size_t ProducerConsumerQueue< T >::Size ( )
	{
	pthread_mutex_lock( &m );
	size_t size = queue.size( );
	pthread_mutex_unlock( &m );
	return size;
	}