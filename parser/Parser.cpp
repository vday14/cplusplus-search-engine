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
<<<<<<< HEAD
// TODO title/url/anchortext, etc. Then continue until close tag and add to tokenizer after end of tag found
// TODO different counts: frequency, total num unique words, etc
//TODO flag different types of words - determine if we want to do this in key of dict or value (in wordData struct)
/*
 * Anchor text = #
 * Title = *
 * Url = @
 * Body = %
 */

void Parser::parse ( string html, Tokenizer *tokenizer )
	{

	//maybe add some code to read in stream and add chars to string as they come in
	auto htmlIt = html.begin();
	int offset = 0;
	while (htmlIt != html.end())
=======
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
	string urlCurrent = host + "/" + path;

	offsetURL = tokenizer->execute( urlCurrent, offsetURL, Tokenizer::URL );

	while ( htmlIt < html.size( ) )
>>>>>>> 02e3c89768ec57f7ea0c16a6fdf7e3d17c3d07bb
		{
		// if open bracket
		if ( html[ htmlIt ] == '<' )
			{
<<<<<<< HEAD
			// TODO have to put a conditional that ensures the opening and closing tags are the same type
			auto begCloseTag = findNext ("</", htmlIt);
			auto endCloseTag = findNext ( ">", begCloseTag);
			string line (htmlIt, endCloseTag + 1);
=======
			unsigned long begCloseTag = findNext( "</", htmlIt, html );
			unsigned long endCloseTag = findNext( ">", begCloseTag, html );
			string line = subStr( html, htmlIt, endCloseTag + 1 - htmlIt );
>>>>>>> 02e3c89768ec57f7ea0c16a6fdf7e3d17c3d07bb
			htmlIt = endCloseTag + 2;

			//check if line is a script
			if ( isScript( line ) )
				{
				// DO NOTHING
				}
			// check if line is url
<<<<<<< HEAD
			else if ( url = extract_url( line ) != "" )
				{
				//where is urlFrontier defined?
				urlFrontier->push ( url );
				}
			// check if line is title
			else if ( title = extract_title( line ) != "" )
				{
				tokenizer->execute ( title, offset );
=======
			string url = extract_url( line );
			if ( url != "" )
				{
				if ( isLocal( url ) )
					{
					string completeUrl = "";
					completeUrl.assign( currentUrl.CompleteUrl );
					url = completeUrl + url;
					}
				if ( isValid( url ) && url != urlCurrent )
					{
					// TODO ParsedUrl with anchor text
					ParsedUrl pUrl = ParsedUrl( url );
					urlFrontier->Push( pUrl );
					cout << url << endl;
					}
>>>>>>> 02e3c89768ec57f7ea0c16a6fdf7e3d17c3d07bb
				}
            else if ( body = extract_body( line ) != "")
                {
                tokenizer->execute( body, offset );
                }
			else
				{
<<<<<<< HEAD
				//DO NOTHING
=======
				string title = extract_title( line );
				if ( title != "" )
					{
					offsetTitle = tokenizer->execute( title, offsetTitle, Tokenizer::TITLE );
					}
>>>>>>> 02e3c89768ec57f7ea0c16a6fdf7e3d17c3d07bb
				}
			}
		else
			{
			++htmlIt;
			}
		}
	}


/*
 * Returns true if script tag, false if not
*/
bool Parser::isScript ( string & word )
	{
	if ( *findStr ( "<script", word ) != '\0' )
		{
			return true;
		}
	return false;
	}
/*
 * Returns body text if p tags, empty string if not
 * If there's no closing tag, stops at the first opening tag or when it hits end of file
*/
string Parser::extract_body( string & word, int & offset )
    {
    string body = "";
    auto foundBody = findStr("<p", word) != '\0';
    if ( *foundBody != '\0' )
        {
        while ( *findStr != '<' )
            {
            body += *findStr;
			if ( *findStr == ' ')
				{
				count += 1;
				}
            }
        }
    return body;
    }

/**
 * Returns a url, or "" if none
 * @param word
 * @return
 */
<<<<<<< HEAD

string Parser::extract_url ( string & word )
=======
string Parser::extract_url ( string html )
>>>>>>> 02e3c89768ec57f7ea0c16a6fdf7e3d17c3d07bb
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
