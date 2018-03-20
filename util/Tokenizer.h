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

	// decorators
	static const char TITLE = '#';
	static const char ANCHOR = '@';
	static const char URL = '$';
	static const char BODY = '%';

	/**
 	* Tokenizer Cstor
 	*/
	Tokenizer ( );


	/**
 	* Returns pointer to the docIndex dictionary
	 *
 	* @return pointer to unordered_map< string, vector< int>>
 	*/
	const unordered_map< string, vector< unsigned long > > *get ( ) const;

	/**
	 * Executes the Tokenizer
	 * Sends tokens to dictionary
	 *
	 *
	 * @param originalText
	 * @param offset
	 * @param decorator
	 */
	unsigned long execute ( string originalText, unsigned long offset, char decorator = '\0' );

private:

    unordered_map< string, vector< unsigned long > > *docIndex;
    Stemmer stem;

    /**
     * Tokenizes text (titles, body text)
     *
     * @param originalText
     * @param offset
     * @param decorator
     */
    unsigned long tokenize ( vector< string > splitText, unsigned long offset, char decorator );

};
