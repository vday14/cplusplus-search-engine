
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
#include "../crawler/UrlFrontier.h"
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
	Parser ( UrlFrontier  *urlFrontierIn );

	/**
	 * Executes the Parser
	 * @return
	 */
	const unordered_map< string, vector< unsigned long > > *execute ( StreamReader *reader );


private:
	UrlFrontier *urlFrontier;

	/**
	 * Parses file
	 * @param inFile
	 * @return
	 */
	void parse ( StreamReader *reader, Tokenizer *tokenizer );

	/**
	 * Returns anchor text if found
	 * @param html 
	 * @return 
	 */
	string extractAnchorText ( string html );

	/**
	 * Returns true if no closing tag & should ignore
	 * @param html
	 * @param htmlIt
	 * @return
	 */
	bool isInvalidTag( string html, unsigned long htmlIt );

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
	 * @param currentUrl
	 * @return
	 */
	string isLocal ( string url, ParsedUrl currentUrl );

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
	void pushToUrlQueue ( string url, ParsedUrl * currentUrl, string anchorText, bool debug );

	/**
	 * Returns true if given tag
	 *
	 * @param html
	 * @param tag
	 * @return
	 */
	bool isTag ( string html, string tag );

	/**
	 * Extracts the paragraph text
	 *
	 * @param html
	 * @param offsetTitle
	 * @param offsetBody
	 * @param isParagraph
	 * @param tokenizer
	 * @param currentUrl
	 * @return
	 */
	string extractBody ( string html, unsigned long & offsetTitle, unsigned long & offsetBody, bool isParagraph,
	                      Tokenizer *tokenizer,
	                      ParsedUrl * currentUrl );


	/**
	 * Extracts all text in html
	 *
	 * @param line
	 * @param offsetTitle
	 * @param offsetBody
	 * @param isParagraph
	 * @param tokenizer
	 * @param currentUrl
	 */
	void extractAll ( string line, unsigned long & offsetTitle, unsigned long & offsetBody, bool isParagraph,
	                   Tokenizer *tokenizer,
	                   ParsedUrl * currentUrl );

	//TODO delete?? may not need
	/**
	 * Removes given html tags
	 *
	 * @param html
	 * @param htmlIt
	 * @param savePosition
	 * @param tag
	 */
	void removeTag ( string & html, unsigned long & htmlIt, unsigned long savePosition, string tag );

	/**
	 * Extracts the header tags and adds to body
	 * @param html
	 * @return
	 */
	string extractHeader ( string html );

	};

