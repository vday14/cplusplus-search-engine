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
const unordered_map< string, vector< unsigned long > > *Parser::execute ( StreamReader* reader)
	{
	Tokenizer tokenizer;
	parse(reader, &tokenizer);
	return tokenizer.get( );
	}

/**
 * Parses file
 * @param inFile
 * @return
 */
void Parser::parse ( StreamReader* reader, Tokenizer *tokenizer )
	{

	unsigned long htmlIt = 0;
	unsigned long offsetTitle = 0;
	unsigned long offsetURL = 0;
	unsigned long offsetAnchor = 0;
	ParsedUrl currentUrl = reader->getUrl();

	// tokenize url
	offsetURL = tokenizer->execute( currentUrl.getHost( ) + "/" + currentUrl.getPath( ), offsetURL, Tokenizer::URL );

	// tokenize anchor
	// TODO ParsedUrl with anchor text
	string anchorText = currentUrl.getAnchorText( );
	if ( anchorText != "" )
		{
		offsetAnchor = tokenizer->execute( anchorText, offsetAnchor, Tokenizer::ANCHOR );
		}

	reader->request();
	bool success = reader->checkStatus();
	if(success)
		{
		string html = reader->PageToString( );
		while ( htmlIt < html.size( ) )
			{
			// if open bracket
			if ( html[ htmlIt ] == '<' )
				// if open bracket
				if ( htmlIt >= html.size( ) )
					break;

			if ( html[ htmlIt ] == '<' )
				{
				unsigned long begCloseTag = findNext( "</", htmlIt, html );
				unsigned long endCloseTag = findNext( ">", begCloseTag, html );
				string line = subStr( html, htmlIt, endCloseTag + 1 - htmlIt );
				htmlIt = endCloseTag + 2;

				// check if line is url
				string url = extractUrl( line );
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
						ParsedUrl pUrl = ParsedUrl( url );
						urlFrontier->Push( pUrl );
						cout << url << endl;
						}
					}
					// check if line is title
				else
					{
					string title = extractTitle( line );
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
	}

/**
 * Returns anchor text if found
 * @param html
 * @return
 */
string Parser::extractAnchorText( string html )
	{
	return "";
	}

/**
 * Returns a url, or "" if none
 * @param word
 * @return
 */
string Parser::extractUrl ( string html )
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
			unsigned long closeSpace = findNext( " ", foundHref, html );
			unsigned long closeUrl = 0;
			// end == ' >'
			if ( closeSpace < html.size( ) && closeTag < html.size( ) && closeSpace < closeTag )
				{
				if ( html[ closeSpace - 1 ] == '\"' )
					{
					closeSpace -= 1;
					}
				closeUrl = closeSpace;
				}
			// end == '>'
			else if ( closeTag < html.size( ) )
				{
				if ( html[ closeTag - 1 ] == '\"' )
					{
					closeTag -= 1;
					}
				closeUrl = closeTag;
				}

			while ( foundHttp != closeUrl && html[ foundHttp ] != '\n')
				{
				url.push_back( html[ foundHttp ] );
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
string Parser::extractTitle ( string html )
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

	// png || jpg || css || gif || pdf || wav || mp3 || mp4 || ico
	if ( lastFour == ".png" ||  lastFour == ".jpg" || lastFour == ".css" ||  lastFour == ".gif"
	     || lastFour == ".pdf" ||  lastFour == ".wav" || lastFour == ".mp3" || lastFour == ".mp4" || lastFour == ".ico" )
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

/**
 * Sends to Url Frontier
 *
 * @param url
 * @param currentUrl
 * @param anchorText --> will be "null" if empty
 * @param debug --> will print urls to std::cout
 */
void Parser::pushToUrlQueue( string url, ParsedUrl currentUrl, string anchorText, bool debug )
	{
	if ( isLocal( url ) )
		{
		url = currentUrl.getCompleteUrl( ) + url;
		}
	if ( isValid( url ) && url != currentUrl.getCompleteUrl( ) )
		{
		ParsedUrl pUrl = ParsedUrl( url );
		pUrl.setAnchorText( anchorText );
		urlFrontier->Push( pUrl );
		if ( debug )
			{
			cout << url << endl;
			cout << anchorText << endl;
			}
		}
	}
