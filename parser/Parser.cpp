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
const unordered_map< string, vector< unsigned long > > *Parser::execute ( StreamReader *reader )
	{
	Tokenizer tokenizer;
	parse( reader, &tokenizer );
	return tokenizer.get( );
	}

/**
 * Parses file
 * @param inFile
 * @return
 */
void Parser::parse ( StreamReader *reader, Tokenizer *tokenizer )
	{

	unsigned long htmlIt = 0;
	unsigned long offsetTitle = 0;
	unsigned long offsetURL = 0;
	unsigned long offsetAnchor = 0;
	unsigned long offsetBody = 0;
	ParsedUrl currentUrl = reader->getUrl( );

	// tokenize anchor
	// TODO ParsedUrl with anchor text
	string anchorText = currentUrl.getAnchorText( );
	if ( anchorText != "" )
		{
		offsetAnchor = tokenizer->execute( anchorText, offsetAnchor, Tokenizer::ANCHOR );
		}
	// tokenize url
	offsetURL = tokenizer->execute( currentUrl.getHost( ) + "/" + currentUrl.getPath( ), offsetURL, Tokenizer::URL );

	string html = reader->PageToString( );
	while ( htmlIt < html.size( ) )
		{
		unsigned long begCloseTag = 0;
		bool isParagraph = false;
		unsigned long savePosition = htmlIt;

		if ( htmlIt >= html.size( ) )
			break;
		// if open bracket
		if ( html[ htmlIt ] == '<' )
			{

			if (  html[ htmlIt + 1 ] == 'p' && ( ( html[htmlIt + 2]) == '>' || ( html[ htmlIt + 2 ] == ' ') ) )
				{
				begCloseTag = findNext( "</p>", htmlIt, html );
				isParagraph = true;
				}
			else
				{
				begCloseTag = findNext( "</", htmlIt, html );
				}
			unsigned long endCloseTag = findNext( ">", begCloseTag, html );
			string line = subStr( html, htmlIt, endCloseTag + 1 - htmlIt );
			htmlIt = endCloseTag + 2;


			// check if line is url
			string title = extractTitle( line );
			string url = extractUrl( line );
			string header = extractHeader( line );
			// checking if html line is script
			if ( isTag( line, "script" ) )
				{
				//DO NOTHING
				}
				//checking for p tag
			else if ( isParagraph )
				{
				string body = extractBody( line, offsetTitle, offsetBody, isParagraph, tokenizer, currentUrl );
				offsetBody = tokenizer->execute( body, offsetBody, Tokenizer::BODY );
				}

			// if html line is url, parses accordingly and pushes to frontier
			else if ( url != "" )
				{
				pushToUrlQueue( url, currentUrl, extractAnchorText( "" ), false );
				}
			// check if line is header; classifies as body text
			else if ( header != "")
				{
				offsetBody = tokenizer->execute( header, offsetBody, Tokenizer::BODY );
				}
			// check if line is title
			else if ( title != "" )
				{
				offsetTitle = tokenizer->execute( title, offsetTitle, Tokenizer::TITLE );
				}
			else
				{
				//DO NOTHING
				}
			}
		else
			{
			++htmlIt;
			}
		}
	}

/**
 * Returns anchor text if found
 * @param html
 * @return
 */
string Parser::extractAnchorText ( string html )
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

			while ( foundHttp != closeUrl && html[ foundHttp ] != '\n' )
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
	if ( lastFour == ".png" || lastFour == ".jpg" || lastFour == ".css" || lastFour == ".gif"
	     || lastFour == ".pdf" || lastFour == ".wav" || lastFour == ".mp3" || lastFour == ".mp4" || lastFour == ".ico" )
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
void Parser::pushToUrlQueue ( string url, ParsedUrl currentUrl, string anchorText, bool debug )
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


//TODO delete?? may not need
/**
 * Removes given html tags
 *
 * @param html
 * @param htmlIt
 * @param savePosition
 * @param tag
 */
void Parser::removeTag ( string & html, unsigned long & htmlIt, unsigned long savePosition, string tag )
	{
	unsigned long openTag = findStr( "<" + tag + ">", html );
	unsigned long closeTag = findNext( "</" + tag + ">", openTag, html );
	//TODO write erase functions??
	html.erase( closeTag, tag.length( ) + 2 );
	html.erase( openTag, tag.length( ) + 3 );

	htmlIt = savePosition;
	}

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
void Parser::extractAll ( string line, unsigned long & offsetTitle, unsigned long & offsetBody, bool isParagraph,
                  Tokenizer *tokenizer,
                  ParsedUrl & currentUrl )
	{
	// check if line is url
	string title = extractTitle( line );
	string url = extractUrl( line );
	//checking if html line is script
	if ( isTag( line, "script" ) )
		{
		//DO NOTHING
		}
		//TODO delete this conditional if keeping whats in main right now
	else if ( isParagraph )
		{
		string body = extractBody( line, offsetTitle, offsetBody, isParagraph, tokenizer, currentUrl );
		offsetBody = tokenizer->execute( body, offsetBody, Tokenizer::BODY );
		}

	else if ( url != "" )
		{
			pushToUrlQueue( url, currentUrl, extractAnchorText( "" ), false );
		}
		// check if line is title
		// check if line is title
	else if ( title != "" )
		{
		offsetTitle = tokenizer->execute( title, offsetTitle, Tokenizer::TITLE );
		}

	else
		{
		//DO NOTHING
		}
	}

/**
 * Returns true if given tag
 *
 * @param html
 * @param tag
 * @return
 */
bool Parser::isTag ( string html, string tag )
	{
	string findTag = "<" + tag;
	if ( findStr( findTag, html ) < html.size( ) )
		{
		return true;
		}
	return false;
	}

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
string Parser::extractBody ( string html, unsigned long & offsetTitle, unsigned long & offsetBody, bool isParagraph,
                     Tokenizer *tokenizer,
                     ParsedUrl & currentUrl )
	{
	string body = "";
	unsigned long startParTag = findNext( "<p>", 0, html );
	unsigned long closeParTag = findNext( "</p>", startParTag, html );
	unsigned long nextCloseTag = findNext( "</", startParTag, html );
	startParTag += 3;
	while ( nextCloseTag != startParTag )
		{
		if ( closeParTag == nextCloseTag )
			{
			while ( startParTag != closeParTag )
				{
				body += html[ startParTag ];
				++startParTag;
				if ( startParTag >= html.size( ) )
					{
					return body;
					}
				}
			}
		else
			{
			unsigned long newHtmlStart = findNext( "<", startParTag, html );
			char a = html[ newHtmlStart ];
			unsigned long closeNewHtml = findNext( ">", newHtmlStart, html );
			char b = html[ closeNewHtml ];
			unsigned long newHtmlTagLength = closeNewHtml - newHtmlStart;

			while ( startParTag != newHtmlStart )
				{
				body += html[ startParTag ];
				++startParTag;
				}

			string newHtml = subStr( html, newHtmlStart, nextCloseTag - newHtmlStart + newHtmlTagLength + 2 );
			extractAll( newHtml, offsetTitle, offsetBody, false, tokenizer, currentUrl );
			startParTag = nextCloseTag + newHtmlTagLength + 2;
			nextCloseTag = findNext( "</", startParTag, html );
			}
		}

	return body;
	}
/**
 * Extracts the header tags and adds to body
 * @param html
 * @return
 */
string Parser::extractHeader ( string html )
	{
	string header = "";
	unsigned long startHeader = findStr( "<h", html );
	if ( startHeader != html.size( ) && ( html[ startHeader + 1 ] >= '1' && html[ startHeader + 1 ] <= '6' ) )
		{
		unsigned long endHeader = findNext( "</h", startHeader, html );
		startHeader += 4;
		while ( startHeader != endHeader )
			{
			header += html[ startHeader ];
			++startHeader;
			}
		}
	return header;
	}
