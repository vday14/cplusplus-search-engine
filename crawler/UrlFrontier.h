//
// Created by Jake Close on 3/26/18.
//
#pragma  once
#include "../shared/ProducerConsumerQueue.h"
//#include "../shared/SharedHashMap.h"
#include "../shared/url.h"
#include <time.h>
#include <unordered_map>
#include <set>
#include <iostream>
using namespace std;


typedef  unordered_map<string, int> anchorToCountMap ;
typedef   unordered_map<string , anchorToCountMap>  urlMap;

class ComparisonClass {
public:
	bool operator() (ParsedUrl *lhs , ParsedUrl *rhs) {
		//comparison code here
		return lhs->getScore() > rhs->getScore();
		}
	};



class UrlFrontier
	{

	public:
		UrlFrontier( ) {
				readBlackList();
		};

		void Push ( ParsedUrl * url );
		bool checkUrl(ParsedUrl *  url);
		void readBlackList( );
		void printAnchorTable( );
		set < string > Blacklist ;
		ParsedUrl *	Pop ( );
		size_t Size();
		pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
		pthread_cond_t consumer_cv = PTHREAD_COND_INITIALIZER;
		std::priority_queue<ParsedUrl *, std::vector<ParsedUrl*>, ComparisonClass> queue;

		//Writes the duplicate url map and priorty queue from disk
		void writeDataToDisk( );
		//Constructs the priority queue and duplicate map from stored data
		void readDataFromDisk();

		urlMap *duplicateUrlMap =  new urlMap;
	private:
		//urlMap *duplicateUrlMap =  new urlMap;
		unordered_map< string , time_t > *domainMap = new unordered_map< string, time_t >( );

	};



