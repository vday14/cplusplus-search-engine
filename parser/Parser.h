
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
#include "../crawler/Readers/StreamReader.h"


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
	Parser ( ProducerConsumerQueue< ParsedUrl > *urlFrontierIn );


	/**
	 * Executes the Parser
	 * @return
	 */
	const unordered_map< string, vector< unsigned long > > *execute ( StreamReader* reader );


private:
	ProducerConsumerQueue< ParsedUrl > *urlFrontier;

	/**
	 * Parses file
	 * @param inFile
	 * @return
	 */
	void parse ( StreamReader* reader, Tokenizer* tokenizer );

	/**
	 * Returns anchor text if found
	 * @param html 
	 * @return 
	 */
	string extractAnchorText( string html );
	
	/**
	 * Returns a url, or "" if none
	 * @param html
	 * @return
	 */
	string extractUrl ( string html );


	/**
	 * Returns a title, or "" if none
	 * @param html
	 * @return
	 */
	string extractTitle ( string html );

	/**
	 * Will return true if local url
	 *
	 * @param url
	 * @return
	 */
	bool isLocal ( string url );

	/**
	 * Returns true is url is valid
	 *
	 * @param url
	 * @return
	 */
	bool isValid ( string url );

	/**
	 * Sends to Url Frontier
	 * 
	 * @param url 
	 * @param currentUrl 
	 * @param anchorText 
	 * @param debug --> will print urls to std::cout
	 */
	void pushToUrlQueue( string url, ParsedUrl currentUrl, string anchorText, bool debug );

	};

