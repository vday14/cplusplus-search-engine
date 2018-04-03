//
// Created by nick on 3/16/18.
//

#include <iostream>
#include <set>
#include "../../indexer/DocumentEnding.h"
#include "../ISRWord.h"
#include "../ISREndDoc.h"


using namespace std;

int main ( )
	{
	char* query = "iphone";
	clock_t start = clock();
	vector<ISRWord> queries;
	vector< vector< size_t > > locations;


	ISRWord q1 = ISRWord("%trump");
	ISRWord q2 = ISRWord("%world");
	queries.push_back(q2);
	queries.push_back(q1);


	vector<DocumentEnding> docEnds;


	vector<set<string>> urls;
	set<string> out1;
	set<string> out2;
	urls.push_back(out1 );
	urls.push_back(out2 );

	set<string> or_set;

	vector<size_t> loc1;
	vector<size_t> loc2;
	locations.push_back(loc1);
	locations.push_back(loc2);

	for(int i = 0; i <queries.size() ; i++ )
		{
		while(queries[i].getCurrentLocation() != MAX_Location)  {
			auto url = queries[i].DocumentEnd->getCurrentDoc().url;
			urls[i].insert( url  );
			queries[i].NextDocument();

			}
		}
	clock_t end = clock();





	for(auto output  : urls)
		{
		for(auto urrl : output) {
			cout << urrl << endl;
			}

		}

	cout << "Time to complete query: " << (end - start) / (double) CLOCKS_PER_SEC << endl;
	return 0;
	}