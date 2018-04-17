//
// Created by Jake Close on 3/26/18.
//
#pragma  once
#include "../shared/ProducerConsumerQueue.h"
//#include "../shared/SharedHashMap.h"
#include <algorithm>
#include "../shared/ParsedUrl.h"
#include <time.h>
#include <unordered_map>
#include <set>
#include <iostream>
#include <atomic>
using namespace std;


typedef  unordered_map<string, int> anchorToCountMap ;
typedef   unordered_map<string , anchorToCountMap>  urlMap;

class ComparisonClass {
public:
	bool operator() (ParsedUrl lhs , ParsedUrl rhs) {
		//comparison code here
		return lhs.getScore() < rhs.getScore();
		}
	};

class UrlFrontier : public ProducerConsumerQueue<ParsedUrl>
	{

	public:
		UrlFrontier( ) {
				readBlackList();
				readHosts( );
		};

		void Push ( ParsedUrl url ) override;
		bool try_pop( ParsedUrl& result ) override;
		//ParsedUrl Pop ( ) override ;
		//size_t Size() override;

		bool checkUrl(ParsedUrl url);
		void readBlackList( );
		void readHosts( );

		void printAnchorTable( );
		set < string > Blacklist ;
		unordered_map<string, priority_queue<ParsedUrl , std::vector<ParsedUrl>, ComparisonClass> *> RestrictedHosts;
		vector<string> RoundRobinHosts;
		size_t numHost;
		//atomic_ulong GlobalCounter;
		std::atomic<u_long> GlobalCounter;
		//std::priority_queue<ParsedUrl , std::vector<ParsedUrl>, ComparisonClass> queue;

		//Writes the duplicate url map and priorty queue from disk
		void writeDataToDisk( );
		//Constructs the priority queue and duplicate map from stored data
		void readDataFromDisk();

		urlMap *duplicateUrlMap =  new urlMap;
	private:
		//urlMap *duplicateUrlMap =  new urlMap;
		//unordered_map< string , time_t > *domainMap = new unordered_map< string, time_t >( );

	};



