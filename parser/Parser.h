
#pragma once
#include <string>
#include <functional>
#include <queue>
#include <iostream>
#include <fstream>
#include "../util/Tokenizer.h"
#include "../util/stringProcessing.h"
#include "../shared/Document.h"
#include "../shared/ProducerConsumerQueue.h"


using namespace std;

/**
 * This class uses the Doc object from the Crawler to parse the text
 * Returns a pointer to a dictionary that contains the tokenized input
 */
class Parser
	{

public:

	/**
	 * Parser Cstor
	 * @param urlFrontierIn
	 */
	Parser ( ProducerConsumerQueue < string > * urlFrontierIn);


	/**
	 * Executes the Parser
	 * @return
	 */
	const unordered_map< string, vector< unsigned long > > *execute ( Document *document );


private:
	ProducerConsumerQueue < string >* urlFrontier;

	/**
	 * Parses file
	 * @param inFile
	 * @return
	 */
	void parse ( string html, ParsedUrl currentUrl, Tokenizer *tokenizer );


	/**
	 * Returns a url, or "" if none
	 * @param word
	 * @return
	 */
	string extract_url ( string & word );


	/**
	 * Returns a title, or "" if none
	 * @param word
	 * @return
	 */
	string extract_title ( string & word );

	/**
	 * Will return true if local url
	 *
	 * @param url
	 * @return
	 */
	bool isLocal ( string url );

	};

