//
// Created by Jake Close on 2/8/18.
//

#pragma once

#include "url.h"
#include <string>
#include <vector>
#include <pthread.h>

using namespace std;

namespace filepath
	{
		const char* DOC_MAP = "/docMap.txt";
	}

	pthread_mutex_t docMap_mutex = PTHREAD_MUTEX_INITIALIZER;

class Document
	{
	private:
		ParsedUrl url;
		long docID;
		bool lastCrawlStatus;
		int lastCrawlDate;
		int lastCrawlPageCount;

		//add more info fields here

	public:
		Document(string url_in) : url(ParsedUrl(url_in)) {}

		int WriteToDocMap()
			{

			pthread_mutex_lock(&docMap_mutex);

			//for now just write url

			string loc = util::GetCurrentWorkingDir() + filepath::DOC_MAP;
			int file = util::getFileDescriptor(loc.c_str(), "W");
			off_t resultPosition = 0;

			//check if its available
			if (file == -1) {
				cerr << "Error opening docMap" << endl;
				close( file );
				pthread_mutex_unlock(&docMap_mutex);
				return -1;
			} else
				{
				//get the current size of the docMap
				size_t seekPosition = util::FileSize(file);
				//seek to the end of the file
				resultPosition = lseek(file, seekPosition, SEEK_SET);

				if (resultPosition == -1) {
					cerr << "Could not seek to " << seekPosition <<
						 ", error = " << errno;
					close( file );
					pthread_mutex_unlock(&docMap_mutex);
					return -1;
				}
				cout << "Current docMap position on disk" << endl;
				cout << resultPosition << endl;

				size_t success = write(file, "Hello World!\n", 14);
				if (success == -1)
					{
					cerr << "Error writing document object to document map" << endl;
						close( file );
						pthread_mutex_unlock(&docMap_mutex);
					return -1;
					}
				}
			close( file );
			pthread_mutex_unlock(&docMap_mutex);
			return resultPosition;
			}



		static void PrintDocMap(string url, int location)
			{
			pthread_mutex_lock(&docMap_mutex);

			std::cout << url << " is " << location;

			string loc = util::GetCurrentWorkingDir() + filepath::DOC_MAP;
			int file = util::getFileDescriptor( loc.c_str(), "R" );


			//check if its available
			if ( file )
			{
				off_t resultPosition = lseek( file, (size_t)location, SEEK_SET );
				int bytes = 14;
				if ( bytes > 0 )
				{
					char *buffer = new char[bytes];
					ssize_t bytesRead;
					if ( bytesRead = read( file, buffer, bytes ))
						write( 1, buffer, bytesRead );
					else
					{
						cerr << "Could not read " << bytes << " bytes at position " <<
							 resultPosition << ", error = " << errno;
						pthread_mutex_unlock(&docMap_mutex);
						return;
					}
				}

			}
			pthread_mutex_unlock(&docMap_mutex);
			return;
			}
	};