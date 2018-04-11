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
	string query = "%trump";
	ISRWord queryWord(query);
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

	cout << "Number of results: " << urls.size() << "\n\n\n";

	clock_t startRanker = clock();

	Ranker rankeyboi;
	ISRWord doc(query);

	while(doc.getCurrentLocation() != MAX_Location)
		{
		vector< ISRWord > docvec;
		docvec.push_back ( doc );
		rankeyboi.addDoc ( docvec );
		doc.NextDocument ( );
		}


	rankeyboi.printRankedSites();

	clock_t endRanker = clock();
	cout << "Time to complete query: " << (endRanker - startRanker) / (double) CLOCKS_PER_SEC << endl;

	}


