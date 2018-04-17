//
// Created by Ben Bergkamp on 4/16/18.
//

#include "ThreadClass.h"

ThreadClass::ThreadClass ( )
	{ };

ThreadClass::~ThreadClass ( )
	{ };

bool ThreadClass::StartThread ( )
	{
	return ( pthread_create( &thread, NULL, StaticFuncToRun, this ) == 0 );
	}

void ThreadClass::WaitForFinish()
	{
	pthread_join( thread, NULL );
	}

void ThreadClass::Die()
	{
	pthread_cancel( thread );
	}

void* ThreadClass::StaticFuncToRun(void *This)
	{
	( ( ThreadClass * ) This )->run( );
	return nullptr;
	}