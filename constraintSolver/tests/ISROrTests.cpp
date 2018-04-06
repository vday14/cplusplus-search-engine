//
// Created by Jake Close on 3/16/18.
//

#include <iostream>
#include <set>
#include "../../indexer/DocumentEnding.h"
#include "../ISRWord.h"
#include "../ISREndDoc.h"
#include "../ISROr.h"
#include <vector>
using namespace std;

int main ( )
	{
	string query;
	vector< ISR* > input;
	query = "!";
	while(cin >> query)
		{
		if(query == "-q")
			break;
		ISRWord *q = new ISRWord( query.c_str() );
		input.push_back(q);
		}




	ISROr *queryOr = new ISROr(input);
	set<string> urls;
	clock_t start = clock();

	while(queryOr->GetCurrentLocation() != MAX_Location) {

		auto url = queryOr->GetEndDocument()->getCurrentDoc().url;
		if(url == "file59tweet151421970293063681")
			cout << "PREBUG";
		cout << url << endl;
		urls.insert(url);
		queryOr->NextDocument();

		}

	clock_t end = clock();


	for(auto urrl : urls) {
		cout << urrl << endl;
		}

	cout << "Time to complete query: " << (end - start) / (double) CLOCKS_PER_SEC << endl;
	cout << "Number of results: " << urls.size();

	/*
	 *
	 * moment and life
	 	file3tweet151407709667856384
		file5tweet151408405939093504
		file9tweet151409353818255361
	 *
	 *
	 * token and life
	 * file48tweet151419172700684288
	 */


	return 0;
	}