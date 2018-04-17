//
// Created by Ben Bergkamp on 1/25/18.
//

#include "ProducerConsumerQueue.h"
#include "ParsedUrl.h"
using namespace std;
template< class T >
void ProducerConsumerQueue< T >::Push ( T obj )
	{
	pthread_mutex_lock( &m );

	queue_.push( obj );

	if ( queue_.size( ) == 1 )
		{
		pthread_cond_broadcast( &consumer_cv );
		}

	pthread_mutex_unlock( &m );
	}

template< class T >
bool ProducerConsumerQueue< T >::try_pop(T &result)
	{

	gettimeofday(&now, NULL);
	timeToWait.tv_sec = now.tv_sec + 5;
	timeToWait.tv_nsec = (now.tv_usec+1000UL*100)*1000UL;


	int retval;

	pthread_mutex_lock(&m);

	while(queue_.empty()){
		retval = pthread_cond_timedwait(&consumer_cv, &m, &timeToWait);
		if(retval != 0){
			//fprintf(stderr, "pthread_cond_timedwait %s\n",
			//		strerror(retval));
			cerr << "error popping" << endl;
			pthread_mutex_unlock(&m);
			return false;
		}
	}

	result = std::move(queue_.front());
	queue_.pop();

	pthread_mutex_unlock(&m);
	return true;
	}

template< class T >
T ProducerConsumerQueue< T >::Pop ( )
	{
	pthread_mutex_lock( &m );

	while ( queue_.empty( ) == true )
		{
		pthread_cond_wait( &consumer_cv, &m );
		}

	T front = queue_.front( );
	queue_.pop( );

	pthread_mutex_unlock( &m );

	return front;
	}

template< class T >
size_t ProducerConsumerQueue< T >::Size ( )
	{
	pthread_mutex_lock( &m );
	size_t size = queue_.size( );
	pthread_mutex_unlock( &m );
	return size;
	}
