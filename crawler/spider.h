
#pragma once


#include<string>
#include <pthread.h>
#include "crawler.h"
#include <fstream>
using namespace std;
Crawler c( " m ") ;

class Spider : public Crawler {

private:
    int locationOnDisk;
    pthread_t runningThread;

public:


    //Takes a url off of the url frontier
    string getUrl( )
    {
        return urlFrontier->Pop();

    }

    void* run(void * arg){


        while( true )
            {
                string currentUrl  = getUrl();
                if ( request( currentUrl ) )
                    {
                        // markURLSeen( currentUrl );
                        // writeHTMLtoDisk( );
                        // addHTMLToQueue( );

                    }
                else
                {
                    cerr << "Error connecting" ;
                }



            }


    }

    //Makes request to given url
    // if successful, writes file to disk, stores location to memeber value
    // else return false and error information, retry if necessary
    bool request( string url )
        {
        if ( mode == 'local' )
            {
                ifstream inFile;
                string in;
                inFile.open(url);
                if ( !inFile ) {
                    cout << "Unable to open file";
                    exit(1); // terminate with error
                }

                while (inFile >> in) {
                   cout << in << endl;
                }

                inFile.close();


            }

        }


    //Where to write to disk? What type of data are we reading in?
    void writeHTMLtoDisk( );

    //Adds location
    void addHTMLToQueue();


    void markURLSeen( string URL );


    Spider( )
        {
            cout << "SPAWNING NEW SPIDER " << endl;
            pthread_create(&runningThread, NULL, run, nullptr);

        };






};