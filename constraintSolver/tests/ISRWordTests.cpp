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
	ISRWord queryWord("news");
	ISREndDoc endDocs;
	vector<size_t> locations;
	vector<DocumentEnding> docEnds;
	set<string> urls;

	clock_t start = clock();


	while(queryWord.getCurrentLocation() != MAX_Location)  {
		auto url = queryWord.DocumentEnd->getCurrentDoc().url;
		cout << url << endl;
		urls.insert( url  );
		queryWord.NextDocument();

		}

	/*
	while(queryWord.getCurrentLocation() != MAX_Location) {
		locations.push_back(queryWord.Next());
    }
    locations.pop_back();
    clock_t start = clock();
    ISREndDoc fge;
    for(auto locs : locations) {
		fge.seek(locs);
		cout << fge.getCurrentDoc().url << endl;
	}
    clock_t end = clock();
    cout << "Time to complete query: " << (end - start) / (double) CLOCKS_PER_SEC << endl;
    start = clock();
    while(endDocs.next().url != "aaa") {
		for(auto locs : locations) {
			if(locs < endDocs.getCurrentDoc().docEndPosition &&
				locs >= (endDocs.getCurrentDoc().docEndPosition - endDocs.getCurrentDoc().docNumWords)) {
				urls.insert(endDocs.getCurrentDoc().url);
			}
        }
    }
    */
    clock_t end = clock();

    cout << "Time to complete query: " << (end - start) / (double) CLOCKS_PER_SEC << endl;

    return 0;
}
