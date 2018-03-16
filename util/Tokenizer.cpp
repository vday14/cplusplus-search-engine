
#include "Tokenizer.h"

/**
 * Tokenizer Cstor
 */
Tokenizer::Tokenizer ( )
	{
	docIndex = new unordered_map< string, vector< int>>;
	}

/**
 * Returns pointer to the docIndex dictionary
 *
 * @return pointer to unordered_map< string, vector< int>>
 */
unordered_map< string, vector< int>> *Tokenizer::get ( ) const
	{
	return docIndex;
	}

/**
 * Executes the Tokenizer
 * Sends tokens to dictionary
 *
 * token -> [offsets]
 * @param originalText
 * @param offset
 */
void Tokenizer::execute ( string & originalText, unsigned long offset )
	{
	vector< string > splitText = splitStr( originalText, ' ', true );
	string processedString = "";
	for ( int i = 0; i < splitText.size( ); ++i )
		{
		// case fold
		processedString = toLower( splitText[ i ] );
		//strip all characters

		if ( !isStopWord( processedString ) )
			{
			// stem word
			processedString = stem.execute( processedString );
			( *docIndex )[ processedString ].push_back( offset );
			++offset;
			}
		}
	}
