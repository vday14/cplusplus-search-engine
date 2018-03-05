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
	//TODO instead of grabbing each line, look to see if beginning of
	// TODO title/url/anchortext, etc. Then continue until close tag and add to tokenizer after end of tag found
	void parse ( string html, Tokenizer *tokenizer )
		{
		auto htmlIt = html.begin();
		int offset = 0;
		while (htmlIt != html.end())
			{
			// if open bracket
			if ( *htmlIt == '<' )
				{
				auto begCloseTag = findNext ("</", htmlIt);
				auto endCloseTag = findNext ( ">", begCloseTag);
				string line (htmlIt, endCloseTag + 1);
				htmlIt = endCloseTag + 2;

				// check if line is url
				string url = extract_url ( line );
				if (url != "")
					{
					urlFrontier->Push ( url );
					}
				// check if line is title
				else
					{
					string title = extract_title ( line );
					if (title != "")
						{
						tokenizer->execute ( title, offset );
						}
					}
				//TODO fix offset?
				offset = htmlIt - html.begin();
				}
			else
				{
				++htmlIt;
				}
			}


		}

	/**
	 * Returns a url, or "" if none
	 * @param word
	 * @return
	 */
	string extract_url ( string word )
		{
		string url = "";
		if ( *findStr ( "<a", word ) != '\0' )
			{
			auto foundHref = findStr ( "href", word );
			auto foundHttp = findNext ( "http", foundHref );
			if ( *foundHttp != '\0' )
				{
				url = "";
				auto closeTag = findNext ( ">", word.begin ( ) );
				while ( *foundHttp != *closeTag )
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
		char end = '<';
		auto pos = findStr ( "<title>", word );
		if ( *pos != '\0')
			{
			pos += 7;
			while ( *pos != end )
				{
				title += *pos;
				++pos;
				}
			}
		return title;
		}

	};

