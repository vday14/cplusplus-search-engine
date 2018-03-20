//
// Created by Jake Close on 3/18/18.
//

#ifndef EECS398_SEARCH_SHAREDHASHMAP_H
#define EECS398_SEARCH_SHAREDHASHMAP_H
#include <unordered_map>
#include <pthread.h>


template <class T> class SharedHashMap {
	private:
		std::unordered_map<T, T> map;
		pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
		pthread_cond_t consumer_cv = PTHREAD_COND_INITIALIZER;

	public:

		SharedHashMap() {}


		void Insert(T key, T value);
		T Find(T Key);
		size_t Size();


	};

//Necessary because this class is templated
#include"SharedHashMap.cpp"

#endif
