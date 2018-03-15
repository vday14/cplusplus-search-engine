
#include "Parser.h"


/**
 * Parses file
 * @param inFile
 * @return
 */
//TODO instead of grabbing each line, look to see if beginning of
// TODO title/url/anchortext, etc. Then continue until close tag and add to tokenizer after end of tag found
// TODO have to read input in as a stream of chars eventually - cat into string?
// TODO different counts: frequency, total num unique words, etc
// TODO handle bad html style (ie no closing p tag)
//TODO flag different types of words - determine if we want to do this in key of dict or value (in wordData struct)

void Parser::parse ( string html, Tokenizer *tokenizer )
	{

	//maybe add some code to read in stream and add chars to string as they come in
	auto htmlIt = html.begin();
	int offset = 0;
	while (htmlIt != html.end())
		{
		// if open bracket
		if ( *htmlIt == '<' )
			{
			// TODO have to put a conditional that ensures the opening and closing tags are the same type
			auto begCloseTag = findNext ("</", htmlIt);
			auto endCloseTag = findNext ( ">", begCloseTag);
			string line (htmlIt, endCloseTag + 1);
			htmlIt = endCloseTag + 2;

			//check if line is a script
			if ( isScript( line ) )
				{
				// DO NOTHING
				}
			// check if line is url
			else if ( url = extract_url( line ) != "" )
				{
				//where is urlFrontier defined?
				urlFrontier->push ( url );
				}
			// check if line is title
			else if ( title = extract_title( line ) != "" )
				{
				tokenizer->execute ( title, offset );
				}
            else if ( body = extract_body( line ) != "")
                {
                tokenizer->execute( body, offset );
                }
			else
				{
				//DO NOTHING
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

bool Parser::isScript ( string word )
	{
	if ( *findStr ( "<script", word ) != '\0' )
		{
			return true;
		}
	return false;
	}

string Parser::extract_body( string word )
    {
    string body = "";
    auto foundBody = findStr("<p", word) != '\0';
    if ( *foundBody != '\0' )
        {
        while ( *findStr != '<' )
            {
            body += *findStr;
            }
        }
    return body;
    }

string Parser::extract_url ( string word )
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
string Parser::extract_title ( string & word )
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

