#pragma once

#include<vector>
#include "spider.h"
#include<string>
#include "../shared/ProducerConsumerQueue.h"
#include <unordered_map>
#include "UrlFrontier.h"

//#include "CrawlerStatistics.h"
/*
 *
 */
using namespace std;
using DocIndex = const unordered_map< string, vector< unsigned long > >;

class Crawler
	{

public:
	Crawler ( string mode_in,
				 UrlFrontier  *url_q_in,
				 ProducerConsumerQueue< DocIndex * > *doc_index_queue_in )
			: IndexerQueue( doc_index_queue_in ),
			  mode( mode_in ),
			  urlFrontier( url_q_in )
		{ };

	//spawns a number of works
	void SpawnSpiders ( size_t num_spiders, atomic_bool* alive );

	//Creates a housekeeping thread
	void houseKeeper ( );

	void KillAllSpiders ( );

	void WaitOnAllSpiders ( );
	UrlFrontier  *urlFrontier;


private:
	vector< Spider * > spiders;
	//UrlFrontier  *urlFrontier;
	ProducerConsumerQueue< DocIndex * > *IndexerQueue;
	//CrawlerStatistics housekeeper;
	string mode;

	};


//spiders : threads doing work of fetching urls
//houseKeeper : This thread is generally quiescent except that it wakes up once every few seconds to log crawl progress statistics
// (URLs crawled, frontier size, etc.), decide whether to terminate the crawl, or (once every few hours of crawling) checkpoint the crawl. In checkpointing, a snapshot of the crawler's state (say, the URL frontier) is committed to disk. In the event of a catastrophic crawler failure, the crawl is restarted from the most recent checkpoint.