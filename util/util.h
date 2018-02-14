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
#include <string>

#define PATH_TO_BLACKLIST = '/bin/blacklist.txt'
#define PATH_TO_VISITED_URL = 'bin/urls.txt'
#define PATH_TO_HTML_DIR = 'bin/html/'
#define PATH_TO_INDEX = 'bin/index/wordIDX'
#define PATH_TO_DOC_INDEX = 'bin/index/docIDX'


using namespace std;

namespace util
	{
		size_t FileSize(int f);


/*
 * Takes filename as input, maps file into character pointer
 * If cannot open file, returns a nullptr
 */
		int getFileDescriptor(string fileName, string type);


		char *getFileMap(string fileName);


/*
 * Takes integer file descriptor, returns char* map of file
 */
		char *getFileMap(int fileDescriptor);


/*
 * Takes a point to start of a file and string of a location on disk
 * writes filemap to disk at location, and returns the file descriptor to the new file
 */
		int writeToNewFileToLocation(char *fileContents, string locationOnDisk);

		string GetCurrentWorkingDir(void);
	}