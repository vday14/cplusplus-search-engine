//
// Created by nick on 3/16/18.
//

#include <iostream>
#include <set>
#include "../../indexer/DocumentEnding.h"
#include "../ISRWord.h"
#include "../../util/Stemmer.h"
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

	Stemmer stem;
	/*
	for(auto dec : decorators)
		{

		ISRWord queryWord( dec + stem.execute("world") ) ;
		queries.push_back(queryWord);
		}
*/
	ISRWord queryWord( "spiritual" ) ;
	queries.push_back(queryWord);
	vector<size_t> locations;
	set<string> urls;

	clock_t start = clock();

	for(auto query : queries)
		{
		while(query.getCurrentLocation() != MAX_Location)  {
			auto url = query.DocumentEnd->getCurrentDoc().url;
			urls.insert( url  );
			query.NextDocument();

			}

		}


    clock_t end = clock();

    cout << "Time to complete query: " << (end - start) / (double) CLOCKS_PER_SEC << endl;
		for(auto url :urls)
			cout << url << endl;

	cout << "Number of results: " << urls.size();
    return 0;
}
