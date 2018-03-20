
#include "Parser.h"


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
	//parse( document->DocToString( ), document->getUrl( ), &tokenizer );
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
	reader->request();
	bool success = reader->checkStatus();
	if(success) {
		string html = reader->PageToString();
		ParsedUrl currentUrl = reader->getUrl();

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

/**
 * Returns false if the link is an invalid type
 *
 * @param url
 * @return
 */
bool Parser::isValid ( string url )
	{
	auto begPtr = url.begin( );
	auto endPtr = begPtr + url.size( ) - 1;
	unsigned long size = url.size( );

	auto html = findPrev( ".html", endPtr, begPtr + size - 6 );

	if ( *html != '\0' )
		{
		return true;
		}

	// png
	if ( *findPrev( ".png", endPtr, begPtr + size - 5 ) != '\0' )
		{
		return false;
		}
	//jpg
	if ( *findPrev( ".jpg", endPtr, begPtr + size - 5 ) )
		{
		return false;
		}
	//jpeg
	if ( *findPrev( ".jpeg", endPtr, begPtr + size - 6 ) )
		{
		return false;
		}
	//css
	if ( *findPrev( ".css", endPtr, begPtr + size - 5 ) )
		{
		return false;
		}
	//gif
	if ( *findPrev( ".gif", endPtr, begPtr + size - 5 ) )
		{
		return false;
		}
	//pdf
	if ( *findPrev( ".pdf", endPtr, begPtr + size - 5 ) )
		{
		return false;
		}
	//wav
	if ( *findPrev( ".wav", endPtr, begPtr + size - 5 ) )
		{
		return false;
		}
	//mp3
	if ( *findPrev( ".mp3", endPtr, begPtr + size - 5 ) )
		{
		return false;
		}
	return true;
	}