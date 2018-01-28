#pragma once

#include<vector>
#include "spider.h"
#include<string>
/*
 *
 */
using namespace std;

class Crawler {


    vector< *Spider> spiders;



public:
    string mode;

    ProducerConsumerQueue *urlFrontier;
    ProducerConsumerQueue *fileQueue;


    //spawns a number of works
    void spawnSpiders(size_t numberOfSpiders)
        {
        for( size_t i = 0 ; i < numberOfSpiders;  i++)
            {
                Spider *temp = new Spider( this.mode );
                this->spiders.push_back(temp);
            }


        }

    //Creates a housekeeping thread
    void houseKeeper();



    Crawler(string mode_in, ProducerConsumerQueue* url_q_in , ProducerConsumerQueue* html_q_in) : mode( mode_in ), urlFrontier(url_q_in) , fileQueue(html_q_in);








};


//spiders : threads doing work of fetching urls
//houseKeeper : This thread is generally quiescent except that it wakes up once every few seconds to log crawl progress statistics
// (URLs crawled, frontier size, etc.), decide whether to terminate the crawl, or (once every few hours of crawling) checkpoint the crawl. In checkpointing, a snapshot of the crawler's state (say, the URL frontier) is committed to disk. In the event of a catastrophic crawler failure, the crawl is restarted from the most recent checkpoint.