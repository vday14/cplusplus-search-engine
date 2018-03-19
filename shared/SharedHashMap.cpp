//
// Created by Jake Close on 3/18/18.
//

#include "SharedHashMap.h"



template <class T>
void SharedHashMap::Insert( T key, T value )
	{
	pthread_mutex_lock(&m);

	map.insert(key, value);

	pthread_mutex_unlock(&m);
	}

template <class T>
T void SharedHashMap::Find( T key)

	{
	pthread_mutex_lock(&m);

	T value = map.find(key);


	pthread_mutex_unlock(&m);

	return value;
	}

template <class T>
size_t ProducerConsumerQueue<T>::Size()
	{
	pthread_mutex_lock(&m);
	size_t size = map.size();
	pthread_mutex_unlock(&m);
	return size;
	}