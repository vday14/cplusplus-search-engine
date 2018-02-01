//
// Created by Ben Bergkamp on 1/31/18.
//

#include "spider.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
                cond = false;
            }
        else
            {
            cerr << "Error connecting" ;
            }
        }
    }


bool Spider::request( string url )
    {
        char buf[100];

    if ( this->mode == "local" )
    {
        ifstream inFile;
        string in;
        inFile.open(url);
        if ( !inFile )
        {
            cout << "Unable to open file";
            exit(1); // terminate with error////
        }
        int i = 0;
        while (i < 100 && inFile >> buf[i])
        {
                i++;
        }

        inFile.close();
        int file = writeFileToDisk(buf, 100);
        fileQueue->Push(file);
        return true;
    }
    return false;
    }

int Spider::writeFileToDisk( char * fileContents, size_t fileSize)
{
    int fd = creat("/Users/benbergkamp/Desktop/398/eecs398-search/test.txt", S_IRWXU);
    ssize_t bytes_written = 0;
    if(fd != -1)
    {
        bytes_written = write(fd, fileContents, fileSize);
    } else
    {
        cout << "ERROR CREATING FILE\n";
    }
    if(bytes_written != 100)
    {
        cout << "ERROR: Only " << bytes_written << " bytes written\n";
    }

    return fd;

}