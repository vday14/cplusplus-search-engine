//
// Created by Ben Bergkamp on 1/31/18.
//

#pragma once

#include <pthread.h>

class ThreadClass
	{
public:
	ThreadClass ( );

	virtual ~ThreadClass ( );

	//Returns true if thread was created successfully
	bool StartThread ( );

	//Blocks until thread finishes
	void WaitForFinish ( );

	void Die ( );

protected:
	//IMPLEMENT THIS METHOD IN YOUR SUB CLASS WITH CODE YOU WANT YOUR THREAD TO RUN
	virtual void run ( ) = 0;

private:
	static void *StaticFuncToRun ( void *This );

	pthread_t thread;
	};

