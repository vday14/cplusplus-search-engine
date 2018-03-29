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
	char* query;
	ISRWord *q1 = new ISRWord("iphone");
	ISRWord *q2 = new ISRWord("apple");
	vector< ISR* > input;
	input.push_back(q1);
	input.push_back(q2);
	ISROr *queryOr = new ISROr(input);
	ISREndDoc endDocs;
	vector<size_t> locations;
	vector<DocumentEnding> docEnds;
	set<string> urls;
	while(queryOr->GetCurrentLocation() != MAX_Location) {
		locations.push_back(queryOr->Next());
		}
	while(endDocs.next().url != "aaa")
		{
		for(auto locs : locations)
			{
			if(locs < endDocs.getCurrentDoc().docEndPosition &&
				locs >= (endDocs.getCurrentDoc().docEndPosition - endDocs.getCurrentDoc().docNumWords)) {
				urls.insert(endDocs.getCurrentDoc().url);
				}
			}

		}
	for(auto urrl : urls) {
		cout << urrl << endl;
		}
	return 0;
	}