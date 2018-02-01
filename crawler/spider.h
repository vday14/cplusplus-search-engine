#pragma once


#include<string>
#include <pthread.h>
#include <fstream>
#include "../ProducerConsumerQueue.h"
#include "../ThreadClass.h"
#include<iostream>

using namespace std;

class Spider : public ThreadClass{

public:

    Spider(string mode_in, ProducerConsumerQueue<string>* url_q_in , ProducerConsumerQueue<string>* html_q_in)
            : mode( mode_in ), urlFrontier(url_q_in) , fileQueue(html_q_in) {};


    //Takes a url off of the url frontier
    string getUrl();

    virtual void FuncToRun();

    //Makes request to given url
    // if successful, writes file to disk, stores location to memeber value
    // else return false and error information, retry if necessary
    bool request( string url );

    //Where to write to disk? What type of data are we reading in?
    void writeHTMLtoDisk( );

    //Adds location
    void addHTMLToQueue();


    void markURLSeen( string URL );

private:

    int locationOnDisk;
    ProducerConsumerQueue<string> *urlFrontier;
    ProducerConsumerQueue<string> *fileQueue;
    string mode;

};