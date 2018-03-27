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
	bool operator() (ParsedUrl lhs , ParsedUrl rhs) {
		//comparison code here
		return lhs.getScore() < rhs.getScore();
		}
	};



class UrlFrontier : public ProducerConsumerQueue<ParsedUrl>
	{

public:
	void Add ( ParsedUrl url );

	ParsedUrl	Get ( );


private:
	unordered_map< string , bool > *duplicateUrlMap = new unordered_map< string, bool >( );
	unordered_map< string , time_t > *domainMap = new unordered_map< string, time_t >( );
	std::priority_queue<ParsedUrl, std::vector<ParsedUrl>, ComparisonClass> pq;

	};



