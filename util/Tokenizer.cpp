
#include "Tokenizer.h"
#include <iostream>
#include <set>
#include <string>

using namespace std;

/**
 * Tokenizer Cstor
 */
Tokenizer::Tokenizer ( )
	{
	docIndex = new unordered_map< string, vector< unsigned long > >;
	haveTitle = false;
	}

/**
 * Returns pointer to the docIndex dictionary
 *
 * @return pointer to unordered_map< string, vector< int>>
 */
const unordered_map< string, vector< unsigned long > > *Tokenizer::get ( ) const
	{
	return docIndex;
	}

/**
 * Executes the Tokenizer
 * Sends tokens to dictionary
 *
 * @param originalText
 * @param offset
 * @param decorator
 */
unsigned long Tokenizer::execute ( string originalText, unsigned long offset, char decorator )
	{
	// split by symbols
	if ( decorator == Tokenizer::URL )
		{
		set< char > split = { '.', ':', '/', '\\', '_', '?', '-', '~', '#', '[', ']', '@', '!', '$', '&', '\'',
		                      '(', ')', '*', '+', ',', ';', '=' };

        ( *docIndex )[ Tokenizer::HOST + originalText ].push_back( 0 );
		return tokenize( splitStr( originalText, split, true ), offset, decorator );

		}
	// split by spaces
	else
		{

		originalText = unEncodeHtml( originalText );

        if( decorator == Tokenizer::TITLE && !haveTitle )
	        {
	        ( *docIndex )[ Tokenizer::HOST + originalText ].push_back( 1 );
	        haveTitle = true;
	        }

		return tokenize( splitStr( originalText, ' ', true ), offset, decorator );
		}
	}



/**
 * Tokenizes text (titles, body text)
 *
 * @param originalText
 * @param offset
 * @param decorator
 */
unsigned long Tokenizer::tokenize ( vector< string > splitText, unsigned long offset, char decorator )
	{
	string processedString = "";
	for ( int i = 0; i < splitText.size( ); ++i )
		{
		// case fold
		processedString = toLower( splitText[ i ] );

		// remove "click here" etc
		if ( decorator == Tokenizer::ANCHOR && anchorsToRemove.find( processedString ) != anchorsToRemove.end( ) )
			continue;

		if ( !isStopWord( processedString ) )
			{
			// stem word
			processedString = stem.execute( processedString );
			if ( decorator != '\0' )
				{
				processedString = decorator + processedString;
				}
			( *docIndex )[ processedString ].push_back( offset );
			++offset;
			}
		}
	return offset;
	}

