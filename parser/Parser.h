
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

<<<<<<< HEAD

	Parser ( ProducerConsumerQueue < string > * urlFrontierIn)
		{
		urlFrontier = urlFrontierIn;
		}
=======
	/**
	 * Parser Cstor
	 * @param urlFrontierIn
	 */
	Parser ( ProducerConsumerQueue< ParsedUrl > *urlFrontierIn );
>>>>>>> 02e3c89768ec57f7ea0c16a6fdf7e3d17c3d07bb


	/**
	 * Executes the Parser
	 * @return
	 */
<<<<<<< HEAD
	// TODO need to change vector type to word data, change where struct is declared
	const unordered_map< string, vector< Tokenizer::wordData>> * execute ( Document* document)
		{
		Tokenizer tokenizer;
		parse ( document->DocToString (), &tokenizer );
		return tokenizer.get ( );
		}
=======
	const unordered_map< string, vector< unsigned long > > *execute ( Document *document );
>>>>>>> 02e3c89768ec57f7ea0c16a6fdf7e3d17c3d07bb


private:
	ProducerConsumerQueue< ParsedUrl > *urlFrontier;

	/**
	 * Parses file
	 * @param inFile
	 * @return
	 */
<<<<<<< HEAD
	void parse ( string html, Tokenizer *tokenizer );
=======
	void parse ( string html, ParsedUrl currentUrl, Tokenizer *tokenizer );
>>>>>>> 02e3c89768ec57f7ea0c16a6fdf7e3d17c3d07bb


	/**
	 * Returns a url, or "" if none
	 * @param html
	 * @return
	 */
	string extract_url ( string html );


	/**
	 * Returns a title, or "" if none
	 * @param html
	 * @return
	 */
	string extract_title ( string html );

<<<<<<< HEAD
	bool isScript ( string & word );

	string extract_body( string & word );
=======
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
>>>>>>> 02e3c89768ec57f7ea0c16a6fdf7e3d17c3d07bb
	};

