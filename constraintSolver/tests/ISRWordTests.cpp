//
// Created by nick on 3/16/18.
//

#include <iostream>
#include <set>
#include "../../indexer/DocumentEnding.h"
#include "../ISRWord.h"
#include "../ISREndDoc.h"


using namespace std;

int main ( ) {
	//char* query = "iphone";


	vector<ISRWord> queries;
	vector<string> decorators;
	decorators.push_back("#");
	decorators.push_back("%");
	decorators.push_back("@");
	decorators.push_back("$");

	for(auto dec : decorators)
		{

		ISRWord queryWord( dec + "trump");
		queries.push_back(queryWord);
		}

	vector<size_t> locations;
	set<string> urls;

	clock_t start = clock();

	for(auto query : queries)
		{
		while(query.getCurrentLocation() != MAX_Location)  {
			auto url = query.DocumentEnd->getCurrentDoc().url;
			urls.insert( url  );
			query.NextDocument();
			cout << url << endl;
			}

		}


    clock_t end = clock();

    cout << "Time to complete query: " << (end - start) / (double) CLOCKS_PER_SEC << endl;
		for(auto url :urls)
			cout << url << endl;

	cout << "Number of results: " << urls.size();
    return 0;
}
