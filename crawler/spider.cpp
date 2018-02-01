//
// Created by Ben Bergkamp on 1/31/18.
//

#include "spider.h"

string Spider::getUrl()
{
    return urlFrontier->Pop();
}

void Spider::FuncToRun()
    {

    std::cout << "Spider is crawling" << endl;
    bool cond = true;

    while( cond )
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


bool Spider::request( string url )
    {
    if ( this->mode == "local" )
        {
        ifstream inFile;
        string in;
        inFile.open(url);
        if ( !inFile )
            {
            cout << "Unable to open file";
            exit(1); // terminate with error
            }

        while (inFile >> in)
            {
            cout << in << endl;
            }

        inFile.close();
        return true;

        }
    return false;
    }