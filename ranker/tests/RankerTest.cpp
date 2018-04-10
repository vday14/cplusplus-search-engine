//
// Created by Zane Dunnings on 4/2/18.
//

#include "../Ranker.h"
#include <iostream>
#include <set>


void testSimple();

int main()
	{
	cout << "------Starting ranker Test------" << endl;
	testSimple ();
	cout << "------Passed All ranker Tests---" << endl;
	}

void testSimple()
	{
	//Initialize Ran
	string query = "%everybodi";
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
	ISRWord queryWord1(query);
	ISRWord queryWord2(query);
	queryWord2.NextDocument();
	ISRWord queryWord3(query);
	queryWord3.NextDocument();

	ISRWord queryWord4(query);
	queryWord4.NextDocument();
	queryWord4.NextDocument();


	vector< ISRWord > wordList;
	wordList.push_back( queryWord1 );
	wordList.push_back( queryWord2 );
	wordList.push_back( queryWord3 );
	wordList.push_back( queryWord4 );


	Ranker rankeyboi = Ranker( wordList );
	rankeyboi.generateSiteList();
	rankeyboi.printSites();
	rankeyboi.rank();
	rankeyboi.printRankedSites();

	}


