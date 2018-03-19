
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


	Parser ( ProducerConsumerQueue < string > * urlFrontierIn)
		{
		urlFrontier = urlFrontierIn;
		}


	/**
	 * Parser
	 * @return
	 */
	// TODO need to change vector type to word data, change where struct is declared
	const unordered_map< string, vector< Tokenizer::wordData>> * execute ( Document* document)
		{
		Tokenizer tokenizer;
		parse ( document->DocToString (), &tokenizer );
		return tokenizer.get ( );
		}


private:
	ProducerConsumerQueue < string >* urlFrontier;

	/**
	 * Parses file
	 * @param inFile
	 * @return
	 */
	void parse ( string html, Tokenizer *tokenizer );


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

	bool isScript ( string & word );

	string extract_body( string & word );
	};

