
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "stringProcessing.h"
#include "Stemmer.h"
#include "../parser/Parser.h"

using namespace std;


class Tokenizer
	{

public:
	struct wordData {
		int frequency = 0;
		int offset;
	};
	
	Tokenizer ( )
		{
		docIndex = new unordered_map< string, vector<wordData>>;
		}

	unordered_map< string, vector< wordData>> *get ( ) const
		{
		return docIndex;
		}
	//add type of word parameter, ie paragraph, url etc

    void execute ( string & originalText, int offset )
		{
		vector< string > splitText = splitStr ( originalText, ' ' );
        string processedString = "";
		int vectorLength = 0;
        for ( int i = 0; i < splitText.size( ); ++i )
            {
             // case fold
             processedString = toLower( splitText[ i ] );
             //strip all characters
             processedString = stripStr( processedString );

             if ( !isStopWord ( lowerString ) )
				{
                // stem word
                processedString = stem.execute( processedString );

                wordData currentWord;
				currentWord.offset = offset;
				vectorLength = ( *docIndex )[ lowerString ].size( );
				( *docIndex )[ lowerString ].push_back ( currentWord );
                //incrementing frequency value of the current word
				( *docIndex )[ lowerString ][ vectorLength - 1 ].frequency += 1;
				++offset;
				}
			}
		}



	// decorators
	static const char TITLE = '#';
	static const char ANCHOR = '@';
	static const char URL = '$';

	/**
 	* Tokenizer Cstor
 	*/
	Tokenizer ( );

	/**
 	* Returns pointer to the docIndex dictionary
	 *
 	* @return pointer to unordered_map< string, vector< int>>
 	*/
<<<<<<< HEAD
	unordered_map< string, vector<wordData>> *get ( ) const;
=======
	unordered_map< string, vector< unsigned long > > *get ( ) const;
>>>>>>> 02e3c89768ec57f7ea0c16a6fdf7e3d17c3d07bb

	/**
	 * Executes the Tokenizer
	 * Sends tokens to dictionary
	 *
	 *
	 * @param originalText
	 * @param offset
	 * @param decorator
	 */
	unsigned long execute ( string originalText, unsigned long offset, char decorator = '\0' );

private:

	unordered_map< string, vector< unsigned long > > *docIndex;
	Stemmer stem;

	/**
	 * Tokenizes text (titles, body text)
	 *
	 * @param originalText
	 * @param offset
	 * @param decorator
	 */
	unsigned long tokenize ( vector< string > splitText, unsigned long offset, char decorator );

<<<<<<< HEAD
	private:
        unordered_map< string, vector<wordData>> *docIndex;
		Stemmer stem;
=======
>>>>>>> 02e3c89768ec57f7ea0c16a6fdf7e3d17c3d07bb
	};
