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
	ISRWord queryWord("%trump");
	ISREndDoc endDocs;
	vector<size_t> locations;
	vector<DocumentEnding> docEnds;
	set<string> urls;

	clock_t start = clock();


	while(queryWord.getCurrentLocation() != MAX_Location)  {
		auto url = queryWord.DocumentEnd->getCurrentDoc().url;
		urls.insert( url  );
		queryWord.NextDocument();

		}

    clock_t end = clock();

    cout << "Time to complete query: " << (end - start) / (double) CLOCKS_PER_SEC << endl;
		for(auto url :urls)
			cout << url << endl;

	cout << "Number of results: " << urls.size();
    return 0;
}
