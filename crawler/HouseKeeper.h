//
// Created by Ben Bergkamp on 2/1/18.
//

#pragma once

#include "../shared/ThreadClass.h"
#include<string>
#include <pthread.h>
#include <iostream>
#include "crawler.h"
class HouseKeeper : public ThreadClass
	{

public:
	HouseKeeper ( Crawler * crawler_in ) : crawler(crawler_in)
		{ };

	 void run( );

private:
	//members
	Crawler* crawler;

	};


