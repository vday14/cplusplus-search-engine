//
// Created by Ben Bergkamp on 2/1/18.
//

#pragma once

#include "../shared/ThreadClass.h"
#include<string>
#include <pthread.h>
#include <iostream>

class HouseKeeper : public ThreadClass
	{

public:
	HouseKeeper()
		{ };

	virtual void FuncToRun();

private:
	//members

	};


#endif //EECS398_SEARCH_CRAWLERSTATISTICS_H
