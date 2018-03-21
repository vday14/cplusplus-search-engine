//
// Created by Jake Close on 3/18/18.
//

#include "SharedHashMap.h"

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <cassert>

using namespace std;

pthread_mutex_t cout_lock = PTHREAD_MUTEX_INITIALIZER;

int main ( int argc, const char *argv[] )
	{
	SharedHashMap< int, int > *sharedTable = new(SharedHashMap< int, int >);

	pthread_t t;

	sharedTable->Insert( 5, 4 );
	int v = sharedTable->Find( 5 );
	assert( v == 4 );


	delete sharedTable;

	return 0;
	}
