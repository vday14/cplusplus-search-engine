
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
 * @return pointer to unordered_map< string, vector< int>>
 */
unordered_map< string, vector< int>> *Tokenizer::get ( ) const
	{
	return docIndex;
	}

/**
 * Executes the Tokenizer
 * Sends tokens to dictionary
 * token -> [offsets]
 * @param originalText
 * @param offset
 */
void Tokenizer::execute ( string originalText, int offset )
	{
	vector< string > splitText = splitStr ( originalText, ' ' );
	//TODO make function to remove characters
	//TODO normalize contractions
	string lowerString = "";
	for ( int i = 0; i < splitText.size ( ); ++i )
		{
		lowerString = toLower ( splitText[ i ] );
		if ( !isStopWord ( lowerString ) )
			{
			( *docIndex )[ lowerString ].push_back ( offset );
			++offset;
			}
		}
	}
