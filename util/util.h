//
// Created by Jake Close on 2/6/18.
//

#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


size_t FileSize( int f )
{
    struct stat fileInfo;
    fstat( f, &fileInfo );
    return fileInfo.st_size;
}



/*
 * Takes filename as input, maps file into character pointer
 * If cannot open file, returns a nullptr
 *
 *
 */

char * getFileMap( string fileName )
{
    int f = open( fileName.c_str() , O_RDONLY );
    if ( f != -1 )
        {
        size_t fileSize = FileSize(f);
        char *map = (char *) mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, f, 0);
            if ( map != MAP_FAILED ){
                return map;
            }
        }
    return nullptr;
}
/*
 * Takes integer file descriptor, returns char* map of file
 *
 */

char * getFileMap( int fileDescriptor )
{
    if ( fileDescriptor != -1 )
    {
        size_t fileSize = FileSize(fileDescriptor);
        char *map = (char *) mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fileDescriptor, 0);
        if ( map != MAP_FAILED ){
            return map;
        }
    }
    return nullptr;
}


/*
 *
 * Takes a point to start of a file and string of a location on disk
 * writes filemap to disk at location, and returns the file descriptor to the new file
 */


int writeToNewFileToLocation( char * fileContents , string locationOnDisk)
{
    int fileSize = strlen( fileContents );

    int fd = creat( locationOnDisk.c_str() , S_IRWXU );
    ssize_t bytes_written = 0;
    if( fd != -1 )
        bytes_written = write( fd, fileContents, fileSize );
    else
        cout << "ERROR CREATING FILE\n";

    if( bytes_written != fileSize )
        cout << "ERROR: Only " << bytes_written << " bytes written\n";


    return fd;

}