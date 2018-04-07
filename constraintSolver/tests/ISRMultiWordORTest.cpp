//
// Created by Jake Close on 4/6/18.
//

//
// Created by nick on 3/16/18.
//

#include <iostream>
#include <set>
#include "../../indexer/DocumentEnding.h"
#include "../ISRWord.h"
#include <iterator>

#include <vector>
#include "../ISREndDoc.h"


using namespace std;

int main ( )
	{
	vector<ISRWord> queries;
	vector< vector< size_t > > locations;

	/*
	static const char TITLE = '#';
	static const char ANCHOR = '@';
	static const char URL = '$';
	static const char BODY = '%';
	static const char HOST = '=';
	*/

	ISRWord q1 = ISRWord("chicken");
	ISRWord q2 = ISRWord("waffle");


	queries.push_back(q2);
	queries.push_back(q1);





	vector<vector<string>> urls;
	vector<string> out1;
	vector<string> out2;
	urls.push_back(out1 );
	urls.push_back(out2 );

	set<string> or_set;

	vector<size_t> loc1;
	vector<size_t> loc2;
	locations.push_back(loc1);
	locations.push_back(loc2);


	vector<double> times;
	for(int i = 0; i <queries.size() ; i++ )
		{
		clock_t start = clock();
		while(queries[i].getCurrentLocation() != MAX_Location)  {
			auto url = queries[i].DocumentEnd->getCurrentDoc().url;
			urls[i].push_back( url  );
			queries[i].NextDocument();

			}
		clock_t end = clock();
		double time = (end - start) / (double) CLOCKS_PER_SEC;
		times.push_back(time);

		}





	int i = 0;
	for(auto output  : urls)
		{
		cout << queries[i].term << endl;
		cout << "Time to complete query: " << times[i] << endl;
		for(auto urrl : output) {
			cout << urrl << endl;
			}
		i++;
		}


	cout << "Printing Set Intersection " << endl;
	vector<string> v1 = urls[0];
	vector<string> v2 = urls[1];

	std::vector<string> v_intersection;

	std::set_union(v1.begin(), v1.end(),
								 v2.begin(), v2.end(),
								 std::inserter(v_intersection, v_intersection.begin()));
	for(auto url : v_intersection)
		std::cout << url << endl;

	cout << "Number of results" << v_intersection.size( ) << endl;


	return 0;
	}