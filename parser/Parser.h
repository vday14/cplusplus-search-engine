//
// Created by Veronica Day on 1/28/18.
//

// keep running count of offset, if stop word: don't incrememnt and remove stopword
// tokenizer returns pointer to document dictionary, parser puts it on the indexer's queue
//


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
	const unordered_map< string, vector< int>> * execute ( Document* document)
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
	void parse ( string html, Tokenizer *tokenizer )
		{

		string tokenizerInput = "";
		string currentTerm = "";
		for ( int i = 0; i < html.size ( ); ++i )
			{
			while ( html.at( i ) != '\n' )
				{
				currentTerm += html[ i ];
				}

			string url = extract_url ( currentTerm );
			if (url != "")
				{
				urlFrontier->Push (url);
				}
			else
				{
				string title = extract_title ( currentTerm );
				if (title != "")
					{
					tokenizerInput += title;
					}
				}

			}
		tokenizer->execute ( tokenizerInput );

		}

	/**
	 * Returns a url, or "" if none
	 * @param word
	 * @return
	 */
	string extract_url ( string word )
		{
		string url = "";

		if ( *findStr ( word, "<a" ) != '\0' )
			{
			auto foundHttp = findStr ( word, "href=http" );
			if ( *foundHttp != '\0' )
				{
				url = "http";
				foundHttp += 9;

				while ( *foundHttp != *findStr ( word, "\">" ) )
					{
					url += *foundHttp;
					++foundHttp;
					}
				}
			}

		return url;
		}

	/**
	 * Returns a title, or "" if none
	 * @param word
	 * @return
	 */
	string extract_title ( string & word )
		{
		string title = "";
		auto pos = findStr ( "<title>", word );
		if ( *pos != '\0')
			{
			pos += 6;
			while ( *pos != *findStr ( "</title>", word ) )
				{
				++pos;
				title += *pos;
				}
			}
		return title;
		}

	};

