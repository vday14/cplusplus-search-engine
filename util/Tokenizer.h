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
	static const char HOST = '=';

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
	 bool haveTitle;


    /**
     * Tokenizes text (titles, body text)
     *
     * @param originalText
     * @param offset
     * @param decorator
     */
    unsigned long tokenize ( vector< string > splitText, unsigned long offset, char decorator );

	/**
	 * Removes weird html encodings
	 *
	 * @param originalText
	 * @return
	 */
	std::string unEncodeHtml( std::string originalText );

	/**
	 * Anchor text that should not be included in index
	 */
	set< string > anchorsToRemove = {"click", "here", "here!"};

	/**
	 * html encoded mapped to correct char
	 */
	set < std::string > encodeSet =
			{ "&lsquo;", "&rsquo;", "&cent;", "&pound;", "&sect;", "&copy;", "&laquo", "&raquo;",
			  "&quot;", "&reg;", "&deg;", "&plusmn;", "&para;", "&middot;", "&frac12;", "&ndash;",
			  "&mdash;", "&rsquo;", "&sbquo;", "&ldquo;", "&rdquo;", "&bdquo;", "&dagger;", "&Dagger;",
			  "&bull;", "&hellip;", "&prime;", "&Prime;", "&apos;", "&euro;", "&trade;", "&asymp;", "&ne;",
			  "&le;", "&ge;", "&lt;", "&gt;", "ldquo" };
};
