#include "Parser.h"
#include <string>

/**
 * Parser Cstor
 * @param urlFrontierIn
 */
Parser::Parser ( UrlFrontier* urlFrontierIn )
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
	unsigned long offset = 0;
	ParsedUrl * currentUrl = reader->getUrl( );

	// tokenize anchor
	string anchorText = currentUrl->getAnchorText( );
	if ( anchorText != "" )
		{
		offset = tokenizer->execute( anchorText, offset, Tokenizer::ANCHOR );
		}
	// tokenize url
	offset = tokenizer->execute( currentUrl->getHost( ) + "/" + currentUrl->getPath( ), offset, Tokenizer::URL );

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
			if ( isInvalidTag(  html, htmlIt ) )
				{
				begCloseTag = findNext( ">", htmlIt, html );
				htmlIt = begCloseTag;
				continue;
				}
			else if (  html[ htmlIt + 1 ] == 'p' && ( ( html[htmlIt + 2]) == '>' || ( html[ htmlIt + 2 ] == ' ') ) )
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
				string body = extractBody( line, offset, offset, isParagraph, tokenizer, currentUrl );
				offset = tokenizer->execute( body, offset, Tokenizer::BODY );
				}

			// if html line is url, parses accordingly and pushes to frontier
			else if ( url != "" && url != "#" )
				{
				pushToUrlQueue( url, currentUrl, extractAnchorText( line ), false );
				}
			// check if line is header; classifies as body text
			else if ( header != "")
				{
				offset = tokenizer->execute( header, offset, Tokenizer::BODY );
				}
			// check if line is title
			else if ( title != "" )
				{
				offset = tokenizer->execute( title, offset, Tokenizer::TITLE );
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
	string anchor = "";
	unsigned long aTag = findStr( "<a", html );
	if ( aTag != html.size( ) )
		{
		unsigned long begAnchor = findNext( ">", aTag, html );
		unsigned long endAnchor = findNext( "</a>", aTag, html );

		if ( begAnchor > endAnchor)
			{
			return anchor;
			}

		if ( begAnchor < html.size( ) && endAnchor < html.size())
			{
			++begAnchor;
			while ( begAnchor != endAnchor && begAnchor < html.size( ) )
				{
				anchor += html[ begAnchor ];
				++begAnchor;
				}
			}
		}
	return anchor;
	}

/**
 * Return true if the tag does not close
 * @param html
 * @param htmlIt
 * @return
 */
bool Parser::isInvalidTag( string html, unsigned long htmlIt )
	{
	// check size first so stay within string
	if ( htmlIt + 1 < html.size( ) && html[ htmlIt + 1 ] == '!' && html[ htmlIt + 1 ] == '%' )
		{
		// comment or <!DocType> or <%
		return true;
		}

	if (htmlIt + 3 < html.size( ) )
		{
		// break
		if ( html[ htmlIt + 1 ] == 'b' && html[ htmlIt + 2 ] == 'r' && html[ htmlIt + 3 ] == '>' )
			return true;
		// br
		else if ( html[ htmlIt + 1 ] == 'c' && html[ htmlIt + 2 ] == 'o' && html[ htmlIt + 3 ] == 'l' )
			return true;
			// img
		else if ( html[ htmlIt + 1 ] == 'i' && html[ htmlIt + 2 ] == 'm' && html[ htmlIt + 3 ] == 'g' )
			return true;
			// input
		else if ( html[ htmlIt + 1 ] == 'i' && html[ htmlIt + 2 ] == 'n' && html[ htmlIt + 3 ] == 'p' )
			return true;
			// keygen
		else if ( html[ htmlIt + 1 ] == 'k' && html[ htmlIt + 2 ] == 'e' && html[ htmlIt + 3 ] == 'y' )
			return true;
			// link
		else if ( html[ htmlIt + 1 ] == 'l' && html[ htmlIt + 2 ] == 'i' && html[ htmlIt + 3 ] == 'n' )
			return true;
			// source
		else if ( html[ htmlIt + 1 ] == 's' && html[ htmlIt + 2 ] == 'o' && html[ htmlIt + 3 ] == 'u' )
			return true;
			// wbr
		else if ( html[ htmlIt + 1 ] == 'w' && html[ htmlIt + 2 ] == 'b' && html[ htmlIt + 3 ] == 'r' )
			return true;
		}

	if ( htmlIt + 4 < html.size( ) )
		{
		// meta
		if ( html[ htmlIt + 1 ] == 'm' && html[ htmlIt + 2 ] == 'e' && html[ htmlIt + 3 ] == 't' && html[ htmlIt + 4 ] == 'a' )
			return true;
			// area
		else if ( html[ htmlIt + 1 ] == 'a' && html[ htmlIt + 2 ] == 'r' && html[ htmlIt + 3 ] == 'e' && html[ htmlIt + 4 ] == 'a' )
			return true;
			// base
		else if ( html[ htmlIt + 1 ] == 'b' && html[ htmlIt + 2 ] == 'a' && html[ htmlIt + 3 ] == 's' && html[ htmlIt + 4 ] == 'e' )
			return true;
			// command
		else if ( html[ htmlIt + 1 ] == 'c' && html[ htmlIt + 2 ] == 'o' && html[ htmlIt + 3 ] == 'm' && html[ htmlIt + 4 ] == 'm' )
			return true;
			// track
		else if ( html[ htmlIt + 1 ] == 't' && html[ htmlIt + 2 ] == 'r' && html[ htmlIt + 3 ] == 'a' && html[ htmlIt + 4 ] == 'c' )
			return true;
		}

	if ( htmlIt + 5 < html.size( ) )
		{
		// param
		if ( html[ htmlIt + 1 ] == 'p' && html[ htmlIt + 2 ] == 'a' && html[ htmlIt + 3 ] == 'r'
		     && html[ htmlIt + 4 ] == 'a' && html[ htmlIt + 5 ] == 'm' )
			return true;
		}
	return false;
	}


/**
 * Returns a url, or "" if none
 * @param word
 * @return
 */
string Parser::extractUrl ( string html )
	{
	string url = "";
	unsigned long aTag = findStr( "<a", html );
	if ( aTag != html.size( ) )
		{
		unsigned long foundHref = findStr( "href=", html );
		unsigned long begQuote = findNext( "\"", foundHref, html );

		if ( begQuote < html.size( ) )
			{
			++begQuote;
			unsigned long endQuote = findNext( "\"", begQuote + 1, html );
			while ( begQuote != endQuote && endQuote < html.size( ) && begQuote < html.size( ) )
				{
				url += html[ begQuote ];
				++begQuote;
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
	auto pos = findStr( "<title", html );
	if ( pos < html.size( ) )
		{
		pos += 7;
		while ( html[ pos ] != end && pos < html.size( ) )
			{
			title += html[ pos ];
			++pos;
			}
		}
	return title;
	}

/**
 * Will return new url if local
 *
 * @param url
 * @param currentUrl
 * @return
 */
string Parser::isLocal ( string url, ParsedUrl* currentUrl )
	{
	if( url.size() <= 1)
		return url;

	if ( url[ 0 ] != '/' )
		{
		return url;
		}

	if ( currentUrl->getCompleteUrl( ).back( ) == '/' )
		{
		string temp = currentUrl->getDomain( );
		temp.pop_back();
		url = temp + url;
		}
	else
		{
		url = currentUrl->getDomain( ) + url;
		}
	return url;
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
	// #
	if ( url[ 0 ] == '#' )
		{
		return false;
		}
	if ( url[ 0 ] == '/' )
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
void Parser::pushToUrlQueue ( string url, ParsedUrl * currentUrl, string anchorText, bool debug )
	{
	url = isLocal( url, currentUrl );
	if ( isValid( url ) && url != currentUrl->getCompleteUrl( ) )
		{
		try
			{
			ParsedUrl url_(url);
			url_.setAnchorText( anchorText );
			urlFrontier->Push( url_ );
			if ( debug )
				{
				cout << url << endl;
				cout << anchorText << endl;
				}
			}
		catch (exception e)
			{
			cerr << "HTML url parsed from web page had issue creating object" << endl;
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
                  ParsedUrl * currentUrl )
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
			pushToUrlQueue( url, currentUrl, extractAnchorText( line ), true );
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
                     ParsedUrl * currentUrl )
	{
	string body = "";
	unsigned long startParTag = findNext( "<p", 0, html );
	startParTag = findNext( ">", startParTag, html) - 1;
	unsigned long closeParTag = findNext( "</p>", startParTag, html );
	unsigned long nextCloseTag = findNext( "</", startParTag, html );
	startParTag += 2;
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
