//
// Created by Zane Dunnings on 2/19/18.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "../Indexer.h"

using namespace std;

int main( int argc, char *argv[]) {
	Indexer indexer = Indexer();

	unordered_map<string, vector<int> > test1;
	ifstream ifstream1(argv[ 1 ]);

	string word = "";
	int id = 0;
	while(ifstream1 >> word) {
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
		if(word != "")
			test1[word].push_back(id);
		id++;
		}

	indexer.pointerToDictionaries.Push(&test1);
	indexer.verbose_run();
	indexer.verbose_save();
	cout << "congrats!";

	}