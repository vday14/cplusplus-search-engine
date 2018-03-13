
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "stringProcessing.h"

using namespace std;

class Tokenizer
	{
	
public:
	Tokenizer ( );

	unordered_map< string, vector< int>> *get ( ) const;

	void execute ( string originalText, int offset );

	private:
		unordered_map< string, vector< int>> *docIndex;
	
	};
