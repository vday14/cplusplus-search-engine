
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

	auto htmlIt = html.begin( );
	unsigned long offsetTitle = 0;
	unsigned long offsetURL = 0;

	// tokenize url
	string host = "";
	host.assign( currentUrl.Host );
	string path = "";
	path.assign( currentUrl.Path );
	string url = host + "/" + path;

	offsetURL = tokenizer->execute( url, offsetURL, Tokenizer::URL );

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
				if ( isLocal ( url ) )
					{
					string completeUrl = "";
					completeUrl.assign( currentUrl.CompleteUrl );
					url = completeUrl + url;
					}
				urlFrontier->Push( url );
				cout << url << endl;
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

/**
 * Will return true if local url
 *
 * @param url
 * @return
 */
bool Parser::isLocal ( string url )
	{
	return ( *url.begin( ) == '/' );
	}