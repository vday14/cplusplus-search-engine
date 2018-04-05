//
// Created by Zane Dunnings on 4/2/18.
//

#include "../Ranker.h"
#include <iostream>
#include <set>


void testSimple();

int main()
	{
	cout << "------Starting Ranker Test------" << endl;
	testSimple ();
	cout << "------Passed All Ranker Tests---" << endl;
	}

void testSimple()
	{
	//Initialize Ran
	ISRWord queryWord("%trump");
	ISREndDoc endDocs;
	vector<size_t> locations;
	vector<DocumentEnding> docEnds;
	set<string> urls;

	while( queryWord.getCurrentLocation() != MAX_Location )
		{
		auto url = queryWord.DocumentEnd->getCurrentDoc().url;
		urls.insert(  url  );
		queryWord.NextDocument();

		}

	}


