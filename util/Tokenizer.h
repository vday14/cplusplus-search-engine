
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "stringProcessing.h"
#include "Stemmer.h"

using namespace std;

class Tokenizer
	{

public:

	/**
 	* Tokenizer Cstor
 	*/
	Tokenizer ( );

	/**
 	* Returns pointer to the docIndex dictionary
	 *
 	* @return pointer to unordered_map< string, vector< int>>
 	*/
	unordered_map< string, vector< int>> *get ( ) const;

	/**
	 * Executes the Tokenizer
	 * Sends tokens to dictionary
	 *
	 * token -> [offsets]
	 * @param originalText
	 * @param offset
	 */
	void execute ( string &originalText, unsigned long offset );

	private:
		unordered_map< string, vector< int>> *docIndex;
		Stemmer stem;
	};
