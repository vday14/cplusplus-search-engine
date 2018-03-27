//
// Created by Jake Close on 3/26/18.
//

#include "../shared/ProducerConsumerQueue.h"
//#include "../shared/SharedHashMap.h"
#include "../shared/url.h"
#include <time.h>
#include <unordered_map>
using namespace std;


class ComparisonClass {
public:
	bool operator() (ParsedUrl *lhs , ParsedUrl *rhs) {
		//comparison code here
		return lhs->getScore() < rhs->getScore();
		}
	};



class UrlFrontier
	{

public:
	void Push ( ParsedUrl * url );
	void checkUrl(ParsedUrl *  url);

	ParsedUrl *	Pop ( );
	size_t Size();
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t consumer_cv = PTHREAD_COND_INITIALIZER;
	std::priority_queue<ParsedUrl *, std::vector<ParsedUrl*>, ComparisonClass> queue;




private:
	unordered_map< string , bool > *duplicateUrlMap = new unordered_map< string, bool >( );
	unordered_map< string , time_t > *domainMap = new unordered_map< string, time_t >( );

	};



