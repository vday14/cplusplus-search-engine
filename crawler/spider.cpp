//
// Created by Ben Bergkamp on 1/31/18.
//

#include "spider.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../util/util.h"




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
        char * fileMap;
        if ( request( currentUrl , fileMap ) )
            {
            // markURLSeen( currentUrl );
                string HARDCODEDLOCATION = "../crawlerOutput/" + currentUrl;
            int fd = writeFileToDisk(fileMap , HARDCODEDLOCATION );
                //Write to disk successful
                if( fd !=-1 )
                {
                    addFDToQueue( fd  );

                }
                cond = false;
            }
        else
            {
            cerr << "Error connecting" ;
            }
        }
    }


bool Spider::request( string url , char* fileMap)
    {

    if ( this->mode == "local" )
        {
            fileMap =  getFileMap( url );
            if (fileMap != nullptr )
                return true;
        }
    return false;
    }

int Spider::writeFileToDisk( char * fileContents , string locationOnDisk)
{

    return writeToNewFileToLocation( fileContents, locationOnDisk );

}


void Spider::addFDToQueue( int fileDescriptor )
{
    fileQueue->Push( fileDescriptor );

}