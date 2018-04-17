//
// Created by Ben Bergkamp on 1/25/18.
//

#pragma once

#include <pthread.h>
#include <chrono>
#include <sys/time.h>
#include <iostream>
#include <queue>


//for now use STL queue, create better one later


template< class T >
class ProducerConsumerQueue
	{

public:

	ProducerConsumerQueue ( )
		{ }


	virtual void Push ( T obj );
	virtual bool try_pop(T& result);
	virtual T Pop ( );
	virtual size_t Size ( );

	//Right now these pass objects by value but
	// probably should pass pointers in future

protected:
	std::queue< T > queue_;
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t consumer_cv = PTHREAD_COND_INITIALIZER;
	struct timespec timeToWait;
	struct timeval now;
	};

//Necessary because this class is templated
#include"ProducerConsumerQueue.cpp"

#endif //EECS398_SEARCH_PRODUCERCONSUMERQUEUE_H
