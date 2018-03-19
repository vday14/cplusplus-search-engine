#include "Parser.h"
#include <string>

/**
 * Parser Cstor
 * @param urlFrontierIn
 */
Parser::Parser ( ProducerConsumerQueue< ParsedUrl > *urlFrontierIn )
	{
	urlFrontier = urlFrontierIn;
	}


/**
 * Executes the Parser
 * @return
 */
const unordered_map< string, vector< unsigned long > > *Parser::execute ( Document *document )
	{
	Tokenizer tokenizer;
	parse( document->DocToString( ), document->getUrl( ), &tokenizer );
	return tokenizer.get( );
	}

/**
 * Parses file
 * @param inFile
 * @return
 */
void Parser::parse ( string html, ParsedUrl currentUrl, Tokenizer *tokenizer )
	{

	unsigned long htmlIt = 0;
	unsigned long offsetTitle = 0;
	unsigned long offsetURL = 0;

	// tokenize url
	string host = "";
	host.assign( currentUrl.Host );
	string path = "";
	path.assign( currentUrl.Path );
	string url = host + "/" + path;

	offsetURL = tokenizer->execute( url, offsetURL, Tokenizer::URL );

	while ( htmlIt < html.size( ) )
		{
		// if open bracket
		if ( html[ htmlIt  ]== '<' )
			{
			unsigned long begCloseTag = findNext( "</", htmlIt, html );
			unsigned long endCloseTag = findNext( ">", begCloseTag, html );
			string line = subStr( html, htmlIt, endCloseTag );
			htmlIt = endCloseTag + 2;

			// check if line is url
			string url = extract_url( line );
			if ( url != "" )
				{
				if ( isLocal( url ) )
					{
					string completeUrl = "";
					completeUrl.assign( currentUrl.CompleteUrl );
					url = completeUrl + url;
					}
				if ( isValid( url ) )
					{
					// TODO ParsedUrl with anchor text
					ParsedUrl pUrl = ParsedUrl( url );
					urlFrontier->Push( pUrl );
					cout << url << endl;
					}
				}
				// check if line is title
			else
				{
				string title = extract_title( line );
				if ( title != "" )
					{
					offsetTitle = tokenizer->execute( title, offsetTitle, Tokenizer::TITLE );
					}
				}
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
string Parser::extract_url ( string html )
	{
	string url = "";
	if ( findStr( "<a", html ) != html.size( ) )
		{
		unsigned long foundHref = findStr( "href", html );
		unsigned long foundHttp = findNext( "http", foundHref, html );
		if ( foundHttp < html.size( ) )
			{
			url = "";
			unsigned long closeTag = findNext( ">", foundHref, html );
			if ( closeTag < html.size( ) && html[ closeTag - 1 ] == '\"' )
				{
				closeTag -= 1;
				}
			while ( html[ foundHttp ] != html[ closeTag ] )
				{
				url += html[ foundHttp ];
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
string Parser::extract_title ( string html )
	{
	string title = "";
	char end = '<';
	auto pos = findStr( "<title>", html );
	if ( pos < html.size( ) )
		{
		pos += 7;
		while ( html[ pos ] != end )
			{
			title += html[ pos ];
			++pos;
			}
		}
	return title;
	}

/**
 * Will return true if local url
 *
 * @param url
 * @return
 */
bool Parser::isLocal ( string url )
	{
	return ( url[ 0 ] == '/' );
	}

/**
 * Returns false if the link is an invalid type
 *
 * @param url
 * @return
 */
bool Parser::isValid ( string url )
	{
	unsigned long size = url.size( );

	string lastFive = lastN( url, 5 );
	string lastFour = lastN( url, 4 );

	// .html
	if ( lastFive == ".html" )
		{
		return true;
		}

	// png || jpg || css || gif || pdf || wav || mp3 || mp4
	if ( lastFour == ".png" ||  lastFour == ".jpg" || lastFour == ".css" ||  lastFour == ".gif" 
	     || lastFour == ".pdf" ||  lastFour == ".wav" || lastFour == ".mp3" || lastFour == ".mp4" )
		{
		return false;
		}
	//jpeg
	if ( lastFive == ".jpeg" )
		{
		return false;
		}
	return true;
	}
