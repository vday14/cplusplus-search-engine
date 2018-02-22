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
#include "Tokenizer.h"
#include "../util/stringProcessing.h"

using namespace std;

// Doc Id
std::priority_queue< int > DOCID_PQ;
std::priority_queue< string > URL_PQ;
string PATH = "/doc";

//TEMP - remove once getting actual crawler input


//TODO
// get doc id from DocIDqueue (sent from crawler)
// go to disk and get the HTML file
// parse the html file
// if find url; send to crawler
// if find title send string to tokenizer
class Parser
	{

public:

	struct raw_data
		{
		string url;
		string html_data;

		raw_data ( string u, string h ) : url ( u ), html_data ( h )
			{ }
		};


	/**
	 * Parser
	 * @return
	 */
	// input: object with char*  and URL string
	//
	const unordered_map< string, vector< int>> execute ( )
		{
		Tokenizer tokenizer;
		//TEMP - until we get real input from crawler
		raw_data data ( "url", "html" );
		parse ( data.html_data, &tokenizer );
		return tokenizer.get ( );
		}


private:

	/**
	 * Parses file
	 * @param inFile
	 * @return
	 */

	string parse ( string & html_data, Tokenizer *tokenizer )
		{
		//figure out file handle syntax - pointer to file
		string tokenizerInput = "";
		string currentTerm = "";
		for ( int i = 0; i < html_data.size ( ); ++i )
			{
			while ( html_data[ i ] != ' ' )
				{
				currentTerm += html_data[ i ];
				}

			//one method that directly adds urls onto frontier instead of checking for them
			add_urls ( currentTerm );
			check_title ( currentTerm );
			tokenizerInput += currentTerm;
			}

		tokenizer->execute ( tokenizerInput );
		}

	/*
	 * Uses findStr function in stringProcessing.h: STILL HAVE TO TEST
	 * Instead of bool, just directly adds on to url queue
	 */
	void add_urls ( string & word )
		{
		string a_tag = "<a";
		string http_start = "href=http";
		string http_end_tag = ">";

		auto word_iter = word.begin ( );
		string url = "";
		word_iter = findStr ( word_iter, a_tag );
		if ( word_iter != nullptr )
			{
			auto found_http = findStr ( word_iter, http_start );
			if ( found_http != nullptr )
				{
				url = "http";
				found_http += 9;
				auto end_http = findStr ( word_iter, http_end_tag );
				while ( found_http != end_http )
					{
					url += *found_http;
					++found_http;
					}
				}
			}

		else
			{
			return;
			}

		if ( url != "" )
			{
			URL_PQ.push ( url );
			}


		}

	/**
	 * <title >AJF</title>
	 * @param word
	 */

	bool check_title ( string & word )
		{
		if ( char *pos = strstr ( "<title>", word ) )
			{
			pos += 6;
			auto end_pos = strstr ( "</title>", word );
			string title = "";
			while ( pos != end_pos )
				{
				++pos;
				title += *pos;

				}

			return title;
			}

//        string begin_title = "<title>";
//        auto word_begin = word.begin();
//        auto word_iter = findStr(word_begin, begin_title);

		}

	};

