//
// Created by Jake Close on 3/16/18.
//

#include <iostream>
#include <set>
#include "../../indexer/DocumentEnding.h"
#include "../ISRWord.h"
#include "../ISREndDoc.h"
#include "../ISRAnd.h"
#include <vector>
using namespace std;

int main ( )
	{
	char* query;
	ISRWord *q1 = new ISRWord("%trump");
	ISRWord *q2 = new ISRWord("%washington");
	vector< ISR* > input;
	input.push_back(q1);
	input.push_back(q2);
	ISRAnd *queryAnd = new ISRAnd(input);
	ISREndDoc endDocs;
	vector<size_t> locations;
	vector<DocumentEnding> docEnds;
	set<string> urls;
	while(queryAnd->GetCurrentLocation() != MAX_Location) {
		locations.push_back(queryAnd->NextDocument());
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