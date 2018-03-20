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
    unsigned long offsetBody = 0;
    unsigned long offsetURL = 0;

    // tokenize url
    string host = "";
    host.assign( currentUrl.Host );
    string path = "";
    path.assign( currentUrl.Path );
    string urlCurrent = host + "/" + path;

    offsetURL = tokenizer->execute( urlCurrent, offsetURL, Tokenizer::URL );

    while ( htmlIt < html.size( ) )
    {
        unsigned long begCloseTag = 0;
        bool isParagraph = false;
        unsigned long savePosition = htmlIt;
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
            string title = extract_title( line );
            string url = extract_url( line );
            string header = extract_header( line );
            //checking if html line is script
            if ( isTag( line, "script" ) )
            {
                //DO NOTHING
            }
                //checking for p tag
            else if ( isParagraph )
            {
                string body = extract_body( line, offsetTitle, offsetBody, isParagraph, tokenizer, currentUrl, urlCurrent );
                offsetBody = tokenizer->execute( body, offsetBody, Tokenizer::BODY );
            }
                //if html line is url, parses accordingly and pushes to frontier
            else if ( url != "" )
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
                    // urlFrontier->Push( pUrl );
                    cout << url << endl;
                }
            }
                //check if line is header; classifies as body text
            else if ( header != "")
            {
                offsetBody = tokenizer->execute( header, offsetBody, Tokenizer::BODY );
            }
                // check if line is title
            else if ( title != "")
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

//TODO delete?? may not need
void Parser::remove_tag( string & html, unsigned long & htmlIt, unsigned long savePosition, string tag)
{
    unsigned long openTag = findStr( "<" + tag + ">", html );
    unsigned long closeTag = findNext( "</" + tag + ">", openTag, html );
    //TODO write erase functions??
    html.erase( closeTag, tag.length( ) + 2 );
    html.erase( openTag, tag.length( ) + 3 );

    htmlIt = savePosition;
}
void Parser::extract_all ( string line, unsigned long & offsetTitle, unsigned long & offsetBody, bool isParagraph, Tokenizer * tokenizer,
                           ParsedUrl & currentUrl, string & urlCurrent  )
{
    // check if line is url
    string title = extract_title( line );
    string url = extract_url( line );
    //checking if html line is script
    if ( isTag( line, "script" ) )
    {
        //DO NOTHING
    }
        //TODO delete this conditional if keeping whats in main right now
    else if ( isParagraph )
    {
        string body = extract_body( line, offsetTitle, offsetBody, isParagraph, tokenizer, currentUrl, urlCurrent );
        offsetBody = tokenizer->execute( body, offsetBody, Tokenizer::BODY );
    }

    else if ( url != "" )
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
            // urlFrontier->Push( pUrl );
            cout << url << endl;
        }
    }
        // check if line is title
        // check if line is title
    else if ( title != "")
    {
        offsetTitle = tokenizer->execute( title, offsetTitle, Tokenizer::TITLE );
    }

    else
    {
        //DO NOTHING
    }
}
/**
 * Returns true if tag is in html, false if not
 * @param html
 * @return
 */
bool Parser::isTag( string html, string tag )
{
    string findTag = "<" + tag;
    if ( findStr( findTag, html ) != html.size( ) )
    {
        return true;
    }
    return false;
}

string Parser::extract_body( string html, unsigned long & offsetTitle, unsigned long & offsetBody, bool isParagraph, Tokenizer * tokenizer,
                             ParsedUrl & currentUrl, string & urlCurrent )
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
                if ( startParTag >= html.size( ))
                {
                    return body;
                }
            }
        }
        else
        {
            unsigned long newHtmlStart = findNext ( "<", startParTag, html );
            char a = html[ newHtmlStart ];
            unsigned long closeNewHtml = findNext ( ">", newHtmlStart, html );
            char b = html[ closeNewHtml ];
            unsigned long newHtmlTagLength = closeNewHtml - newHtmlStart;

            while ( startParTag != newHtmlStart )
            {
                body += html[ startParTag ];
                ++startParTag;
            }

            string newHtml = subStr(html, newHtmlStart, nextCloseTag - newHtmlStart + newHtmlTagLength + 2);
            extract_all( newHtml, offsetTitle, offsetBody, false, tokenizer, currentUrl, urlCurrent);
            startParTag = nextCloseTag + newHtmlTagLength + 2;
            nextCloseTag = findNext( "</", startParTag, html );
        }
    }

    return body;
}

string Parser::extract_header( string html )
{
    string header = "";
    unsigned long startHeader = findStr( "<h", html );
    if ( startHeader !=  html.size( ) && ( html[ startHeader + 1] >= '1' && html[ startHeader + 1 ] <= '6' ) )
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
