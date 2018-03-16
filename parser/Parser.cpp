
#include "Parser.h"


/**
 * Parser Cstor
 * @param urlFrontierIn
 */
Parser::Parser ( ProducerConsumerQueue< string > *urlFrontierIn )
	{
	urlFrontier = urlFrontierIn;
	}


/**
 * Executes the Parser
 * @return
 */
const unordered_map< string, vector< int > > *Parser::execute ( Document *document )
	{
	Tokenizer tokenizer;
	parse( document->DocToString( ), &tokenizer );
	return tokenizer.get( );
	}

/**
 * Parses file
 * @param inFile
 * @return
 */
//TODO instead of grabbing each line, look to see if beginning of
// TODO title/url/anchortext, etc. Then continue until close tag and add to tokenizer after end of tag found
void Parser::parse ( string html, Tokenizer *tokenizer )
	{
	auto htmlIt = html.begin( );
	unsigned long offset = 0;
	while ( htmlIt != html.end( ) )
		{
		// if open bracket
		if ( *htmlIt == '<' )
			{
			auto begCloseTag = findNext( "</", htmlIt );
			auto endCloseTag = findNext( ">", begCloseTag );
			string line( htmlIt, endCloseTag + 1 );
			htmlIt = endCloseTag + 2;

			// check if line is url
			string url = extract_url( line );
			if ( url != "" )
				{
				urlFrontier->Push( url );
				cout << url << endl;
				}
				// check if line is title
			else
				{
				string title = extract_title( line );
				if ( title != "" )
					{
					tokenizer->execute( title, offset );
					}
				}
			offset = htmlIt - html.begin( );
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
string Parser::extract_url ( string & word )
	{
	string url = "";
	if ( *findStr( "<a", word ) != '\0' )
		{
		auto foundHref = findStr( "href", word );
		auto foundHttp = findNext( "http", foundHref );
		if ( *foundHttp != '\0' )
			{
			url = "";
			auto closeTag = findNext( ">", foundHref );
			if ( *closeTag != '\0' && *( closeTag - 1 ) == '\"' )
				{
				closeTag -= 1;
				}
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
string Parser::extract_title ( string & word )
	{
	string title = "";
	char end = '<';
	auto pos = findStr( "<title>", word );
	if ( *pos != '\0' )
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

