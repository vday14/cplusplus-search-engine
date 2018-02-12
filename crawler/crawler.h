#pragma once

#include<vector>
#include "spider.h"
#include<string>
#include "../shared/ProducerConsumerQueue.h"
//#include "CrawlerStatistics.h"
/*
 *
 */
using namespace std;

class Crawler
	{

public:
	Crawler( string mode_in, ProducerConsumerQueue < string > *url_q_in )
			: mode( mode_in ), urlFrontier( url_q_in )
		{ };

	//spawns a number of works
	void SpawnSpiders( size_t num_spiders );

	//Creates a housekeeping thread
	void houseKeeper();

	void WaitOnAllSpiders();

private:
	vector < Spider * > spiders;
	ProducerConsumerQueue < string > *urlFrontier;
	//CrawlerStatistics housekeeper;
	string mode;

	};


//spiders : threads doing work of fetching urls
//houseKeeper : This thread is generally quiescent except that it wakes up once every few seconds to log crawl progress statistics
// (URLs crawled, frontier size, etc.), decide whether to terminate the crawl, or (once every few hours of crawling) checkpoint the crawl. In checkpointing, a snapshot of the crawler's state (say, the URL frontier) is committed to disk. In the event of a catastrophic crawler failure, the crawl is restarted from the most recent checkpoint.