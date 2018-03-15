
#include "Parser.h"


/**
 * Parses file
 * @param inFile
 * @return
 */
//TODO instead of grabbing each line, look to see if beginning of
// TODO title/url/anchortext, etc. Then continue until close tag and add to tokenizer after end of tag found
void Parser::parse ( string html, Tokenizer *tokenizer )
	{
	auto htmlIt = html.begin();
	int offset = 0;
	while (htmlIt != html.end())
		{
		// if open bracket
		if ( *htmlIt == '<' )
			{
			auto begCloseTag = findNext ("</", htmlIt);
			auto endCloseTag = findNext ( ">", begCloseTag);
			string line (htmlIt, endCloseTag + 1);
			htmlIt = endCloseTag + 2;

			// check if line is url
			string url = extract_url ( line );
			if (url != "")
				{
				urlFrontier->Push ( url );
				}
				// check if line is title
			else
				{
				string title = extract_title ( line );
				if (title != "")
					{
					tokenizer->execute ( title, offset );
					}
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
string Parser::extract_url ( string & word )
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

